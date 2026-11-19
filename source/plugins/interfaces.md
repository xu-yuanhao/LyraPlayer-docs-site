# 接口查询与返回约定

```c
const LyraPlaybackInterfaceV3 *playback = host->query_interface(
    host->user, LYRA_INTERFACE_PLAYBACK,
    LYRA_INTERFACE_VERSION, sizeof(LyraPlaybackInterfaceV3));
if (!playback) return -1;
```

接口查询返回 NULL 时，该能力不可用。填写输出结构的 `size`，调用可选回调前检查函数指针。

接口的发现方式和完整头文件见[公共 C SDK](/reference/abi)。

## 字符串读取

歌词/catalog/schema 的有界 text 接口返回包括结尾 NUL 的所需 UTF-8 字节数。缓冲不足不修改缓冲；先查询长度，再分配足够内存并在同 revision 下读取。负数代表无效索引/字段/过期 revision；接口各自其他状态以头文件与实现为准。不要把字节数当字符数或 UTF-16 单元数。

媒体信息通过 media descriptor 和 media context 读取完整文本。`config.describe` 的固定预览字段可能截断，返回 1 表示预览截断；完整值走 schema text。

## 播放命令

command 返回 0 表示执行、1 表示帧内接受后延迟、负数拒绝。不要因为返回 1 没立即改变 position 就重复发送。延期命令绑定 generation，旧曲目的操作不能落到新曲目上。

队列给出的是目录索引和当前队列行，二者不是曲目 ID；索引只在当前目录版本有效。选择队列行使用 QUEUE\_SELECT，SELECT 使用目录索引。


## 媒体数据与资源

新增可选媒体接口见[媒体数据插件](/plugins/media)。查询成功才使用；旧宿主没有这些接口时应停止相关功能并提示升级，不能假设安装任意版本就有在线播放能力。原有 ABI 3 的结构布局不变。

`CATALOG` 返回当前播放目录；播放在线集合时，它与真实队列的目录索引对应。需要本地资料库数据，请通过媒体上下文请求内置提供者 `system.local` 的集合，而不是把当前播放目录永远当作本地库。

## 播放选择观察者

服务可在自身 `query_interface` 返回 `LyraPlaybackObserverV3`，ID 为 15，接口版本为 2。回调在宿主拥有者线程执行；只在服务有效期间绑定，替换后旧默认服务不再收到该通知，卸载前撤销。旧宿主可能不支持该可选接口。描述符、user 和回调必须有效到 shutdown。

事件仅在回调期间借用，不能保存事件指针。from\_entry / to\_entry 是播放集合条目身份，同一媒体重复加入也有不同身份；track\_id 是宿主媒体 ID，来源不可用时可为 -1。position\_us / duration\_us 是微秒；direction 是默认转场方向提示。RESET 表示新的选择需要重置曲目相关状态，OPENING 表示即将重新打开音频资源。generation 是通知发布时的音频代次；打开通知可以早于新解码器创建，不能当成解码就绪或 seek 已完成。进度、歌词和可视化继续读取 PLAYBACK 快照，不能从通知创建第二套播放计时器。

回调里的播放命令延迟到当前选择处理完成后执行；返回 1 表示排队，未必已经打开音频。显式提供的 generation 仍会按既有规则校验。需要绘制时调用 request\_frame，selection 回调本身不是绘制帧。

```c
static void selection(void *user, const LyraPlaybackSelectionV3 *event) {
    const LyraHostV3 *host = user;
    if (!event || event->size != sizeof(*event)) return;
    if (event->flags & LYRA_SELECTION_RESET)
        host->request_frame(host->user);
}
static LyraPlaybackObserverV3 observer;
/* 在插件初始化中绑定宿主，query_interface(15, 2, size) 返回 &observer。 */
static void bind_observer(const LyraHostV3 *host) {
    observer = (LyraPlaybackObserverV3){sizeof(observer),
        LYRA_INTERFACE_VERSION, (void *)host, selection};
}
```

host.user 必须保持不透明。始终使用收到的 host 与 host.user 调用函数；不要假定它指向某个页面或当前窗口。不同实例可有不同的 VM / Activity 和密度；Android VM / Activity 的生命周期仍遵守系统规则。后台线程不能提交绘制命令，必须 request\_frame 后在 on\_frame 提交。shutdown 必须停止并等待自己的线程，不得在 shutdown 中重新注册回调。

默认组件的公开复用流程见[服务上下文](/plugins/service-context)。内置实现和插件均通过这些 C 接口连接，不提供宿主私有 C++ 对象。

接口 18：`LYRA_INTERFACE_PLUGIN_INVENTORY`，读取本实例安装/内置插件清单，使用 `LyraPluginInventoryV3.list`。

## 剪贴板消息能力

`LYRA_INTERFACE_CLIPBOARD`（ID 19）通过 `system.clipboard` 的服务句柄查询，消息接口包含精确的 size/version/user/request 字段。调用和替换约定见[剪贴板接口](/plugins/clipboard)。

## 系统网页导航

`LYRA_INTERFACE_LINKS`（ID 20）通过 `system.links` 服务查询。只接收 http(s) 网页地址，使用精确 size/version/user/request 消息接口；不接受 Intent extras 或组件名。见[系统网页接口](/plugins/links)。
