#include "plugin/lyra_plugin.h"
#include <string.h>
static int64_t value;
static int echo(void *user, const LyraMessageV3 *message, LyraReplyV3 *reply) {
    (void)user;
    LyraFieldRuleV3 rules[] = {{1, LYRA_FIELD_I64}};
    int valid = lyra_message_fields(message,rules,1);
    if (valid) return valid;
    if (message->operation != 1) return LYRA_MESSAGE_UNSUPPORTED;
    if (!reply->capacity) return LYRA_MESSAGE_CAPACITY;
    for (uint32_t i=0;i<message->field_count;++i) if(message->fields[i].tag==1) memcpy(&value,message->fields[i].data,sizeof(value));
    reply->fields[0]=(LyraFieldV3){1,LYRA_FIELD_I64,0,sizeof(value),&value};
    reply->field_count=1;
    return LYRA_MESSAGE_OK;
}
__attribute__((visibility("default"))) int lyra_plugin_init(const LyraHostV3 *host,LyraPluginV3 *out) {
    if(!host || host->abi!=LYRA_PLUGIN_ABI || host->size!=sizeof(*host)) return -1;
    const LyraServiceContextV3 *api=host->query_interface(host->user,LYRA_INTERFACE_SERVICE_CONTEXT,LYRA_INTERFACE_VERSION,sizeof(*api));
    if(!api)return -1;
    LyraCapabilityV3 definition={sizeof(definition),"example.echo",0,echo};
    if(!api->publish(api->user,&definition))return -1;
    definition.name="example.other";
    if(!api->publish(api->user,&definition))return -1;
    *out=(LyraPluginV3){0};out->size=sizeof(*out);out->abi=LYRA_PLUGIN_ABI;
    out->id="capability.fixture";out->kind="capability.parent";out->version="test";
    return 0;
}
