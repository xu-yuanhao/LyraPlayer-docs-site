# 服务上下文与默认组件复用

可选接口 16 `LYRA_INTERFACE_SERVICE_CONTEXT` 和 17 `LYRA_INTERFACE_PRESENTATION_CONTEXT` 为插件提供与默认组件相同的执行入口。先查询能力；当前接口缺失时返回 NULL，不能通过私有符号补上。

## 开放能力注册

count/at 枚举本实例的服务句柄，lookup 只解析名称；frame/input/supply/interface/request 均通过句柄执行。内置槽位不是公开能力目录，新能力不需要宿主增加枚举项。

插件可在初始化或自身回调中调用 publish，提供 LyraCapabilityV3 名称、user 和 request 回调。它只能发布新名称或更新自己发布的能力，不能覆盖别人的注册；失败初始化与模块卸载会撤销全部发布。user 仍由插件拥有，shutdown 前终止 worker；request 只在帧线程运行。查询 describe 的 REQUEST 标志可识别消息端点。

[完整可编译示例](/downloads/lyra-plugin-sdk.zip) 包含 examples/capability.c，发布 example.echo 与 example.other。其他插件用 lookup 取得句柄，再 request；没有宿主源码依赖。

## 标签字段扩展

LyraMessageV3 是固定的当前消息头，operation 由能力定义，fields 包含 tag/type/flags/bytes/data。新可选字段增加新 tag，不改变结构大小或 ABI；接收方使用 lyra\_message\_fields 校验自己的 schema，忽略未知可选字段，拒绝未知 REQUIRED 字段或类型错误。这里没有旧版本读取、旧结构前缀转换或并行协议。

字段类型包括 I64、F64、UTF8、BYTES、HANDLE；标量为 8 字节，UTF8 含末尾 NUL。单次消息最多 64 个字段、合计 1MiB，不允许重复 tag。调用方拥有 reply.fields 数组，capacity 表示可写数量；结果数据借用至该端点下一次调用，需跨调用保存时复制。回调不能更换调用方数组或扩大容量。无效请求返回 INVALID，未知操作/必需字段返回 UNSUPPORTED，容量不足返回 CAPACITY。

## 服务句柄

通过 lookup(capability) 获取本实例中的非零句柄；名称用于解析声明，不是全局对象地址。current() 返回当前服务回调的句柄，回调之外可能为 0。句柄只用于取得它的同一个上下文，服务被删除后应视为失效；不要跨宿主实例混用。

describe 输出先填写 size，成功返回 0，失效返回 -1。capability、selected\_id、default\_id 是借用字符串，更新或卸载前复制。flags 表示选中实现是否覆盖默认实现，以及它实际声明的 frame/input/supply 回调。FALLBACK\_FRAME 表示注册时声明了缺失绘制回调时的默认回退策略，不代表覆盖所有方法。

## 执行选中实现或默认实现

frame、input、supply、interface 均接受句柄和实现选择：LYRA\_SERVICE\_SELECTED 使用选中实现；LYRA\_SERVICE\_DEFAULT 直接复用宿主注册的默认实现。默认实现不存在、句柄过期或目标无效会返回错误或 NULL；没有对应回调则返回 0。supply 的返回值沿用对应服务协议，不能统一理解成字节数。

默认绘制不调用替换它的插件，也不会自动在插件结果上再叠加一层。插件决定是否调用、调用哪些默认组件。调用 frame 必须处于宿主绘制回调中；box 指定绘制层的 section/命中边界，并不自动重排默认组件内部布局。需要自己的布局时读取展示快照，提交自己的 Scene。

DEFAULT\_ACTIVE 表示本帧或紧邻上一帧执行过默认绘制。宿主据此保留相应默认文字与资源需求；复用默认根时也保持必要的帧请求。更换实现会清理执行参与状态。

## 根插件复用默认界面



```c
#include "plugin/lyra_plugin.h"

static int frame(const LyraHostV3 *host, int64_t now) {
    const LyraServiceContextV3 *api = host->query_interface(
        host->user, LYRA_INTERFACE_SERVICE_CONTEXT,
        LYRA_INTERFACE_VERSION, sizeof(LyraServiceContextV3));
    if (!api) return -1;
    uint64_t handle = api->current(api->user);
    if (!handle) return -1;
    return api->frame(api->user, handle, LYRA_SERVICE_DEFAULT, now, 0);
}
```

