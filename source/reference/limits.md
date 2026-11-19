# 平台兼容范围

| 项目 | 约定 |
| --- | --- |
| Android | API 26 起，正式包 arm64-v8a |
| SDK | ABI 3。可选接口通过 ID、版本和精确大小探测。 |
| 默认播放 | 系统 MediaExtractor 和 MediaCodec，格式随设备而变。FFmpeg 可作为外部播放插件安装。 |
| 插件权限 | 进程内原生代码。系统权限受 Android 授权及宿主清单约束。 |
| 格式 | 配置使用宿主支持的 TOML 子集，插件详情使用受限 Markdown。 |
| 活动资料库 | `source` 优先。默认本地适配器可通过 `library.mediastore` 替换。 |
| 歌单与队列 | 可保存提供者与曲目 UID。集合请求 ID 和队列行号仅在当前运行期间有效。 |
| Android 文档选择 | 当前 Activity 共享结果槽。插件需在发起新请求前处理已有结果。 |

[具体版本](/reference/snapshot) · [接口目录](/reference/abi)
