# 声明可编辑参数

任何活动服务都可以发布 `LyraConfigSchemaV3`，无需增加专门的配置插件。宿主复制 describe 的字符串，校验整批声明后激活。

| 字段 | 规则 |
| --- | --- |
| kind | 0 字符串、1 数字、2 布尔 |
| key | 稳定配置键，建议用插件命名空间 |
| default\_value | 可解析的 TOML scalar |
| flags | MINIMUM、MAXIMUM、INTEGER 按需组合 |
| minimum/maximum | 声明数字界限 |
| schema\_version | 声明的 schema 版本 |
| name/description/unit/group | 编辑说明 |

```c
*out = (LyraParameterV3){
    sizeof(*out), LYRA_INTERFACE_VERSION, 0, 1,
    "example.remember_history", "记录导航历史", "是否记录手动导航历史",
    "", "播放规则", "true", 0, 0
};
```

完整可编译示例是 `examples/rules.c`。只声明当前参数键，宿主不提供旧键别名或迁移。相同参数不能被多个插件占用。卸载保留用户文件，重新安装后重新提供声明。

## 读取与写入

插件需要在 config\_tables 声明消费表，并通过 config\_text 或配置接口读值。schema text 的 field 0 当前值、1 默认值、2 名字、3 说明、4 单位、5 分组、6 旧键。

写入通过 `LyraConfigInterfaceV3.write(user,key,scalar)`，例如布尔用 `"true"`，字符串值需要包含 TOML 双引号。类型、声明范围与内置校验通过后持久化，在帧边界激活；随后 request\_frame。

不要一帧一帧重复声明不同 schema、无条件写回默认值或自行修改用户其他表。默认值不是重置用户设置的命令。

## 验证

检查默认值可解析、界限与整数标志有效、错误类型拒绝、越界拒绝、写入后下一帧可见、重启保留以及卸载重装。插件声明可配置参数不自动产生复杂设置控件；对应 UI 仍由默认或替换服务实现。
