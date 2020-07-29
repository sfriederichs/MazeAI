//Ai Exp. Code for g_game.c
//
//This module contains:
//
//Game Loop

#include "main.h"
#include "G_Game.h"
#include "A_Ai.h"
#include "I_Main.h"

void A_AIDebug( char *message );
void A_IntAIDebug( int num );


int G_GameLoop(void)
{

 gamecount = 0;

 if(!defaults.demo) //Steve 4/18/99 - Want these defined in .dem
 {
  player.loc = defaults.startloc;

  goalloc = defaults.goalloc;

  player.goal = defaults.startgoal;
 }

 do
 {
  gamecount++;
  //clrscr();
  
  A_AiLoop();

  if(defaults.debug)
  {
   A_AIDebug( "Gamecount" );
   A_IntAIDebug( gamecount );
   A_AIDebug( "\n" );
  }

 }while(((player.loc.x != goalloc.x) || (player.loc.y != goalloc.y)) 
         && gamecount < defaults.maxtime); 

 G_WriteTimes();

 return gamecount;

}			

void G_WriteTimes( void )
{

 FILE *bah;

 bah = fopen(defaultfile, "at+");
 fprintf(bah, "Map - %d\n", mapnum);
 fprintf(bah, "Time - %d\n\n", gamecount);
 if(gamecount >= defaults.maxtime)
  fprintf(bah, "Timed Out\n\n");

 fclose(bah);      	
}
