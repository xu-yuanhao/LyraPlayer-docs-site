# zh-Hans.toml · plugin\_settings

此表控制对应默认组件的布局、行为或界面文案。

根据公开默认配置生成。只覆盖需要的键，类型与默认值一致。完整约束通过宿主配置接口校验；替换服务可能不消费这些默认键。

## plugin\_settings.builtin

类型：字符串。

```toml
[plugin_settings]
builtin = "内置插件"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.external

类型：字符串。

```toml
[plugin_settings]
external = "外部插件"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.install

类型：字符串。

```toml
[plugin_settings]
install = "安装插件"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.progress\_relative

类型：字符串。

```toml
[plugin_settings]
progress_relative = "点击进度条不跳转"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.hide\_status

类型：字符串。

```toml
[plugin_settings]
hide_status = "隐藏状态栏"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.hide\_navigation

类型：字符串。

```toml
[plugin_settings]
hide_navigation = "隐藏导航栏"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.artwork\_motion

类型：字符串。

```toml
[plugin_settings]
artwork_motion = "动态封面"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.artwork\_prefer

类型：字符串。

```toml
[plugin_settings]
artwork_prefer = "优先内嵌封面"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.artwork\_embedded\_first

类型：字符串。

```toml
[plugin_settings]
artwork_embedded_first = "内嵌优先"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.artwork\_sidecar\_first

类型：字符串。

```toml
[plugin_settings]
artwork_sidecar_first = "外置优先"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.install\_hint

类型：字符串。

```toml
[plugin_settings]
install_hint = "选择 ZIP 插件包"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.empty

类型：字符串。

```toml
[plugin_settings]
empty = "暂无外部插件"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.active

类型：字符串。

```toml
[plugin_settings]
active = "已启用"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.inactive

类型：字符串。

```toml
[plugin_settings]
inactive = "未启用"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.overridden

类型：字符串。

```toml
[plugin_settings]
overridden = "已被外部插件替换"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.unsupported

类型：字符串。

```toml
[plugin_settings]
unsupported = "不支持，请重新编译（ABI 2）"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.installing

类型：字符串。

```toml
[plugin_settings]
installing = "正在安装插件"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.installed

类型：字符串。

```toml
[plugin_settings]
installed = "插件已安装"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.invalid

类型：字符串。

```toml
[plugin_settings]
invalid = "插件包无效，请选择含 manifest.toml 和 arm64 插件的 ZIP"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.exists

类型：字符串。

```toml
[plugin_settings]
exists = "该插件已安装"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.io\_error

类型：字符串。

```toml
[plugin_settings]
io_error = "无法读取或保存插件包"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.write\_error

类型：字符串。

```toml
[plugin_settings]
write_error = "无法保存设置"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.back

类型：字符串。

```toml
[plugin_settings]
back = "‹"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.forward

类型：字符串。

```toml
[plugin_settings]
forward = "›"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.about

类型：字符串。

```toml
[plugin_settings]
about = "关于"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.docs

类型：字符串。

```toml
[plugin_settings]
docs = "开发者文档"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。

## plugin\_settings.docs\_url

类型：字符串。

```toml
[plugin_settings]
docs_url = "https://xu-yuanhao.github.io/LyraPlayer-docs-site/"
```

来自[公开默认配置](/downloads/reference-data/zh-Hans.toml)。[类型与校验说明](/config/validation)。
