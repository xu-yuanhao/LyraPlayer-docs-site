# 流派、文件夹与语言规则

个人页只显示曲库确实拥有的分类，分组复用现有封面与折叠样式。

## 流派

`profile.genre_rules` 为换行分隔的规则，每行 `展示名=alias|alias`。大小写/空格/连字符规范化按当前本地规则处理。`genre_numbers` 是有顺序的 ID3 数字标签映射；改顺序会改变数字标签含义，不能随便排序。

```toml
[profile]
genre_rules = "Rock=rock|摇滚\nJazz=jazz|爵士"
```

这是用两条规则替换整份字符串，不是在默认大列表上自动追加。要保留全量默认别名，应先从[完整 profile 默认值](/config/reference/ui-profile)复制并增补。未知用户标签保留原文，不从歌名猜流派。

## 文件夹

按存储卷与完整位置分组；同名但不同位置的目录不合并。展示 basename 与完整路径。unknown\_folder 只决定无法取得目录时的标签，不伪造目录来源。

## 语言

language\_scripts 按字母范围识别，language\_words 提供词表，language\_labels 决定显示标签。word\_weight、minimum\_word\_score、script\_fraction、kana\_priority 控制本地规则。拉丁共享字母、罗马字、短标题和混合语言存在歧义，应回退未知。

优先歌词正文，忽略译文/注音；没有可读歌词再用歌名。有歌词但不能识别时不强制标题结论。侧车后缀和读取预算可配，Android 不可读文件不会当作已经读取。

后台索引批次完成后发布语言样本与分组，避免把一半索引状态当完整语言目录。外部源可提供可选 catalog 字段，也可替换 classification rules。

显示类目文案在 `[profile_copy]`，规则标签与未知标签在 `[profile]`，两者别混放。
