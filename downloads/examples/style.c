#include "plugin/lyra_plugin.h"
#include <string.h>
static const LyraPlaybackInterfaceV2 *playback;
static float box_x, box_y, box_w, box_h;
static int paint(void *user, const LyraHostV2 *host, int64_t now, float x, float y, float w, float h) {
    (void)user;
    (void)now;
    box_x = x;
    box_y = y;
    box_w = w;
    box_h = h;
    LyraPlaybackSnapshotV2 current = {0};
    current.size = sizeof(current);
    playback->snapshot(playback->user, &current);
    LyraSolid background = {x, y, w, h, 0, .16f, .16f, .16f, 1};
    LyraGlyphCmd title = {x + 24, y + h * .4f, 24, 1, 1, 1, 1, "Third style", 0};
    LyraSceneV2 scene = {0};
    scene.size = sizeof(scene);
    scene.solids = &background;
    scene.solid_count = 1;
    scene.glyphs = &title;
    scene.glyph_count = 1;
    host->submit(host->user, &scene);
    return 0;
}
static int input(void *user, const LyraHostV2 *host, const LyraInput *input) {
    (void)user;
    if (input->action != LYRA_INPUT_UP || input->x < box_x || input->x > box_x + box_w ||
        input->y < box_y + box_h * .6f || input->y > box_y + box_h)
        return 0;
    LyraPlaybackCommandV2 command = {0};
    command.size = sizeof(command);
    command.kind = LYRA_PLAYBACK_TOGGLE;
    playback->command(playback->user, &command);
    host->request_frame(host->user);
    return 1;
}
static int count(void *user) {
    (void)user;
    return 1;
}
static int describe(void *user, int32_t index, LyraStyleDescriptionV2 *out) {
    (void)user;
    if (index != 0 || !out || out->size < sizeof(*out))
        return -1;
    *out = (LyraStyleDescriptionV2){0};
    out->size = sizeof(*out);
    strcpy(out->id, "example.third");
    strcpy(out->label, "Third style");
    out->paint = paint;
    out->input = input;
    return 0;
}
static const LyraStylesInterfaceV2 styles = {sizeof(styles), 2, 0, count, describe};
static const void *interface(const LyraHostV2 *host, uint32_t id, uint32_t version, uint32_t size) {
    (void)host;
    return id == LYRA_INTERFACE_STYLES && version == 2 && size <= sizeof(styles) ? &styles : 0;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV2 *host, LyraPluginV2 *out) {
    if (!host || host->abi != 2 || host->size < sizeof(*host) || !host->query_interface)
        return -1;
    playback = host->query_interface(host->user, LYRA_INTERFACE_PLAYBACK, 2, sizeof(*playback));
    if (!playback)
        return -1;
    *out = (LyraPluginV2){0};
    out->size = sizeof(*out);
    out->abi = 2;
    out->id = "example.style";
    out->kind = "style";
    out->version = "1.0";
    out->query_interface = interface;
    return 0;
}
