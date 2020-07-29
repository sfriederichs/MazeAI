//AI Project
//
//This module contains:
//
//Drawer Code, and clear screen code

#include <stdio.h>
#include <conio.h>
#include "main.h"
#include "d_drawer.h"

//note: .'s are better than *'s for drawing, and a - is an unknown char

void D_DrawMap( void )
{
 int i,p;
 gotoxy(0,1);
 for(i=0;i<21;i++) 
 {
  for(p=1;p<22;p++)
  {
   if(player.loc.x == p && player.loc.y == i)
    printf( "" );
   else if(nextloc.x == p && nextloc.y == i)
    printf( "0" );
   else if(goalloc.x == p && goalloc.y == i)
    printf( "*" );
   else if(map[i][p] == '*')
    printf( "." );
   else if(map[i][p] == ' ')
    printf( " " );
   else
    printf( "-" );
  }
  D_DrawHUD(i);
//  D_DrawText(i);
  printf("\n");
 } 
}

void D_DrawHUD( int i )
{
 int a = strlen(player.state.action),b,c;
 b = 48 - a;

 switch(i)
 {
  case 1:
   printf( "Gamecount: %3d",gamecount);
   break;
  case 2:
   printf( "AI Num: %3d (%d,%d,%d,%d,%d)", player.ai.number,
						  player.ai.thriftyness,
						  player.ai.updown,
						  player.ai.annoyance,
						  player.ai.resolutness,
						  player.ai.lookahead);
   break;
  case 3:
   printf( "Goal: %2d  State: Thr %d Upd %d Ann %d Res %d", player.goal,
							    player.state.thrifty,
						            player.state.updown,
						            player.state.annoyed,
						            player.state.resolute);
   break;
  case 4: 
   printf( "Action: %s", player.state.action);
   for(c = 0; c<b;c++) //Steve 5/4/99 - Text buffer
    printf("%1s",null);
   break;
  case 5:
   printf( "Upfailed: %d Downfailed: %d",player.state.upfailed, player.state.downfailed);
   break;   
  default:
   break; //Ouch :)
 }
}							 