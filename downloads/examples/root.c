#include "plugin/lyra_plugin.h"
static int frame(const LyraHostV2 *host, int64_t time_ns) {
    (void)time_ns;
    LyraSolid background = {0, 0, 4096, 4096, 0, .12f, .12f, .12f, 1};
    LyraGlyphCmd title = {24, 80, 28, 1, 1, 1, 1, "Lyra: replacement root", 0};
    LyraSceneV2 scene = {0};
    scene.size = sizeof(scene);
    scene.solids = &background;
    scene.solid_count = 1;
    scene.glyphs = &title;
    scene.glyph_count = 1;
    host->submit(host->user, &scene);
    return 0;
}
static int input(const LyraHostV2 *host, const LyraInput *input) {
    (void)host;
    (void)input;
    return 1;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV2 *host, LyraPluginV2 *out) {
    if (!host || host->abi != 2 || host->size < sizeof(*host))
        return -1;
    *out = (LyraPluginV2){0};
    out->size = sizeof(*out);
    out->abi = 2;
    out->id = "example.root";
    out->kind = "frame";
    out->version = "1.0";
    out->on_frame = frame;
    out->on_input = input;
    return 0;
}
