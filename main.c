//AI Exp. 
//
//This module contains:
//
//Main

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "G_Game.h"
#include "I_Main.h"
#include "S_Script.h"

int main()
{
 
 I_Startup();

 if(defaults.demo)
 {
  S_InitCommands();
  S_LoadScript();
  S_ExecScript();
 }
 else
 {

 do
  {

  if(!defaults.loop) //Single Loop
   player.ai = defaults.ai;
 
  else //Large, continuous loop
  {


   do
   {
     q++; 
     p = q - 1;  

     if(counter[p] == 4) 
     {
      counter[q]++; 
      counter[p] = 1; 
     }
    } while(q < 6);  

    counter[0] = 4;

    if(counter[6] == 2)
     break;
  
    q=0;
    p=0;

    number++; 
    player.ai.number = number;

    player.ai.thriftyness = counter[1];
    player.ai.updown = counter[2];
    player.ai.annoyance = counter[3];
    player.ai.resolutness = counter[4];
    player.ai.lookahead = counter[5];
   }

  //NOTE: these numbers will be the number of the AI, not the counter, heh, I'm good

   sprintf(defaultfile, "base/%d.txt", player.ai.number); //Make output file

   I_ClearAIDebug();

   I_WriteStats();  //Write Traits of AI to logfile

   mapnum = 0;

   do
   {

    I_LoadMap(mapnum); //Load Map
   
    for(looper = 0; looper<defaults.loops; looper++)
      result.times[mapnum] += G_GameLoop();

    I_WriteResults(mapnum);
   
    mapnum++;

   }while(mapnum < MAPS);

   I_WriteTraits(); //Write traits to results file

  }while(number != 243 && defaults.loop);

  I_WriteBests();

  fprintf(results, "\n");

 }

 fclose(results);
 
 return 1;

}
   
void ClearDebug( void )
{
 FILE *bah = fopen("ai.dbg", "wt+");
 fclose(bah);
}

void Debug( char* message )
{
 FILE *bah = fopen("ai.dbg", "at+");
 fprintf(bah, "%s\n", message);
 fclose(bah);
}

void IntDebug( int value )
{
 FILE *bah = fopen("ai.dbg", "at+");
 fprintf( bah, "%d\n", value);
 fclose(bah);
}  


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        