# 常用配置配方

每段是覆盖片段。合并进已有表，别覆盖用户整份文件。改变后在当前设备验证文字、边界和交互。

## 歌词字号

```toml
[player]
lyric_main_mini_sp = 22
lyric_main_expanded_sp = 36
lyric_translation_mini_sp = 17
lyric_translation_expanded_sp = 21
lyric_phonetic_sp = 14
```

单位 sp，与系统 fontScale 有关。只改字体大小不等于自定义歌词 parser 或改变逐字时间。

## 相对拖动

```toml
[player]
progress_relative_drag = true
```

按下保留原位置，按手指距离移动；轻点不跳转。false 恢复绝对点击定位。

## 深浅色与中性控件

```toml
[theme]
follow_system = true
```

只影响首页卡片背后的统一底层和抽屉，播放卡片不消费系统主题。颜色、染色比例、时长及 action/ink 见[theme 参考](/config/reference/ui-theme)。不要给每个面板重新起一个渐变造成割裂。

## 隐藏状态栏与圆角来源

```toml
[system]
hide_status_bar = true
[shell]
corner_follows_device = false
```

关闭圆角跟随后使用 `shell.corner_radius_dp`。系统安全区仍是平台数据，不是简单把高度设 0。

## 动态封面

```toml
[artwork]
enabled = true
prefer_embedded = true
```

其余 embedded/sidecars/directories/预算见[artwork 参考](/config/reference/ui-artwork)。这些开关不自动授予外部存储读取权限，不把静态图片识别成视频。

## 用户文案

在 zh-Hans.toml 合并：

```toml
[text]
settings_title = "设置"
```

字符串是 UTF-8。不要把可见文字写回 C++ 绘制函数。

## 字体限制

公开绘制接口支持字体族或可读字体文件路径；当前默认全局配置没有 font.family 这样的已实现键。若需要全局字体选择功能，先新增声明与消费路径或开发对应 UI 插件，见[样式与字体](/plugins/styles)。
