# 发布插件与维护仓库

官方插件仓库结构

```text
LyraPlayer-plugins/
  sdk/include/plugin/
  plugins/<name>/
    manifest.toml
    catalog.json
    README.md
    CHANGELOG.md
    icon.png
    build.sh
    src/
    licenses/
  catalog/index.json
  catalog/index.sig
  scripts/catalog.py
  scripts/sync.sh
  dist/  # ignored：包与对应源码附件
```

GitHub 主仓库：[LyraPlayer-plugins](https://github.com/xu-yuanhao/LyraPlayer-plugins)。GitLab 镜像：[lyraplayer-plugins](https://gitlab.com/x13102306563/lyraplayer-plugins)。它们使用相同提交和发布字节，但 Git 同步不自动同步 Release 附件。

## 目录描述

catalog.json 包括 id/title/version/abi/platform/arch/capability/description/tags/author/author\_url/homepage/license/icon/readme/changelog/entry/config，以及发布输入 package 和镜像 urls。

package 只是 dist 下的产物文件名；脚本读取实际 ZIP 计算 bytes 和 SHA-256。不要手填伪造大小或摘要。README/CHANGELOG 的同目录文件内容与 PNG/WebP 图标进入签名索引，原文件同时随包保留。

签名索引根结构为 `schema: 1` 与 plugins 数组；schema 是索引格式版本，不是插件 ABI。没有构建产物时目录生成会失败，先构建后更新目录。

```sh
# 在官方插件仓库执行，需有本机授权的目录签名私钥。
plugins/ffmpeg/build.sh
python3 scripts/catalog.py
```

产物文件名和版本从当前清单与构建输出取得。

## 发布顺序

构建与测试 → 整理许可证及可重建源码 → 在两端上传相同包/对应源码附件 → 核对匿名下载大小与 SHA-256 → 填 urls → 生成并签名索引 → 同步 Git 与索引 → 用设备刷新并验证安装/更新/卸载。

不要先发布指向不存在文件的新索引。GitLab Generic Package 和 GitHub Release 应是字节一致的镜像；版本比较支持数值段和 SemVer prerelease，不猜未知格式，不降级。

第三方源可按同一协议提供索引与包，但默认源信任官方公钥。向官方目录贡献插件不代表自动获取官方私钥，需维护者审查并发布。
