# 样式与绘制教程

使用 `examples/style.c`。插件在 query\_interface 发布 `LyraStylesInterfaceV3`，count 返回描述数，describe 填写 `LyraStyleDescriptionV3`。

```c
static const LyraStylesInterfaceV3 styles = {
    sizeof(styles), LYRA_INTERFACE_VERSION, 0, count, describe
};
```

一个不同 id 添加一种样式；相同 id 可替换内置描述。使用稳定、带命名空间的 id，例如 `example.third`，不要每次版本更新更名。

## 默认背景或整卡片绘制

`background_variant` 选择已有背景变体。非 NULL paint 回调替换整张播放卡片呈现，收到样式选择器计算的 x/y/w/h；通过 submit 画在同一坐标。需要显示歌词、控件或播放信息时，从 SDK 读取数据并绘制。

input 处理该样式的输入；返回 0 让未消费事件继续进入默认导航。选择器打开期间输入由选择器处理，不自行绕过选择器命中。

## Scene 协议

基础命令包括实色、封面、图标、短雾、流动背景、glyph、RGBA image。扩展文字层提供 tracking、词间距、方向、对齐、裁剪、模糊、扫光、变换中心与缩放；形状层提供渐变与边缘材质。具体字段以[SDK](/reference/abi)为准。

颜色为浮点 RGBA，几何为当前传入的像素坐标；dp 通过 density 换算，sp 还需字体缩放策略。不要混用 normalized ripple 中心与像素位置。

图标图集只含上一首、播放、暂停、下一首，不含启动三叶 Logo。封面 key 与资料库标志不能随意混用；插件应查询目录和有效图像语义而不是猜编码。

## 文字和字体

glyph/text layer 接受 UTF-8 text 和 font。当前 Android 后端支持系统字体族名，绝对路径字体由 Typeface.createFromFile 读取，失败回退 sans-serif。字体文件必须在应用可访问路径；自定义 `.ttf/.otf` 不因为放 ZIP 里就自动切换全站字体。

默认字号由 `[player]` 等表控制；当前没有承诺一个默认全局 font 配置键。完整字体选择 UI 或默认全局字体功能需要新增配置及消费路径，或由自定义 UI 插件实现。不要发明不存在的 `font.family` 键。

## 生命周期验收

验证选择、缩放、切歌、暂停、横竖窗口变化、输入消费、卸载与缺失接口回退。不要在每个稳定帧分配新大数组；声明被宿主复制不意味着 paint 持有图像可以立即释放。
