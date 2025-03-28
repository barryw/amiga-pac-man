// sound_manager.h
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <exec/types.h>

#define MAX_CHANNELS 4
#define DEFAULT_VOLUME 64

void init_sound_manager(void);

void play_sound(const UBYTE *data, ULONG length, ULONG sampleRate, BOOL stereo, UBYTE priority, UBYTE volume);

#endif // SOUND_MANAGER_H
