# 插件编译环境

- Android NDK，目标 `aarch64-linux-android26`。
- [SDK ZIP](/downloads/lyra-plugin-sdk.zip) 中的 `include/` 和 `examples/`。
- 一台装有对应宿主版本的 arm64 Android 设备。

```sh
"$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android26-clang" \
  -std=c11 -Oz -fPIC -fvisibility=hidden -shared \
  -I include plugin.c -o plugin.so
```

使用 C++ 时改用 `clang++`，将入口声明为 `extern "C"`，保持结构和回调与 SDK 一致。检查 `llvm-readelf -h -d --dyn-syms plugin.so`，确认 AArch64、依赖库可解析，入口符号 `lyra_plugin_init` 可见。配有非公开依赖的插件要在 Android 8 和目标设备上验证加载。

[编译与安装示例](/plugins/first-plugin) · [测试表](/developers/testing)
