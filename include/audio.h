#ifndef AUDIO_H
#define AUDIO_H

extern const unsigned int WIN_NOTES[];
extern const unsigned int WIN_DURS[];
extern const int WIN_LEN;

extern const unsigned int LOSE_NOTES[];
extern const unsigned int LOSE_DURS[];
extern const int LOSE_LEN;

void Audio_Init(void);
void Audio_PlayMelody(const unsigned int *notes, const unsigned int *durations, int length);
void Audio_PlayMove(void);
void Audio_PlayCollect(void);
void Audio_StartMenuMelody(void);
void Audio_StopMenuMelody(void);
void Audio_UpdateMenuMelody(unsigned int elapsed_ms);

#endif
