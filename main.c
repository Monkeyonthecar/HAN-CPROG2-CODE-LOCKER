// Locker system Project (Monkeyonthecar) --------------------------------------------

#include "fsm.h"
#include "subsystems.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

event_e generateEvent(void);
void eventHandler(event_e event);
event_e CVMinitialise(void);
event_e CVMcheckCode(void);
event_e CNAcheckChoice(void);
void AskLockerNumber(void);
void PickCode(void);
void OWNED(void);

state_e currentState = S_START;
event_e currentEvent = E_NO;
//Variables
int i;
int locker[2][11] = {{1,2,3,4,5,6,7,8,9,10},{0,0,0,0,0,0,0,0,0,0}};
int lockercode[10] = {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000};
int inputtedcode;
int admincode= 4929;
char inputtedcodes[5];
char i2[20];
char newlockercode[50];
char secret[16]="secretadminpass";
int secrett;

int main(void)
{
   eventHandler(E_START);
   // Endless loop

   while (1)
   {

      currentEvent = generateEvent();
      eventHandler(currentEvent);
   }

   return 0;
}

event_e generateEvent(void)
{
   event_e nextEvent = E_NO;
   switch(currentState)
   {
      case S_NO:
         DSPshowSystemError("current state is not initialised");
         break;
      case S_START:
         nextEvent = E_START;
         break;
      case S_INITIALISED:
         nextEvent = E_CONTINUE;
         break;
      case S_ASK_LOCKER: 
         AskLockerNumber();
         nextEvent = CNAcheckChoice();
         break;
      case S_DETECTED_OWNED:
         nextEvent = CVMcheckCode();
         break;
      case S_DETECTED_NEW:
         nextEvent = CVMcheckCode();
         break;
   }

   return nextEvent;
}

void eventHandler(event_e event)
{
   state_e nextState = S_NO;

   switch(currentState)
   {
      case S_START:
         CVMinitialise();
         nextState = S_INITIALISED;
         break;

      case S_INITIALISED:
         nextState = S_ASK_LOCKER;
         break;

      case S_ASK_LOCKER:
         switch (event)
         {
            case E_OWNED:
               OWNED();
               nextState = S_DETECTED_OWNED;
               break;

            case E_NEW:
               nextState = S_DETECTED_NEW;
               break;

            default:
              DSPshowSystemError("S_ASK_LOCKER received event "
                               "not handled");
               nextState = S_ASK_LOCKER;
         }
         break;

      case S_DETECTED_OWNED:
         CVMcheckCode();
         switch (event)
         {
            case E_RIGHT_CODE:
               locker[1][i]=0;//open locker
               DSPshow("correct locker code, locker is open\n");
               nextState = S_ASK_LOCKER;
               break;
            case E_WRONG_CODE:
               DSPshow("wrong locker code or check if this locker is already open\n");
               nextState = S_ASK_LOCKER;
               break;
            default:
               DSPshowSystemError("S_DETECTED_OWNED received event "
                                  "not handled");
               nextState = S_ASK_LOCKER;
               break;
         }
         break;

      case S_DETECTED_NEW:

         if(locker[1][i]==0) //locker is open
         {
               PickCode();
               nextState = S_ASK_LOCKER;
               break;               
         }
         else
         {
         DSPshow("This locker is already taken, please try another locker\n");
         nextState= S_ASK_LOCKER;
         break;
         }

      default:
         DSPshowSystemError("CVM in unknown current state");
         break;
   }
   currentState = nextState;
}

event_e CVMinitialise(void)
{
   // Initialise all subsystems (devices)
   DSPinitialise();
   KYBinitialise();
   CNAinitialise();
   DSPshow("-----------------------------------------------Locker System----------------------------------------------");
   DSPsimulationSystemInfo();
   return E_CONTINUE;
}

event_e CVMcheckCode(void)
{
   if (((lockercode[i] == inputtedcode )|| (inputtedcode == admincode)) &&locker[1][i]==1 )
   {
      return E_RIGHT_CODE;
   }

   else
   {
      return E_WRONG_CODE;
   }
}


void AskLockerNumber(void)
{   


   DSPshow("Which locker would you like to select? (please pick 1 out of 10)");
   gets(i2);
   secrett=strcmp(i2,secret);
   if(secrett==0)
   {
   exit(0);
   }
   i = atoi(i2);
   while(i<1||i>10)
   {
DSPshow("please only use a number between the range 1 to 10");
gets(i2);
i = atoi(i2);
   }
}


void PickCode (void)
{
   DSPshow("Please pick a 4-digit code");
   gets(newlockercode);
   while (strlen(newlockercode)!=4 || !isdigit(newlockercode[0])|| !isdigit(newlockercode[1])|| !isdigit(newlockercode[2])|| !isdigit(newlockercode  [3]) ) {
DSPshow("please use a 4 digit code and only integers");
gets(newlockercode);
   }
lockercode[i] = atoi(newlockercode);
   locker[1][i]=1;// locker gesloten
   DSPshow("Locker is locked \n");
}

void OWNED (void)
{
   DSPshow("please enter your code");
   gets(inputtedcodes);
   while (strlen(inputtedcodes)>4 || !isdigit(inputtedcodes[0])|| !isdigit(inputtedcodes[1])|| !isdigit(inputtedcodes[2])|| !isdigit(inputtedcodes[3]) ) {
DSPshow("please use a 4 digit code and only integers");
gets(inputtedcodes);
inputtedcode = atoi(inputtedcodes);
   }
   inputtedcode = atoi(inputtedcodes);

}
