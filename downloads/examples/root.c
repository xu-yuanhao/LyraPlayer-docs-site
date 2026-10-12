#include "plugin/lyra_plugin.h"
static int frame(const LyraHostV3 *host, int64_t time_ns) {
    (void)time_ns;
    LyraSolid background = {0, 0, 4096, 4096, 0, .12f, .12f, .12f, 1};
    LyraTextLayerV3 title = {0};
    title.size = sizeof(title); title.text = "Lyra: replacement root";
    title.x = 24; title.y = 80; title.text_size = 28;
    title.r = title.g = title.b = title.a = title.opacity = 1;
    LyraSceneV3 scene = {0};
    scene.size = sizeof(scene);
    scene.solids = &background;
    scene.solid_count = 1;
    scene.text_layers = &title;
    scene.text_layer_count = 1;
    host->submit(host->user, &scene);
    return 0;
}
static int input(const LyraHostV3 *host, const LyraInput *input) {
    (void)host;
    (void)input;
    return 1;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV3 *host, LyraPluginV3 *out) {
    if (!host || host->abi != LYRA_PLUGIN_ABI || host->size != sizeof(*host))
        return -1;
    *out = (LyraPluginV3){0};
    out->size = sizeof(*out);
    out->abi = 3;
    out->id = "example.root";
    out->kind = "frame";
    out->version = "1.0";
    out->on_frame = frame;
    out->on_input = input;
    return 0;
}
