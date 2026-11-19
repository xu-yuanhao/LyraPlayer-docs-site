# 文档 MCP

远程 MCP URL 为 `https://lyra-player-docs-mcp.vercel.app/mcp`，使用 Streamable HTTP。

| 工具 | 用途 |
| --- | --- |
| `get_sdk` | 查询 MCP 当前的 SDK 版本与下载摘要 |
| `search_docs` / `read_doc` | 查找页面及读取正文 |
| `get_config` | 查询配置键的类型和默认值 |
| `list_services` | 列出服务与声明的配置表 |

MCP 服务独立部署。使用前对照[本站 SDK 清单](/downloads/manifest.json)核对版本和校验值。

```toml
[mcp_servers.lyra_docs]
url = "https://lyra-player-docs-mcp.vercel.app/mcp"
```
