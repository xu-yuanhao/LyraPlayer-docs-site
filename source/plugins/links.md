# 系统网页接口

宿主提供 `system.links`，接口 `LYRA_INTERFACE_LINKS` 的 ID 为 **20**，版本 **3**，声明位于 `plugin/link_contracts.h`。消息接口为精确的 size/version/user/request 布局，旧接口 ID 不复用。

初始化时通过 `LyraServiceContextV3.lookup` 缓存服务句柄。调用时使用 `context->interface(context->user, handle, LYRA_SERVICE_SELECTED, LYRA_INTERFACE_LINKS, LYRA_INTERFACE_VERSION, sizeof(LyraLinksInterfaceV3))` 获取当前实现；校验接口 size/version 和 request 后调用，不跨操作保留接口指针。

## 消息

操作 `LYRA_LINK_OPEN_WEB` 为 **1**，必需字段 `LYRA_LINK_URI` 为 **1**，类型 `LYRA_FIELD_UTF8`。bytes 为 UTF-8 字节数，不含结尾 NUL；数据只在调用期间借用。仅支持 http 和 https scheme，不接受组件名、Intent extras 或 JavaScript URL。

实现通过系统 ACTION\_VIEW 解析并打开网页。有默认浏览器时使用系统默认；未设默认项时由系统提供选择界面。宿主不会模拟系统提示。

成功为 `LYRA_MESSAGE_OK`，无平台实现、无适用应用或不支持的 scheme 返回 `LYRA_MESSAGE_UNSUPPORTED`；无 URI、重复 URI、空值、嵌入 NUL 或非法信封返回 `LYRA_MESSAGE_INVALID`。返回值同时写入 reply.status，不返回字段。未知必需字段拒绝，未知可选字段忽略。



设置中的开发者文档入口使用此能力。目标地址仍由 `plugin_settings.docs_url` 配置，入口文字由 `plugin_settings.docs` 配置。

在宿主帧线程调用，并确认当前 Activity 有效。`type = "system.links"` 的插件可以提供此端点，具体消息字段见[头文件](/downloads/sdk/include/plugin/link_contracts.h)。
