# Host 与绘制提交参考

先校验 Host 的 `size` 和 `abi`。调用回调时传入对应的 `user` 指针。

| 字段/回调 | 含义 |
| --- | --- |
| `log` | 诊断文本；不输出用户歌词与秘密 |
| `request_frame` | 请求下一帧，动画或异步结果完成后调用 |
| `now_ns` | 单调纳秒，不是音乐进度 |
| `density` | dp 到像素密度；不是完整字体缩放策略 |
| `submit` | 提交 Scene，命令/文本被复制，image 像素借用至帧结束 |
| `layer` | 声明服务命中层及 z、几何区域 |
| `config_text` | 读已声明配置表，非完整 UI 状态对象 |
| `request_permission` | 请求宿主已声明的权限 |
| `set_panes` | 根/导航实现发布面板几何 |
| `acquire_surface` | 平台表面能力；返回值依平台，不是通用 GLES 句柄 |
| `section` | 当前可查询区域的几何；未知能力失败 |
| `listen` | 接收区域/事件回调，遵守服务卸载寿命 |
| `java_vm` / `android_context` | Android 扩展；其他平台可能为空 |
| `query_interface` | 查询版本与结构大小匹配的能力 |

权限状态：GRANTED=0、DENIED=1、UNDECLARED=2、UNAVAILABLE=3。未在宿主 Android 清单声明的权限不能靠运行时请求获得。

## Scene 与命中

所有 count 对应真实数组容量，size 设为 sizeof。基本形状/glyph 几何为像素，ripple 中心为归一化卡片坐标。不要提交悬空 text、无效 image 尺寸或伪造 cover key。

Scene 必须使用当前完整布局并设置 size=sizeof(LyraSceneV3)。基础文字与扩展文字层按各自结构提交。当前默认实现每次最多 4096 个扩展层，插件应在可见区域内生成命令并复用缓冲。自定义输入使用 LyraInput DOWN=0、UP=1、MOVE=2、CANCEL=3；取消不应当作点击确认。

根替换负责发布自己的布局并接管输入。局部替换只负责自己被路由的区域；不要绘制默认结果之后再遮盖当作真正替换。

[完整 SDK 声明](/reference/abi) · [接口查询](/plugins/interfaces) · [生命周期](/plugins/lifecycle)

新增可选业务字段使用服务上下文的标签消息协议，当前结构保持完整布局检查，不添加旧布局读取分支。
