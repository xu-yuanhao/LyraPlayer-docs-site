#include "plugin/lyra_plugin.h"
#include <string.h>
static const LyraPlaybackInterfaceV3 *playback;
static float box_x, box_y, box_w, box_h;
static int paint(void *user, const LyraHostV3 *host, int64_t now, float x, float y, float w, float h) {
    (void)user;
    (void)now;
    box_x = x;
    box_y = y;
    box_w = w;
    box_h = h;
    LyraPlaybackSnapshotV3 current = {0};
    current.size = sizeof(current);
    playback->snapshot(playback->user, &current);
    LyraSolid background = {x, y, w, h, 0, .16f, .16f, .16f, 1};
    LyraTextLayerV3 title = {0};
    title.size = sizeof(title); title.text = "Third style";
    title.x = x + 24; title.y = y + h * .4f; title.text_size = 24;
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
static int input(void *user, const LyraHostV3 *host, const LyraInput *input) {
    (void)user;
    if (input->action != LYRA_INPUT_UP || input->x < box_x || input->x > box_x + box_w ||
        input->y < box_y + box_h * .6f || input->y > box_y + box_h)
        return 0;
    LyraPlaybackCommandV3 command = {0};
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
static int describe(void *user, int32_t index, LyraStyleDescriptionV3 *out) {
    (void)user;
    if (index != 0 || !out || out->size != sizeof(*out))
        return -1;
    *out = (LyraStyleDescriptionV3){0};
    out->size = sizeof(*out);
    strcpy(out->id, "example.third");
    strcpy(out->label, "Third style");
    out->paint = paint;
    out->input = input;
    return 0;
}
static const LyraStylesInterfaceV3 styles = {sizeof(styles), LYRA_INTERFACE_VERSION, 0, count, describe};
static const void *interface(const LyraHostV3 *host, uint32_t id, uint32_t version, uint32_t size) {
    (void)host;
    return id == LYRA_INTERFACE_STYLES && version == LYRA_INTERFACE_VERSION && size == sizeof(styles) ? &styles : 0;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV3 *host, LyraPluginV3 *out) {
    if (!host || host->abi != LYRA_PLUGIN_ABI || host->size != sizeof(*host) || !host->query_interface)
        return -1;
    playback = host->query_interface(host->user, LYRA_INTERFACE_PLAYBACK, LYRA_INTERFACE_VERSION, sizeof(*playback));
    if (!playback)
        return -1;
    *out = (LyraPluginV3){0};
    out->size = sizeof(*out);
    out->abi = 3;
    out->id = "example.style";
    out->kind = "style";
    out->version = "1.0";
    out->query_interface = interface;
    return 0;
}
