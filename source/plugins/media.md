# 媒体数据插件



## 能力查询与注册

插件通过 `query_interface` 提供 `LyraMediaProviderV3`（ID 14，版本 3，完整结构大小）。独立来源使用唯一的 capability，例如 `example-online`。同名 capability 竞争同一个服务槽。提供者 `id` 须唯一、非空且不含换行。

数据插件无需 `on_frame`。若声明 `search` 并提供 `on_frame`，这是替换搜索呈现，宿主不会再画默认搜索列表。只提供数据时保留默认行布局、封面、点击、输入与滚动。

## 身份与描述

集合内 `uid` 非空且唯一。跨集合的真实曲目使用 `(origin_provider, origin_uid)` 识别；省略时使用当前提供者和本条 `uid`。歌单可用独立条目 UID 指向别的提供者曲目，同一首歌能重复出现在歌单中。不要把远程 ID 伪装成 MediaStore ID。

描述包含标题、艺术家、专辑、流派、文件夹、时长、音频 URI、封面 URI、歌词 URI、内嵌歌词文本、封面缓存 key 与来源身份。时长单位是微秒；`cover_key` 为 0 时宿主按曲目身份生成缓存 key。

## 搜索与集合

`request` 收到 SEARCH 或 COLLECTION 后可同步发布，也可在工作线程发布。复制请求字符串；它们只在 request 调用期间有效。sink 在提供者关闭前有效；shutdown 返回前必须停下并等待全部工作线程。

用 `LyraMediaBatchV3` 发布结果。宿主在返回前复制字符串。默认批次替换该请求结果；APPEND 按条目 UID 更新或追加，单个批次不能包含重复 UID。COMPLETE 表示结束，error 非零表示失败，cursor 是下一页令牌。每次发布都改变集合 revision。

上下文 request 返回非零请求 ID；0 表示拒绝。count 返回 -1 表示失效。item 成功返回 0；输出先填 size。item 与 collection\_state 字符串借用至下一帧、revision 变化或取消。collection\_state 提供 error、complete、cursor；复制游标后可发起后续页请求。默认列表不会自动发起任意提供者的分页，提供者可持续向同一请求 APPEND，结果数量受配置预算限制。

选择已发布集合中的行用 select；返回 0 表示接受，下帧执行。选择复制集合成播放队列，改变搜索文字或取消原搜索不会清空当前播放队列。current、queue\_count、queue\_item、queue\_select 读取或选择真实队列。标题与封面依照描述，不依赖曲目是否存在本地库。

## 资源与所有权

AUDIO、COVER、LYRICS 请求包含真实来源 UID。通过 sink.resolved 返回资源：可转交可读、可 seek 的 fd，或返回 HTTPS URI 与 JSON 请求头。fd 的所有权在调用 resolved 时移交，即使请求过期被拒绝也由宿主关闭；插件不能再关闭或复用它。

take\_resource 返回 1 时资源就绪并转移 fd；0 表示未完成，-1 表示无效请求。资源字符串仍属于请求，取消前先复制。使用完 fd 后接收方负责关闭。音频交给宿主播放后由播放链负责关闭。

默认 Android HTTPS 桥把有界完整资源下载成可 seek 的缓存 fd，再交给现有解码器；不承诺直播流、DRM、无限流或边下边播。跨源重定向不传递请求头，HTTP 明文 URL 被拒绝。需要自定义传输的插件通过 Activity/Java VM 或自己实现资源读取，再提供符合约定的 fd。可用解码格式仍取决于系统或安装的播放插件。

数据插件没有自绘要求。自行请求的资源可用 take\_resource 消费，不会被宿主默认播放器抢走。取消、换歌、查询 revision 与提供者生命周期共同阻止旧结果落到新曲目。

## 线程和异步输入

除 set\_query 以及 sink.publish/resolved 外，上下文和提供者 request/cancel 在帧线程调用。工作线程使用 set\_query(query\_revision, text) 做比较并设置；文字已变化时返回 -1，避免旧异步响应覆盖新输入。返回 0 表示事件已接受，帧线程仍会再次验证 revision。不要从音频实时回调发布或调用插件接口。

cancel 后该 ID 不能再发布。request/cancel 不应等待网络；耗时任务放工作线程。插件 shutdown 必须等待线程退出。

## 可配置预算

[media 配置表](/config/reference/ui-media) 控制条目上限、单次文本与累计内存预算、并发请求、下载字节上限、超时、工作线程数和读取块大小。默认资源上限 128 MiB、集合条目上限 512；超过预算会拒绝，插件须处理返回值。提高预算会增加内存或磁盘消耗。

## 替换默认搜索与本地来源

| 清单 type | 提供接口 | 接管范围 |
| --- | --- | --- |
| `search` | `LYRA_INTERFACE_MEDIA_PROVIDER`（14） | 保留默认搜索界面并返回自己的搜索结果。选中时停用内置索引。 |
| `library.mediastore` | 同上 | 替换默认本地适配器和活动资料库，卸载后恢复系统扫描。 |
| `source` | 同上 | 提供活动资料库集合，优先于 `library.mediastore`。 |

如需保留默认结果界面，`search` 只提供数据接口，不填写绘制回调。通过 `LYRA_MEDIA_SEARCH` 接收查询，以对应请求 ID 发布列表。带绘制回调的搜索插件可接管搜索呈现。

用 `origin_provider` 与 `origin_uid` 长期保存来源身份。集合请求 ID 和行号只属于当前会话。宿主在来源切换后撤销旧请求，插件应在 `cancel` 后停止任务和发布。队列及个人歌单的写入方式见[媒体操作](/plugins/messages)。
