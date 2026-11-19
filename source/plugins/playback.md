# 实现播放提供者

这是难度最高的扩展边界。官方 FFmpeg 插件可作完整参考；mock\_provider 只模拟状态，没有音频，不能当作播放器发布。

替换 `playback` 服务并发布 `LYRA_INTERFACE_PLAYBACK_PROVIDER`。不要链接宿主隐藏 C++ 符号，不增加第二套 App 播放状态；公开交互使用 C ABI。

## 必要回调

| 回调 | 行为 |
| --- | --- |
| snapshot | 输出按值快照，支持并发安全读取 |
| command | 接受 OPEN/STOP/PAUSE/RESUME/SEEK/PRIME/CLEAR\_PRIME/REAP/REMEMBER |
| listener | 注册事件回调，不保留进度快照指针 |
| quiesce | 所有线程/回调退出后返回 1 |
| lyrics | 按 generation/track 读取有界嵌入歌词 |

OPEN 被接受后接管 fd。拒绝保持未消费；所有后续关闭只做一次。清理顺序不能让线程读取已关闭 fd 或已释放 decoder。

## 主时钟

position\_us 必须由实际输出位置推导，包含解码起点、seek 时间重定位、采样帧、暂停冻结和系统输出时间戳的处理。不是解码到哪就报告到哪。UI 通过本帧统一快照消费位置。

seek 请求时先标 seeking，落地时改变 origin/revision、landed\_seek，并清理旧 PCM 和特征。连续 seek 以 serial 区分，不能让先发但晚完成的结果覆盖新目标。generation 隔离换歌与提供者更换；音频特征使用同一输出时间轴和 feature\_epoch。

## 事件

0 EOF、1 播放失败、2 实际音频进度、3 seek 失败。事件带 generation，进度可带只在调用期间借用的值快照。进度记忆使用实际输出位置，不能保存 UI 拖动预览。

不要在 AAudio 实时回调执行插件注册、网络、绘制或磁盘写入。恢复缓冲、解码、特征分析和保存分别有明确线程与缓冲所有权。

## 切换

宿主记录实际位置和暂停状态，阻止新读调用，等待正在读的调用，STOP，再等待 quiesce。安全退出后解除旧 listener、增加 generation 并绑定新提供者。拒绝退出会保留旧库。

手机测试锁屏、长后台、焦点打断、耳机/蓝牙变更、暂停/恢复、连续 seek、连续换歌与卸载。静音生命周期测试只证明控制与资源边界，不证明音质或输出延迟。

[官方插件源码](https://github.com/xu-yuanhao/LyraPlayer-plugins/tree/main/plugins/ffmpeg)。格式能力取决于系统解码器或插件，不承诺默认设备原生支持所有格式。
