# 歌词格式与返回键

## 歌词格式（30）

`type = "lyric-source"` 的选中实现可在 `query_interface` 返回 `LyraLyricFormatV3`。转换与 `supply` 独立。只提供转换时，宿主仍负责读取原始歌词。

| 操作 | 输入 | 成功回复 |
| --- | --- | --- |
| `LYRA_LYRIC_NORMALIZE` | `LYRA_LYRIC_INPUT`，BYTES | `LYRA_LYRIC_OUTPUT`，BYTES |

输出为默认歌词解析器支持的 UTF-8 歌词文本，不带 NUL。空输出清除歌词，`UNSUPPORTED` 交回宿主处理原始输入。回调在帧线程同步执行，每条消息最多 1 MiB。返回后宿主立即复制数据。此接口处理播放歌词，本地后台全库索引仍使用内置解析。需要独立索引时使用[搜索提供者](/plugins/media#替换默认搜索与本地来源)。

## 根返回键（29）

`type = "frame"` 的选中实现可提供 `LyraNavigationV3`。

- `LYRA_NAVIGATION_BACK_AVAILABLE` 查询能否消费 Back。可处理时返回 `OK`，其余情况返回 `UNSUPPORTED`。查询不改变页面。
- `LYRA_NAVIGATION_BACK` 执行返回操作，消费后返回 `OK`。
- 两种消息都不带字段。可用状态变化后调用 `host->request_frame`，宿主在帧上同步 Android 返回拦截。

独立根负责场景、触摸和帧请求。保留默认页面时，使用 [服务上下文](/plugins/service-context) 显式委托。没有 Back 端点时由系统处理返回。

[歌词格式头文件](/downloads/sdk/include/plugin/lyric_format_contracts.h) · [导航头文件](/downloads/sdk/include/plugin/navigation_contracts.h)
