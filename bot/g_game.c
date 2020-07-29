//Ai Exp. Code for g_game.c
//
//This module contains:
//
//Game Loop

#include "main.h"

int G_GameLoop(void)
{

 gamecount = 0;

 player.loc = defaults.startloc;

 goalloc = defaults.goalloc;

 player.goal = defaults.startgoal;

 do
 {
  gamecount++;
  //clrscr();
  
  A_AiLoop();

  if(defaults.debug)
  {
   I_AIDebug( "Gamecount" );
   I_IntAIDebug( gamecount );
   I_AIDebug( "\n" );
  }

 }while(((player.loc.x != goalloc.x) || (player.loc.y != goalloc.y)) 
         && gamecount < defaults.maxtime); 

 I_WriteTimes();

 return gamecount;

}			

