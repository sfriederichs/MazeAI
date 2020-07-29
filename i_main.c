//AI experiment
//
//This module contains:
//
//Top level crap, init, error handling, etc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "main.h"
#include "I_Main.h"


void I_Error( char *message )
{
 Debug( message );
 printf( message );
 I_Quit();
}

void I_Quit( void )
{
}

//--------------

void I_ClearAIDebug( void )
{
 FILE *bah = fopen(defaultfile, "wt+");
 fclose(bah);
}

//---------------


void I_ClearResults( void )
{
 results = fopen("base/results.txt", "wt+");
 fclose(results);
}

//----------------

void I_LoadMap(int mapnumber)
{
 
 char c;
 int i,p;
 FILE *mapfile;

 i=p=0;

  switch(mapnumber) //Steve 3/29/99 - Change for multiple map support
  {
   case 0:
    mapfile = fopen("maze.dat", "rt");
    break;
   case 1:
    mapfile = fopen("course.dat","rt");
    break;
   case 2:
    mapfile = fopen("blank.dat","rt");
    break;
   case 3:
    mapfile = fopen("demo1.dat","rt");
    break;
   default:
    mapfile = fopen("blank.dat","rt");
    break;
  }

 if(mapfile==NULL)
  I_Error( "Couldnt open map file" );

 do
 {
  c = fgetc( mapfile );
  
  if( c == '\n')
   c = '\0';
 
  map[i][p] = c;

  if( c == '\0')
  {
   p = 0;
   i++;
   c = '\0';
  }

  p++;

 }while(!feof(mapfile));

 fclose(mapfile);

 result.times[mapnum] = 0; //Steve 3/29/99 - Removed old code, updated for new results system

}

void I_WriteHeader( void )
{
 int i;
 fprintf(results, "AI #  ");
 for(i=0;i<MAPS;i++)
  fprintf(results, "Map %2d ", i);
 fprintf(results, " Traits\n");
}

void I_WriteStats( void )
{
 FILE *bah = fopen(defaultfile, "at+");

 fprintf(results, "%3d    ", player.ai.number);
 fprintf(bah, "AI Num - %d\n", player.ai.number);
 fprintf(bah, "Thriftyness - %d\n", player.ai.thriftyness);
 fprintf(bah, "Updown - %d\n", player.ai.updown);
 fprintf(bah, "Annoyance - %d\n", player.ai.annoyance);
 fprintf(bah, "Resolutness- %d\n", player.ai.resolutness);
 fprintf(bah, "Lookahead - %d", player.ai.lookahead);
 fprintf(bah, "\n\n");

 fclose(bah);
}

void I_WriteResults( int mapnum )
{

 // int maptime;

 result.times[mapnum] = result.times[mapnum]/defaults.loops;

 fprintf(results, "%3d    ",result.times[mapnum]); //Steve 3/29/99
 
 if(result.times[mapnum] < bests.times[mapnum]) 
 {
  bests.times[mapnum] = result.times[mapnum];
  bests.number[mapnum] = result.number[mapnum];
 }
}

void I_WriteBests( void ) //Steve 3/29/99 - Added Multiple map and new results support
{
 int i;
 for(i=0;i<MAPS;i++)
  fprintf(results, "Best Map %d with time %d - %d\n", i, bests.times[i], bests.number[i]);
}

void I_WriteTraits( void )
{
 fprintf(results, "(%d,%d,%d,%d,%d)\n", player.ai.thriftyness,
					player.ai.updown,
					player.ai.annoyance,
					player.ai.resolutness,
					player.ai.lookahead);
}



void I_LoadDefaults( void )
{
 int i=-1,f;
 char input[20][80], file[20];
 FILE *config = fopen("ai.cfg", "rt");

 if(config == NULL)
  I_Error( "Config File Not Found" );

 do
 {
  fgets(file, 20, config); //Steve 5/4/99 - Comments in .cfg file
  f = (int)strchr(file, '#');
  if(!f)
  {
   i++;
   strcpy(input[i], file); 
  }
 } while(!feof(config));

 fclose(config);


 defaults.startloc.x = atoi(input[0]);
 defaults.startloc.y = atoi(input[1]);
 defaults.goalloc.x = atoi(input[2]);
 defaults.goalloc.y = atoi(input[3]);
 defaults.debug = atoi(input[4]);
 defaults.startgoal = atoi(input[5]);
 defaults.ai.thriftyness = atoi(input[6]);
 defaults.ai.updown = atoi(input[7]);
 defaults.ai.annoyance = atoi(input[8]);
 defaults.ai.resolutness = atoi(input[9]);
 defaults.ai.lookahead = atoi(input[10]);
 defaults.ai.number = atoi(input[11]);
 defaults.loop = atoi(input[12]);
 defaults.loops = atoi(input[13]);
 defaults.maxtime = atoi(input[14]);
 defaults.wait = atoi(input[15]);
 defaults.waitime = atoi(input[16]);
 defaults.demo = atoi(input[17]);
}

void I_Startup( void ) //Steve 3/29/99 - Consolidated several here
{

 int i;

 clrscr();
 counter[0] = 3;
 counter[1] = 1;
 counter[2] = 1;
 counter[3] = 1;
 counter[4] = 1;
 counter[5] = 1;
 counter[6] = 1;

 I_LoadDefaults();

 I_ClearResults();
 ClearDebug();

 results = fopen("base/results.txt", "at+" );

 for(i = 0; i < MAPS; i++)
  bests.times[i] = defaults.maxtime; 

 I_WriteHeader();

}

