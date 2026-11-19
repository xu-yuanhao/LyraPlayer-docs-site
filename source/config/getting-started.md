# 配置入门

默认配置打进 APK，用户覆盖文件只需写要改变的键。参数在 ui.toml，文案在 zh-Hans.toml。用[全部配置表](/config/reference/)查当前字段，不从旧截图猜名称。

## 文件位置

宿主取 Android external files root，缺失时用 internal files root，再拼接 `lyra/config`。常见外部位置：

```text
/storage/emulated/0/Android/data/com.petehsu.lyraplayer/files/lyra/config/
  ui.toml
  zh-Hans.toml
```

内部通常是 `/data/user/0/com.petehsu.lyraplayer/files/lyra/config/`。实际根由系统提供，存储卷和 Android 版本会改变访问方式。以日志 `config dir ...` 确认。普通文件管理器可能无权访问 Android/data，正式 APK 的 run-as 不保证可用。

每个文件优先读取外部非空覆盖，外部为空/不存在才读内部；不是把外部与内部逐键再叠加。覆盖在内置 defaults 之上，类型必须一致。

## 改字号与交互

创建或合并到用户 ui.toml：

```toml
[player]
lyric_main_mini_sp = 22
lyric_main_expanded_sp = 36
progress_relative_drag = true
```

这个文件不用复制其他数百个默认键。保留已有配置，避免一个示例覆盖用户其他设置。不要在同一文件重复 `[player]`/同一键，使用编辑器定位现有表修改。

## 生效与恢复

文件监听在安全帧边界请求重新加载；接口写入同样下一帧激活。无效类型/范围不应当作有效配置使用。启动可能使用安全默认回退，运行时失败保留可用状态；不能因此认定坏文件被自动修复。

恢复时先备份覆盖文件，再删除有问题的键或整份覆盖，让默认值生效。不是删除 APK 里的 assets。通过公开配置接口写入可以获得校验和持久化，见[schema](/plugins/config-schema)。

下一步：[语法](/config/syntax)与[常用配方](/config/recipes)。
