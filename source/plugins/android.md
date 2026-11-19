# Android 平台契约

通过 `host->java_vm` 与 `host->android_context` 使用 JNI，context 是当前 Activity。非 Android 宿主可为空；不可把缺少 VM 当成“方法不存在”后尝试旧桥。

## 版本与声明

当前公开平台契约为 **IDL 9**，与插件 ABI 3 分开版本化。[完整方法、操作 ID 与 JNI descriptor](/reference/android-platform)由发布的 IDL 生成，[SDK ZIP](/downloads/lyra-plugin-sdk.zip)也包含原始 JSON。操作 ID 标识声明；JNI 仍按 IDL 的方法名和 descriptor 查找，不是把 ID 传给任意 Java 方法。

先取得 `lyraPlatformVersion()I` 并检查返回 9，再查找所需声明方法。版本不符、方法不存在或出现 JNI exception 时停止调用、报告能力不可用；没有旧版本回退，也不猜其他重载。宿主自身使用同一 IDL 生成 Java 接口、JNI 方法表和 R8 保留规则，并在绑定时验证完整声明。

```cpp
jclass type = env->GetObjectClass(activity);
jmethodID version = env->GetMethodID(type, "lyraPlatformVersion", "()I");
if (!version || env->ExceptionCheck()) { /* clear exception, unavailable */ }
else if (env->CallIntMethod(activity, version) != 9) { /* unsupported */ }
// After checking exceptions, resolve the exact declaration from IDL 9.
env->DeleteLocalRef(type);
```

## 线程与引用

插件自行管理线程附着与本地引用。不要跨帧保留无效 Activity 引用；长期工作只在合法宿主生命周期内使用受管理的引用，在卸载前取消并等待任务退出。窗口操作通过 Activity 的 UI-safe 门面执行，不直接在音频回调里调用平台。

方法 ID 属于 JavaVM 与定义该方法的 class/classloader。不能把第一次取得的 ID 无条件用于另一 VM 或不同 Activity 类。宿主缓存使用 VM + class 弱引用，不持有 Activity；类失效后重新验证版本和声明。

## 数据与 fd 所有权

`takePluginFd()` 返回 -1 未选、-2 失败，非负 fd 转移给调用方，使用完关闭。`extractMotionArtwork(III)I` 的输入和输出 fd 是借用，不能按转移 fd 处理。字符串/Bitmap 是 JNI 引用，需要按 JNI 规则释放；宿主内部光栅桥不是插件可访问的 Activity 成员。

网络请求由 request/poll/cancel 三步组成，卸载前取消未完成任务；没有结果与失败状态要按对应 API 的返回协议处理，不模拟成功。

## 权限与可达性

“知道路径”不等于“有读取授权”。Android 版本、MediaStore、私有目录和用户授权决定外部封面及侧车可达性。插件无法新增宿主清单未声明的权限，方法调用以公开 Activity 接口为准。使用已发布的 IDL、公开媒体接口或自己的原生能力。
