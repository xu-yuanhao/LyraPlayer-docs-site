#pragma once
#include <stdint.h>
// Optional provider interface. Existing ABI 2 structs remain unchanged.
#define LYRA_INTERFACE_PLAYBACK_OBSERVER 15u
#define LYRA_SELECTION_RESET 1u
#define LYRA_SELECTION_OPENING 2u
typedef struct LyraPlaybackSelectionV2 {
    uint32_t size, flags;
    uint64_t generation, from_entry, to_entry;
    int64_t from_track_id, to_track_id, position_us, duration_us;
    float direction;
} LyraPlaybackSelectionV2;
typedef struct LyraPlaybackObserverV2 {
    uint32_t size, version;
    void *user;
    void (*selection)(void *, const struct LyraPlaybackSelectionV2 *);
} LyraPlaybackObserverV2;
