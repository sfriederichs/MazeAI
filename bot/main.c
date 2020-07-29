//AI Exp. 
//
//This module contains:
//
//Main

#include <string.h>
#include "main.h"

int main()
{
 
I_Startup();

 do
 {

  if(!defaults.loop) //Single Loop
   player.ai = defaults.ai;
 
  else //Large, continuous loop
  {

/*
  I_Debug( "Counters Before" );
  I_IntDebug( counter[0] );
  I_IntDebug( counter[1] );
  I_IntDebug( counter[2] );
  I_IntDebug( counter[3] );
  I_IntDebug( counter[4] );
  I_IntDebug( counter[5] );  
  I_IntDebug( i );
  I_IntDebug( p );
*/

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

/*
  I_Debug( "Counters After" );
  I_IntDebug( counter[0] );
  I_IntDebug( counter[1] );
  I_IntDebug( counter[2] );
  I_IntDebug( counter[3] );
  I_IntDebug( counter[4] );
  I_IntDebug( counter[5] );
*/
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

/*
  I_Debug( "Current Defaultfile" );
  I_Debug( defaultfile );
  I_Debug( "Current Number" );
  I_IntDebug( number );
  I_Debug( "Bot Traits" );
  I_IntDebug( player.ai.thriftyness );
  I_IntDebug( player.ai.updown );
  I_IntDebug( player.ai.annoyance );
  I_IntDebug( player.ai.resolutness );
  I_IntDebug( player.ai.lookahead );
*/

//  fprintf(results, "%3d", player.ai.number); //Write number to results file

  I_ClearAIDebug();

  I_WriteStats();  //Write Traits of AI to logfile

  mapnum = 0;

  do
  {

   I_LoadMap(mapnum); //Load Map
   
//   I_Debug( "Current Mapnum" );
//   I_IntDebug( mapnum );

   for(looper = 0; looper<defaults.loops; looper++)
    result.times[mapnum] += G_GameLoop();

//   I_Debug( "Current Map's Time" );
//   I_IntDebug( result.times[mapnum] );

   I_WriteResults(mapnum);
   
   mapnum++;

  }while(mapnum < MAPS);

  I_WriteTraits(); //Write traits to results file

 }while(number != 243 && defaults.loop);

 I_WriteBests();

 fprintf(results, "\n");

 fclose(results);

 return 1;

}
   
  
  

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        