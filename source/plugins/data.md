# 目录、歌词与分类接口

媒体目录与歌词文档都是 revision 限定的数据，先读取版本和曲目标识，再读取当前范围。不要把目录行、曲目 ID 和队列行混为一谈。

## 媒体源

媒体源实现 `LyraMediaProviderV3`，处理 collection/search/audio/cover/lyrics 请求。通过 sink 发布 `LyraMediaDescriptorV3`，其中包含完整 UTF-8 标题、艺术家、专辑、流派、文件夹与资源位置。异步结果必须携带原请求 ID；取消或失效请求不能发布。

宿主 `LyraMediaContextV3` 提供提供者发现、集合读取、当前曲目与队列操作。数据按请求和 revision 读取；字符串在当前帧边界或 revision 变化前借用。不要把旧短记录或同步目录接口作为另一条数据路径。具体流程见[媒体请求接口](/plugins/media)。

## 歌词

LyraLyricsInterfaceV3 提供 revision、track\_id、count、line、word、text。line 的 flags bit0 为 RTL、bit1 为无时间轴。时间是微秒，word.units 是 UTF-16 单元，用于测量对齐，不是 UTF-8 字节数。

text kind：0 正文、1 译文、2 音标、3 和声、4 逐字文本、5 逐字音标；part 为和声/词索引。缓冲不足不写，返回含 NUL 所需长度。

调用者不能包含私有 `document.hpp`，也不能自行把文档工作线程指针送给渲染器。异步歌词结果必须匹配当前曲目和 generation。嵌入文本读入有预算，不读取字幕包、不解密 krc1、不记录正文日志。

## 分类

profile-classification 提供 LyraClassificationRulesV3。genres 返回换行分隔标签；language 接收正文、标题与 has\_lyrics；language\_label 负责显示标签。规则改变推进 revision。

默认流派来自真实标签，未知自定义标签保留原名；文件夹按完整位置区分。语言优先正文而不是译文/注音，只有无可读歌词才用歌名。有歌词但不足以识别时回退未知，不把短标题猜成准确语言。

默认识别是本地规则，不是全语言模型。外部插件可以替换分类策略，但应声明性能、网络与隐私行为；默认搜索和分类不会上传曲库或查询词。
