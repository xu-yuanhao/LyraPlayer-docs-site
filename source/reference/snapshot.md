# SDK 版本与兼容性

| 项目 | 当前版本 |
| --- | --- |
| 插件 ABI | 3 |
| 公共接口版本 | 3，接口单独声明时按其版本查询 |
| Android 平台 IDL | 9 |
| Android 目标 | arm64-v8a，API 26 起 |
| 宿主验证包 | Lyra Player20261119225625 |

查询接口时传入 ID、该接口的版本及精确 `sizeof`。返回 NULL 表示该能力不可用。结构输入和输出都填写头文件规定的 `size`。同为 ABI 3 的宿主可以支持不同的可选接口，以运行时查询为准。

[SDK ZIP](/downloads/lyra-plugin-sdk.zip) · [文件摘要](/downloads/manifest.json) · [接口目录](/reference/abi)
