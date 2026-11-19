# 新增播放模式与真实顺序

使用 `examples/rules.c`，它发布 LyraPlaybackRulesV3、可选 modes 以及一个“记录导航历史”的可调开关。已有四个模式 ID 0..3 保留；自定义模式用 >=4 的稳定 ID。

## 声明模式

modes.describe 输出 size、id 和 UTF-8 label。label 容量 128 字节，模式 ID 不能重复。当前默认菜单最多 64 项且可滚动；这属于默认 UI 容量，插件可替换 UI 实现自己的菜单。

`sheet.mode` 保存模式 ID，不是菜单行号。卸载提供者时回退实际规则，但不删除用户保存 ID。查询规则接口时校验完整结构大小。使用 `modes` 前检查指针。

## 两个必须一致的函数

next 接收 mode、count、current、delta、automatic 和单调时间熵，返回目录 row 或 -1 停止，以及是否记录历史。order 返回真实队列目录索引和当前队列行。

只改 next、不改 order，会让播放顺序页显示错误；只改 order、不改 next，会让页面和实际切歌分裂。返回行必须有效，总数不能超过缓冲容量；空目录要安全失败。

非自定义模式可以委托已查询的默认 rules 接口；不要调用自己的活动接口形成递归。每个模式的手动 previous/next 与自动 EOF 边界应明确定义。

## 参数与顺序分离

示例反向列表按每次一首导航，order 按相同反向顺序提供全部歌曲。`example.remember_history` 只控制返回的 remember 标志，不改变队列顺序，避免参数变化导致 next 与 order 分裂。默认 true；可在配置中改为 false。

## 必测场景

空曲库、单首、第一首 previous、最后一首 next、自动 EOF、连续切歌、seek 到末尾、模式切换、目录修改与插件卸载恢复。播放命令不能自动关闭用户正在看的抽屉或歌词页。
