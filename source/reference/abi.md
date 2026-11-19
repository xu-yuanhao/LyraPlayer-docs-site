# 公共 C SDK

[下载 SDK 与示例](/downloads/lyra-plugin-sdk.zip) · [兼容性](/reference/snapshot) · [查询与返回约定](/plugins/interfaces)

`lyra_plugin.h` 声明 Host、入口及绘制指令。接口通过 Host、指定服务或插件自身的 `query_interface` 发现，按下表链接的头文件编译。先以精确版本和结构大小查询，再使用回调。接口 ID 7 保留。

| 任务 | 发现位置 |
| --- | --- |
| 播放命令、歌词快照、配置、媒体上下文 | Host 查询，见对应接口页 |
| 播放后端、媒体提供者、规则、样式与观察者 | 插件描述符的 `query_interface` |
| 选中或默认服务 | Host 查询服务上下文（16），按句柄发现 |
| 设置页、歌词格式、返回键等消息能力 | 由相应服务提供，调用选中实现可通过接口 28 |

## 接口目录

| ID | 宏 | 契约 | 头文件 |
| --- | --- | --- | --- |
| 1 | `LYRA_INTERFACE_PLAYBACK` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 2 | `LYRA_INTERFACE_LYRICS` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 3 | `LYRA_INTERFACE_STYLES` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 4 | `LYRA_INTERFACE_CONFIG` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 5 | `LYRA_INTERFACE_RULES` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 6 | `LYRA_INTERFACE_PLAYBACK_PROVIDER` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 8 | `LYRA_INTERFACE_MODES` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 9 | `LYRA_INTERFACE_CONFIG_SCHEMA` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 10 | `LYRA_INTERFACE_PLUGIN_CATALOG` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 11 | `LYRA_INTERFACE_PLUGIN_DETAILS` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 12 | `LYRA_INTERFACE_CLASSIFICATION_RULES` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 13 | `LYRA_INTERFACE_MEDIA_CONTEXT` | 固定结构 | [media_contracts.h](/downloads/sdk/include/plugin/media_contracts.h) |
| 14 | `LYRA_INTERFACE_MEDIA_PROVIDER` | 固定结构 | [media_contracts.h](/downloads/sdk/include/plugin/media_contracts.h) |
| 15 | `LYRA_INTERFACE_PLAYBACK_OBSERVER` | 固定结构 | [event_contracts.h](/downloads/sdk/include/plugin/event_contracts.h) |
| 16 | `LYRA_INTERFACE_SERVICE_CONTEXT` | 固定结构 | [service_contracts.h](/downloads/sdk/include/plugin/service_contracts.h) |
| 17 | `LYRA_INTERFACE_PRESENTATION_CONTEXT` | 固定结构 | [presentation_contracts.h](/downloads/sdk/include/plugin/presentation_contracts.h) |
| 18 | `LYRA_INTERFACE_PLUGIN_INVENTORY` | 固定结构 | [contracts.h](/downloads/sdk/include/plugin/contracts.h) |
| 19 | `LYRA_INTERFACE_CLIPBOARD` | 消息端点 | [clipboard_contracts.h](/downloads/sdk/include/plugin/clipboard_contracts.h) |
| 20 | `LYRA_INTERFACE_LINKS` | 消息端点 | [link_contracts.h](/downloads/sdk/include/plugin/link_contracts.h) |
| 21 | `LYRA_INTERFACE_PERSONAL_LIBRARY` | 消息端点 | [personal_contracts.h](/downloads/sdk/include/plugin/personal_contracts.h) |
| 22 | `LYRA_INTERFACE_LISTENING_HISTORY` | 消息端点 | [listening_contracts.h](/downloads/sdk/include/plugin/listening_contracts.h) |
| 23 | `LYRA_INTERFACE_AUDIO_TRANSITION` | 消息端点 | [transition_contracts.h](/downloads/sdk/include/plugin/transition_contracts.h) |
| 24 | `LYRA_INTERFACE_STEM_ANALYSIS` | 消息端点 | [stem_contracts.h](/downloads/sdk/include/plugin/stem_contracts.h) |
| 25 | `LYRA_INTERFACE_FONT_MANAGER` | 消息端点 | [font_contracts.h](/downloads/sdk/include/plugin/font_contracts.h) |
| 26 | `LYRA_INTERFACE_SETTINGS_PAGE` | 消息端点 | [settings_contracts.h](/downloads/sdk/include/plugin/settings_contracts.h) |
| 27 | `LYRA_INTERFACE_MEDIA_ACTIONS` | 消息端点 | [media_actions_contracts.h](/downloads/sdk/include/plugin/media_actions_contracts.h) |
| 28 | `LYRA_INTERFACE_SERVICE_CALL` | 消息端点 | [service_call_contracts.h](/downloads/sdk/include/plugin/service_call_contracts.h) |
| 29 | `LYRA_INTERFACE_NAVIGATION` | 消息端点 | [navigation_contracts.h](/downloads/sdk/include/plugin/navigation_contracts.h) |
| 30 | `LYRA_INTERFACE_LYRIC_FORMAT` | 消息端点 | [lyric_format_contracts.h](/downloads/sdk/include/plugin/lyric_format_contracts.h) |

[入口与绘制声明](/downloads/sdk/include/plugin/lyra_plugin.h) · [消息结构](/downloads/sdk/include/plugin/message_contracts.h)
