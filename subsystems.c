#include "fsm.h"
#include "subsystems.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//--------------------------------------------------------------------- Keyboard

void KYBinitialise(void)
{
   DSPdebugSystemInfo("Keyboard: initialised");
}

//---------------------------------------------------------------------- Display

#define DISPLAY_SIZE_STR "70"
#define DISPLAY_SIZE 70

void DSPinitialise(void)
{
   DSPdebugSystemInfo("Display: initialised");
}

void DSPshow(const char *text)
{
   printf("%-" DISPLAY_SIZE_STR "s \n", text);
}

void DSPdebugSystemInfo(const char *text)
{
   printf("\n-- DEBUG      %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPsimulationSystemInfo(void)
{
   printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t | \n------------------------------------------------SIMULATION------------------------------------------------\n");
}

void DSPshowSystemError(const char *text)
{
   printf("\n## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}

//----------------------------------------------------------------
void CNAinitialise(void)
{
   DSPdebugSystemInfo("locker system: initialised");
}

event_e CNAcheckChoice(void)
{

   event_e event = E_NO;


char choice[20];
int choice_int;
DSPshow("Please choose an option <1> OWNED  <2> NEW");

      gets(choice);
      while (strlen(choice)>1 || !isdigit(choice[0])) {
   DSPshow("please only use a 1 digit integer");
   gets(choice);
   }
   choice_int = atoi(choice);


   switch(choice_int)
   {
      case 1:
         event = E_OWNED;
         break;
      case 2:
         event = E_NEW;
         break;
      default:
         DSPshowSystemError("CNAcheckChoice received event "
                            "not handled");
         event = CNAcheckChoice();
   }
   return event;
}