将此回调作为插件 on\_frame，清单 capability 为 frame。如要复用某个具体组件，可解析其公开 capability 后调用默认实现。默认绘制保持现有样式与动效；配置、媒体、歌词和播放规则仍通过各自公开接口修改。若复用组件的生命周期行为，应在插件 query\_interface 中用相同句柄、LYRA\_SERVICE\_DEFAULT 转发 interface 查询，例如播放观察者接口；不要只复用绘制而忽略组件声明的事件接口。

## 展示与资源

presentation.snapshot 输出按值快照：本帧时间、viewport、density、font scale、卡片/封面/标题/歌词/抽屉等矩形与主题 RGBA。先填 size，失败返回 -1；不要将布局时间作为第二个播放时钟，音乐位置仍读取 playback。

glyph(id) 读取缓存文字的宽高与 ready。image(key) 读取播放器封面或共享图片缓存的宽高、ready、RGBA 数据与字节数。图片 key 使用媒体描述的 cover\_key；不存在的资源返回 -1。RGBA 指针只借用到下一帧边界或缓存变化，工作线程使用前先复制，不要保存跨帧指针。glyph 不提供像素，rgba/bytes 为 NULL/0。

presentation.input(event, present) 可复用默认导航和交互；event 先填写 size。present 为非零时按即时呈现处理，历史移动采样可用 0。输入成功返回 1，调用方应避免再重复向默认交互发送同一事件。服务 input 的处理结果依各服务定义，0 表示未消费。

## 线程与生命周期

所有服务执行与展示读取都是帧线程接口，不能从音频实时回调或网络工作线程调用。worker 的异步数据使用 media 的 sink 和 query revision 接口，回到帧线程再操作界面。host/request context 属于当前宿主实例，不能保存当前绘制目标跨帧。

默认接口与资源仅在宿主有效期内借用。shutdown 返回前停止并等待全部 worker；服务上下文及展示转发在宿主脱离后会拒绝操作，其他借用的服务接口指针不得继续调用。支持的字段以 size/version 和实际回调为准。

## 句柄稳定性与撤销

句柄是 registry 内的 opaque capability identity，不是指针或永久 ID；0 表示不存在。默认能力在同名注册、refresh、外部覆盖与恢复时保持同一句柄，所以可缓存。动态能力没有默认实现，发布者/模块卸载会撤销句柄；同名能力重新发布得到新句柄，旧句柄永远不会指向新能力。未变化模块 refresh 保留句柄，枚举下标和顺序不稳定。

失效/0/已 detach 的句柄：describe、frame、input、supply 返回 -1，interface 返回 NULL；request 返回 UNSUPPORTED，detach 后为 INVALID。describe 要求 size==sizeof，合法大小输出在失败时清空 flags、handle 与字符串指针；错误大小的输出不修改。不要继续使用上次 describe 的结果。

描述字符串和接口指针只借用到下一次 registry mutation，不跨 refresh/unload 保存。Context 指针只在对应 registry 生命周期内有效，detach 的安全失败语义不允许在销毁之后继续调用。句柄不能混用于另一个宿主实例，也不能持久化到下次启动。访问在 registry owner/frame thread 完成，异步结果经公开媒体事务接口提交。

需要动态能力时，缓存句柄前理解其撤销边界；失效后按公开能力名重新 lookup，并重新 describe/interface。没有旧句柄适配。分配器耗尽时返回 0，不回绕或复用身份。

## 扩展纪律

业务扩展优先通过已经发布的 publish/request 消息通道，使用自己的能力名、operation 和带 tag 的字段。不要向 Host 添加某个插件专用的回调，也不要依赖宿主私有对象或改变已公布接口形状。需要宿主新增 C ABI 能力时由宿主发布新接口 ID 与契约，不能重用旧 ID 或在结构尾部自行塞字段。

size 必须等于对应完整结构的 sizeof；>= 或前缀读取都不是当前契约。平台 schema 版本与精确握手一起升级，不尝试旧 Java 重载。普通消息的可选 tag 字段是已经公布的扩展机制，不等于改接口结构。
