# 设置页与消息端点

## 同步调用（28）

拿到 [服务上下文](/plugins/service-context) 的句柄后，查询宿主 `LYRA_INTERFACE_SERVICE_CALL`（版本 3，`sizeof(LyraServiceCallV3)`），用 `lyra_service_call` 发出带接口 ID 的消息。注册器只访问选中实现。此操作在宿主帧线程同步完成，嵌套消息和字段指针在本进程调用期间有效。回复需要跨调用使用时立即复制。

消息声明操作、字段类型和容量。未知可选字段可忽略，未知必需字段及重复字段应拒绝。I64、F64 和 HANDLE 使用 8 字节，普通 UTF8 消息按端点约定包含结尾 NUL。通用请求最多 64 个字段、1 MiB。状态值和字段校验见 [message_contracts.h](/downloads/sdk/include/plugin/message_contracts.h)。

## 设置页（26）

任意选中服务可提供 `LyraSettingsPageV3`，宿主枚举接口并创建设置入口。

| 操作 | 用法 |
| --- | --- |
| INFO | 返回页面标题、入口名、行数、页号与修订号。可带确认提示和通知。 |
| ROW | 按 INDEX 提供标题、详情、按钮文字、标志及滑块参数。 |
| OPEN / BACK | OPEN 回到插件首页。BACK 先取消当前确认，再回上一页，首页可返回 UNSUPPORTED。 |
| ACTIVATE | 对 INDEX 执行操作，可带 SECONDARY 或 VALUE。 |
| CONFIRM | 以 ACCEPT 确认或取消。 |
| HOST_CAPABILITIES | 查询宿主支持的行类型。 |

`INFO.ENTRY_PARENT` 省略时在设置首页。可用的现有父页为 `settings.scan`、`settings.lyrics`、`settings.transitions`、`settings.haptics`、`settings.visualization`。未知父页不显示入口。插件负责校验、状态变更和持久化，宿主负责列表、滑块和确认交互。

## 媒体操作（21、22、27）

- **21 个人资料库**：ADD 接受本地 TRACK，或由 PROVIDER 与 UID 组成的来源引用。两种写法互斥。LIST 可能返回数字字符串或 provider/uid 对象。根级 provider 仅解释该快照中的数字简写。
- **22 听歌记录**：按头文件查询记录与汇总，检查回复字段类型。睡眠计时是同一接口的独立操作。
- **27 队列动作**：APPEND 或 NEXT 接受当前媒体上下文的 COLLECTION 和 ROW。接收成功后宿主复制条目数据。重复曲目可有独立队列条目。请求 ID、行号及队列条目 ID 不适合作为跨进程标识。

## 其他消息能力

[剪贴板 19](/plugins/clipboard)、[链接 20](/plugins/links)、[音频过渡 23](/downloads/sdk/include/plugin/transition_contracts.h)、[分轨分析 24](/downloads/sdk/include/plugin/stem_contracts.h)、[字体 25](/downloads/sdk/include/plugin/font_contracts.h) 各自定义操作和标签。先按实际端点查询，再根据返回结果启用功能。[接口总表](/reference/abi)
