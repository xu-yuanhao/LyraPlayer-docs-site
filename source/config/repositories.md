# 插件源配置

默认 `[plugin_repository]` 指定同一签名信任组的镜像，源 URL 使用 `|` 分隔。public\_key 是 Base64 SPKI DER 的 P-256 公钥。只换 sources 不换正确公钥无法接受其他签名源。

```toml
[plugin_repository]
sources = "https://your-host.example/catalog/index.json|https://your-mirror.example/catalog/index.json"
public_key = "你的真实 SPKI DER Base64 公钥"
```

这是格式示意，不是可直接使用的地址与公钥。签名文件及 URL 派生约定以当前仓库服务为准；不要把 HTML 网页地址当原始 JSON 索引。

## 预算与排序

index/archive 字节限制、timeout、maximum\_rows 和 exact/prefix/substring/description 权重都有配置。见[完整默认值](/config/reference/ui-plugin_repository)。扩大预算不等于放开 ZIP 安全检查或解除 Android 权限。

## 当前实现与扩展

没有单独的源编辑 UI，但配置可编辑。多个不互信的源需要独立验证和合并策略，不把不同公钥目录塞入同一字符串就声称支持多信任组。

plugin-catalog 负责验证目录与安装状态，plugin-search 可替换搜索/排序，plugin-market 可替换呈现。接口见[API](/plugins/interfaces)。默认本地混排音乐与插件，不上传音乐目录或查询词。

进入市场自动刷新并保留可用旧列表；失败不接受未经验证数据。安装、更新、卸载为单个右侧按钮，详情由左侧区域进入。
