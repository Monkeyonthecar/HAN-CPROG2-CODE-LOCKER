#ifndef FSM_H
#define FSM_H

typedef enum {
   S_NO,
   S_START,
   S_INITIALISED,
   S_ASK_LOCKER,
   S_DETECTED_OWNED,
   S_DETECTED_NEW
} state_e;

typedef enum {
   E_NO,
   E_START,
   E_CONTINUE,
   E_ASK_LOCKER,
   E_OWNED,
   E_NEW,
   E_RETURN,
   E_WRONG_CODE,
   E_RIGHT_CODE
} event_e;

#endif

