#include "plugin/lyra_plugin.h"
#include <stdlib.h>
#include <string.h>
static const LyraPlaybackRulesV3 *builtin;
static const LyraConfigSchemaV3 *config;
static int count(void *user) {
    (void)user;
    return 1;
}
static int mode(void *user, int32_t row, LyraModeDescriptionV3 *out) {
    (void)user;
    if (row != 0 || !out || out->size != sizeof(*out))
        return -1;
    *out = (LyraModeDescriptionV3){sizeof(*out), 1001, "Reverse sequence"};
    return 0;
}
static const LyraModesInterfaceV3 modes = {sizeof(modes), LYRA_INTERFACE_VERSION, 0, count, mode};
static int parameter(void *user, int32_t row, LyraParameterV3 *out) {
    (void)user;
    if (row != 0 || !out || out->size != sizeof(*out))
        return -1;
    *out = (LyraParameterV3){sizeof(*out), 2, 0, 1,
        "example.remember_history", "Remember history", "Record manual navigation history",
        "", "Playback example", "true", 0, 0};
    return 0;
}
static const LyraConfigSchemaV3 schema = {sizeof(schema), LYRA_INTERFACE_VERSION, 0, count, parameter, 0};
static int next(void *user, const LyraPlaybackRuleRequestV3 *request, LyraPlaybackRuleResultV3 *out) {
    (void)user;
    if (request->mode != 1001)
        return builtin->next(builtin->user, request, out);
    if (request->count <= 0 || request->current < 0)
        return -1;
    char scalar[32] = {0};
    int remember = 1;
    int required = config->text(config->user, "example.remember_history", 0, scalar, sizeof(scalar));
    if (required > 0 && required <= (int)sizeof(scalar))
        remember = strcmp(scalar, "true") == 0;
    int delta = request->delta < 0 ? 1 : -1;
    int row = (request->current + delta) % request->count;
    if (row < 0)
        row += request->count;
    *out = (LyraPlaybackRuleResultV3){sizeof(*out), row, remember};
    return 0;
}
static int order(void *user, const LyraPlaybackRuleRequestV3 *request, int32_t *rows, int32_t cap, int32_t *current) {
    (void)user;
    if (request->mode != 1001)
        return builtin->order(builtin->user, request, rows, cap, current);
    if (cap < request->count)
        return -1;
    for (int i = 0; i < request->count; ++i)
        rows[i] = request->count - i - 1;
    *current = request->count - request->current - 1;
    return request->count;
}
static const LyraPlaybackRulesV3 rules = {sizeof(rules), LYRA_INTERFACE_VERSION, 0, next, order, &modes};
static const void *interface(const LyraHostV3 *host, uint32_t id, uint32_t version, uint32_t size) {
    (void)host;
    if (version != LYRA_INTERFACE_VERSION)
        return 0;
    if (id == LYRA_INTERFACE_RULES && size == sizeof(rules))
        return &rules;
    if (id == LYRA_INTERFACE_CONFIG_SCHEMA && size == sizeof(schema))
        return &schema;
    return 0;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV3 *host, LyraPluginV3 *out) {
    if (!host || host->abi != LYRA_PLUGIN_ABI || !host->query_interface)
        return -1;
    builtin = host->query_interface(host->user, LYRA_INTERFACE_RULES, LYRA_INTERFACE_VERSION, sizeof(*builtin));
    config = host->query_interface(host->user, LYRA_INTERFACE_CONFIG_SCHEMA, LYRA_INTERFACE_VERSION, sizeof(*config));
    if (!builtin || !config)
        return -1;
    *out = (LyraPluginV3){0};
    out->size = sizeof(*out);
    out->abi = 3;
    out->id = "example.rules";
    out->kind = "playback-rules";
    out->version = "1.0";
    out->query_interface = interface;
    return 0;
}
