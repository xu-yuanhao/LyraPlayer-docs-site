# 清单、元数据与包格式

ZIP 根或一层目录包含 `manifest.toml` 和同级 `plugin.so`。导入后目录名必须匹配 id。不要依赖 ZIP 内绝对路径、`..`、软链接或多个任意层级找到入口。

```toml
id = "example.style"
version = "1.0.0"
abi = 3
type = "style"
entry = "plugin.so"
config = "example"
title = "我的播放样式"
author = "你的名字"
license = "你实际选择的许可证"
icon = "icon.png"
readme = "README.md"
changelog = "CHANGELOG.md"
```

上面的 license 是示意，发布前换成真实声明。id、version、abi、type、entry 必填；config 是可选表声明。入口仅为文件名，不能有路径分隔符；当前加载器 capability 字符串需小于 24 字节、ID 小于 64 字节。当前 SDK 使用 ABI 3。

## 全部展示字段

| 字段 | 内容 |
| --- | --- |
| `title` | 展示名称 |
| `description` | 简短说明 |
| `author` | 作者/维护者 |
| `author_url` | 作者主页 |
| `homepage` | 项目主页 |
| `license` | 包含的真实许可证声明 |
| `icon` | 包内 PNG/WebP 文件 |
| `readme` | 包内 Markdown 文件 |
| `changelog` | 包内更新说明 |
| `tags` | 检索标签文本 |
| `platform` | 当前如 android |
| `arch` | 当前如 arm64-v8a |

这些字段可以放 manifest 字符串或 `metadata.json`。manifest 同名字段优先。`type` 对应目录 `capability`。旧 ABI/未启用插件的元数据仍可显示，不需执行插件代码读取详情。

## Markdown 与图标

Lyra App 中是有界 native 块解析，不是本网站的 Markdown 引擎：支持标题、段落、无序列表、引用、围栏代码和基本行内文本；保留链接文字及目标，不保证可点击导航。没有 HTML/脚本执行，不承诺表格、嵌套列表或行内混合字体。

建议 README 先说明功能、适用版本、是否替换现有服务、安装与恢复方法，再写权限、性能和许可证。图标使用真实品牌授权资源，原始 ≤96 KiB、解码 ≤1024×1024；官方发布工具把图标纳入签名索引，安装前无需额外图标网络请求。

## 安全导入

默认有界读取压缩包与解压内容，校验 CRC、路径、ELF 架构、ABI 和入口。具体预算见 `[plugin_install]`。本地重复 id 导入不会直接覆盖；市场更新是独立的用户动作和原子发布流程。

包校验不是原生代码安全分析。安装可信来源，阅读[信任边界](/plugins/security)。
