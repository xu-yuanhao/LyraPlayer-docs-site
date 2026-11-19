# 编译第一个插件

[下载并解压 SDK](/downloads/lyra-plugin-sdk.zip)。在解压目录运行以下命令，`ANDROID_NDK_HOME` 指向已安装的 NDK。示例目标为 `arm64-v8a`、API 26。

```sh
export ANDROID_NDK_HOME="$ANDROID_HOME/ndk/28.2.13676358"
bash examples/build.sh
```

脚本生成 `out/example.style.zip`、`out/example.rules.zip` 和 `out/example.root.zip`。先在 Lyra Player 的设置页选择「安装插件」导入样式包，在样式选择器验收，然后从插件列表卸载。

## 入口与清单

插件导出 `lyra_plugin_init`。入口校验 `host->abi` 与 `host->size`，清零并填写 `LyraPluginV3`，返回 0。C++ 使用 `extern "C"` 导出，跨库结构以 C 头文件为准。清单的 `id`、`type` 须与入口的 `id`、`kind` 相符。

```toml
id = "example.style"
version = "1.0"
abi = 3
type = "style"
entry = "plugin.so"
```

把 `manifest.toml` 和 `plugin.so` 置于 ZIP 根目录。[完整清单](/plugins/manifest) · [排错](/plugins/troubleshooting)

## 测试根替换

`example.root` 替换完整画面和触摸。它可能遮住默认插件列表，测试前准备可用的恢复方式。正式包通常无法使用 `run-as`，请在可访问插件目录的测试环境验证。需要保留默认界面时，按[服务上下文](/plugins/service-context)显式委托默认根，并按[返回键协议](/plugins/presentation)处理 Back。

[root.c](/downloads/examples/root.c) · [style.c](/downloads/examples/style.c) · [rules.c](/downloads/examples/rules.c)
