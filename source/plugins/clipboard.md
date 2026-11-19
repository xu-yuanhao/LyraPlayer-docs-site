# 剪贴板消息接口

基准宿主 `a278b9d` 提供可替换能力 `system.clipboard`，接口 ID **19**，版本 **3**。它使用当前消息信封；宿主不增加专用字段。复制能力可由插件复用。设置中的开发者文档入口现在通过[系统网页接口](/plugins/links)打开 `plugin_settings.docs_url`，不显示网址。

## 发现与调用

插件初始化时通过 `LyraServiceContextV3.lookup` 获取能力句柄，保存句柄。每次操作时通过 `context->interface` 获取所选实现，调用结束后不保留接口指针。能力缺失或接口为空表示当前宿主未提供此能力。

```c
#include "plugin/lyra_plugin.h"
#include "plugin/clipboard_contracts.h"
#include "plugin/service_contracts.h"

/* context 和 clipboard_handle 在初始化时取得。 */
static int copy_text(const LyraServiceContextV3 *context,
                     uint64_t clipboard_handle, const char *text,
                     uint32_t bytes) {
    const LyraClipboardInterfaceV3 *api = context->interface(
        context->user, clipboard_handle, LYRA_SERVICE_SELECTED,
        LYRA_INTERFACE_CLIPBOARD, LYRA_INTERFACE_VERSION,
        sizeof(LyraClipboardInterfaceV3));
    if (!api || api->size != sizeof(*api) ||
        api->version != LYRA_INTERFACE_VERSION || !api->request)
        return LYRA_MESSAGE_UNSUPPORTED;
    LyraFieldV3 field = {LYRA_CLIPBOARD_TEXT, LYRA_FIELD_UTF8,
                        LYRA_FIELD_REQUIRED, bytes, text};
    LyraMessageV3 message = {sizeof(message), 1,
                            LYRA_CLIPBOARD_COPY, &field};
    LyraReplyV3 reply = {sizeof(reply), 0, 0, 0, 0};
    return api->request(api->user, &message, &reply);
}
```

操作 `LYRA_CLIPBOARD_COPY` 为 **1**，复制纯文本；不执行网址，也不打开外部应用。`TEXT` 标签 **1** 必需；`LABEL` 标签 **2** 可选。两者类型均为 `LYRA_FIELD_UTF8`，`bytes` 为 UTF-8 字节数，不含结尾 NUL。缓冲只在调用期间借用，实现必须同步复制数据，不保留调用者指针。

返回值同时写入 `reply.status`，不返回字段：`OK` 为 0，`INVALID` 为 -1，`UNSUPPORTED` 为 -2。未知必需字段返回 `UNSUPPORTED`；未知可选字段忽略。重复标签、缺少 TEXT、非法消息或回复 size 返回 `INVALID`。

接口 size/version 必须精确匹配。须在宿主帧线程和有效 Activity 生命周期内调用。平台没有实现时返回 `UNSUPPORTED`。Android 使用系统剪贴板，支持完整 UTF-8 文本。

## 提供替代实现

原生插件声明 `kind = "system.clipboard"`，通过 `query_interface` 返回 ID 19 的 `LyraClipboardInterfaceV3`。提供者自行拥有 `user` 和回调状态；仅接受当前接口版本与精确 size。插件可替换该能力，无需了解宿主实现。

## 菜单与集合播放配置

队列播放模式栏位于队列页底部。艺术家、专辑和个人分类的标题/封面点击或长按打开模式菜单，右侧箭头保留折叠操作。选择模式后，播放队列的范围为该集合。

模式菜单复用 `sheet.menu_radius_dp`、`sheet.menu_surface` 与 `shell.frost_blur_dp`、`shell.frost_wash`。原先用于队列页顶部过渡的 `sheet.frost_to_surface` 已移除，不提供旧键迁移。默认配置以站点配置参考为准。

底部模式栏留白由 `sheet.bar_padding_dp` 控制；集合长按阈值为 `player.group_long_press_ms`。按住期间使用手势时钟计时，达到阈值立即弹出；移动或取消会终止长按。
