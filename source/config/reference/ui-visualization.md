# ui.toml · visualization

[下载 ui.toml](/downloads/reference-data/ui.toml) · [配置校验](/config/validation)

## visualization.enabled

````toml
[visualization]
enabled = true
````

## visualization.strength

````toml
[visualization]
strength = "high"
````

## visualization.medium_low_frequency

````toml
[visualization]
medium_low_frequency = 0.3
````

## visualization.low_low_frequency

````toml
[visualization]
low_low_frequency = 0.15
````

## visualization.low_impact

````toml
[visualization]
low_impact = 0.35
````

## visualization.haptic_steps

````toml
[visualization]
haptic_steps = 12
````

## visualization.slider_fraction

````toml
[visualization]
slider_fraction = 0.48
````

## visualization.slider_height_dp

````toml
[visualization]
slider_height_dp = 32
````

## visualization.slider_inset_dp

````toml
[visualization]
slider_inset_dp = 12
````

## visualization.disabled_alpha

````toml
[visualization]
disabled_alpha = 0.35
````

## visualization.custom

````toml
[visualization]
custom = { strength = 0.85, low_frequency = 1, impact = 1, dilation = 0.16, displacement = 0.065, brightness = 0.14, highlights = 0.12, speed_boost = 1.8, lobe_scale = 0.5, contrast = 0.32, saturation = 0.28, size_exchange = 1, attack_ms = 35, release_ms = 180, handoff_hold_ms = 250, track_blend_ms = 180, background_blur = 31.77, background_saturation = 2.5, background_dim = 0.75, top_rotation = 1.2, bottom_rotation = 0.67, container_rotation = -0.6, color_morph_ms = 14000, accent_morph_ms = 10000, cover_morph_ms = 1400, immersive_strength = 0.45 }
````

## visualization.minimum

````toml
[visualization]
minimum = { strength = 0, low_frequency = 0, impact = 0, dilation = 0, displacement = 0, brightness = 0, highlights = 0, speed_boost = 0, lobe_scale = 0, contrast = 0, saturation = 0, size_exchange = 0, attack_ms = 1, release_ms = 10, handoff_hold_ms = 0, track_blend_ms = 1, background_blur = 20, background_saturation = 0.5, background_dim = 0.35, top_rotation = -4, bottom_rotation = -4, container_rotation = -4, color_morph_ms = 1, accent_morph_ms = 1, cover_morph_ms = 1, immersive_strength = 0 }
````

## visualization.maximum

````toml
[visualization]
maximum = { strength = 1.6, low_frequency = 1, impact = 1, dilation = 0.5, displacement = 0.2, brightness = 0.5, highlights = 0.5, speed_boost = 5, lobe_scale = 0.5, contrast = 0.8, saturation = 1, size_exchange = 1, attack_ms = 200, release_ms = 1000, handoff_hold_ms = 1000, track_blend_ms = 1000, background_blur = 100, background_saturation = 4, background_dim = 0.9, top_rotation = 4, bottom_rotation = 4, container_rotation = 4, color_morph_ms = 30000, accent_morph_ms = 30000, cover_morph_ms = 10000, immersive_strength = 1 }
````
