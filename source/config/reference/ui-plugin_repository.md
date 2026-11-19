# ui.toml · plugin_repository

同一签名信任组的镜像、验证公钥、读取预算、搜索权重。

[下载 ui.toml](/downloads/reference-data/ui.toml) · [配置校验](/config/validation)

## plugin_repository.sources

````toml
[plugin_repository]
sources = "https://raw.githubusercontent.com/xu-yuanhao/LyraPlayer-plugins/main/catalog/v2/index.json|https://gitlab.com/xu-yuanhao/lyraplayer-plugins/-/raw/main/catalog/v2/index.json"
````

## plugin_repository.public_key

````toml
[plugin_repository]
public_key = "MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEIh3nwL4tJHEpjJ+qeV/bEVZH4byYfverEkMSXbYYaSBaq8I7YFOT8E96GpgHe5ArP6IBICiRki9Tj0+/gHwoMQ=="
````

## plugin_repository.index_limit_bytes

````toml
[plugin_repository]
index_limit_bytes = 262144
````

## plugin_repository.archive_limit_bytes

````toml
[plugin_repository]
archive_limit_bytes = 33554432
````

## plugin_repository.timeout_ms

````toml
[plugin_repository]
timeout_ms = 10000
````

## plugin_repository.maximum_rows

````toml
[plugin_repository]
maximum_rows = 24
````

## plugin_repository.exact_score

````toml
[plugin_repository]
exact_score = 5000
````

## plugin_repository.prefix_score

````toml
[plugin_repository]
prefix_score = 2500
````

## plugin_repository.substring_score

````toml
[plugin_repository]
substring_score = 1400
````

## plugin_repository.description_score

````toml
[plugin_repository]
description_score = 500
````
