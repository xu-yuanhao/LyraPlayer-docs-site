# 选择插件入口

| 目标 | 清单 type 或接口 | 文档 |
| --- | --- | --- |
| 替换整套界面 | `frame`，可提供返回键接口 29 | [画面与输入](/plugins/host) · [返回键](/plugins/presentation) |
| 更换一个组件 | 对应服务名，例如 `lyrics`、`controls` | [服务目录](/reference/services) |
| 新样式、新播放模式 | 样式声明 3，或 rules 5 与 modes 8 | [样式](/plugins/styles) · [播放规则](/plugins/rules) |
| 替换解码与输出 | `playback`，提供接口 6 | [播放后端](/plugins/playback) |
| 接入搜索、集合、资源 | 媒体提供者 14 | [媒体插件](/plugins/media) |
| 替换本地扫描来源 | `library.mediastore`，提供接口 14 | [本地来源](/plugins/media#替换默认搜索与本地来源) |
| 支持新的歌词格式 | `lyric-source`，提供接口 30 | [歌词格式](/plugins/presentation) |
| 增加设置入口、参数 | 设置页 26、配置 schema 9 | [设置与消息](/plugins/messages) · [参数](/plugins/config-schema) |
| 调整资料库分类 | `profile-classification`，提供接口 12 | [分类配置](/config/classification) |

包 ID 标识安装项，type 声明插件占用的服务槽。同一槽仅一个活动实现。用[服务上下文](/plugins/service-context)显式调用其他服务或默认实现。

跨库数据以 SDK 头文件为准。平台调用、回调线程和资源回收分别见 [Android](/plugins/android) 与 [生命周期](/plugins/lifecycle)。
