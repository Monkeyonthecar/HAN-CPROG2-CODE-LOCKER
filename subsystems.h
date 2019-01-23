#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "fsm.h"

//--------------------------------------------------------------------- Keyboard
void KYBinitialise(void);
char KYBgetchar(void);
//---------------------------------------------------------------------- Display
void DSPinitialise(void);
void DSPshow(const char *text);
void DSPdebugSystemInfo(const char *text);
void DSPsimulationSystemInfo(void);
void DSPshowSystemError(const char *text);
//--------------------------------------------------------------------- Initialise
void CNAinitialise(void);
void CLDinitialise(void);
void CHDinitialise(void);

#endif
