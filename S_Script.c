#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include "main.h"
#include "A_Ai.h"
#include "S_Script.h"
#include "G_Game.h"
#include "D_Drawer.h"
#include "I_Main.h"

void S_InitCommands( void )
{

int n;

//GameState or .cfg things

 clrscr();

 printf( "Initializing Commands" );

 sprintf(commands[n++].name, "StartLoc =");
 commands[n].inputype = 2;

 sprintf(commands[n++].name, "GoalLoc =");
 commands[n].inputype = 2;

 sprintf(commands[n++].name, "TimeLimit =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Slow =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Debug =");
 commands[n].inputype = 1;
 
//General Commands

 printf( "." );

 sprintf(commands[n++].name, "Pause");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "LoadMap");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Text =");
 commands[n].inputype = 4;

 sprintf(commands[n++].name, "GameLoop");
 commands[n].inputype = 5;

 sprintf(commands[n++].name, "Redraw");
 commands[n].inputype = 5;

//BotState

 printf( "." );

 sprintf(commands[n++].name, "BotLoc =");
 commands[n].inputype = 2;

 sprintf(commands[n++].name, "Traits =");
 commands[n].inputype = 3;

 sprintf(commands[n++].name, "AINum =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Goal =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Thrifty =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Updown =" );
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Annoyed =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "UpFailed =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "DownFailed =");
 commands[n].inputype = 1;

 sprintf(commands[n++].name, "Action" );
 commands[n].inputype = 4;
 
//Oops, newer commands

 printf( "." );

 sprintf(commands[n++].name, "ClearScreen" );
 commands[n].inputype = 5;

 sprintf(commands[n++].name, "NextLoc =" );
 commands[n].inputype = 2;

 printf( "\n" );

}

void S_LoadScript( void )
{

 FILE *bah = fopen("ai.dem", "rt+");
 
 char c;

 int i, scriptnum = 0;

 scriptcmd_t* command;

 S_ClearLine();
 
 printf( "Loading Script" );

 do
 {
  c = fgetc(bah);
   
  if(c == '\n')
   continue;

  if(c == ';')
  {
   S_NewLine();
   continue;
  }

  line[character] = c;

  Debug( "Character" );
  IntDebug( character );
  Debug( "Line" );
  Debug( line );

  character++;

  for(i=0;i<COMMANDS;i++)
   if(strcmp(line, commands[i].name) == 0)
   {
    Debug( "Found" );
    Debug( line );

    script[scriptnum].cmdnum = i;

    command = &script[scriptnum];

    Debug( "1" );

    S_LoadValues(bah);

    Debug( "2" );

    S_AssignValues(command);

    Debug( "3" );

    S_NewLine();
    scriptnum++;
  
    Debug( "Done with found" );
  
    break;

   }
 
 Debug( "\n" );

 }while(!feof(bah));

 printf("\n");
 
}

void S_LoadValues( FILE* bah )
{
 char c;

 int i = -1;

 Debug( "4" );

 datacounter = 0;

 Debug( "7" );

 S_ClearData();

 Debug( "5" );

 do
 {
  c = fgetc(bah);

  Debug( "6" );

  if(c == ',')
  {
   datacounter++;
   i = -1;
   continue;
  }      

  if(c == ';' )
   break;
  
  i++;
 
  data[datacounter][i] = c; //Add the current character (while not a \n or a ,) to the raw value

  Debug( "Current Data" );
  Debug( data[datacounter]);
  Debug( "i" );
  IntDebug( i );
  Debug( "Command Counter" );
  IntDebug( datacounter );

 }while(c != '\n'); //I really don't need that while, but it's required

 Debug( "Done with Loading Values" );
}


void S_AssignValues( scriptcmd_t *command )
{

 int p;

 switch(commands[command->cmdnum].inputype)
 {

  case 1: //Simple Value
   command->value = atoi(data[0]);
   break;

  case 2: //A loc
   command->loc.x = atoi(data[0]);
   command->loc.y = atoi(data[1]);
   break;

  case 3: //AI Traits
   command->ai.thriftyness = atoi(data[0]);
   command->ai.updown = atoi(data[1]);
   command->ai.annoyance = atoi(data[2]);
   command->ai.resolutness = atoi(data[3]);
   command->ai.lookahead = atoi(data[4]);
   break;      
           
  case 4:
   for(p=0;p<LINES;p++)
   {
    Debug( "p" );
    IntDebug( p );
    Debug( "Raw Data" );
    Debug( data[p] );
    sprintf(command->text[p], data[p]);
    Debug( "What it came up with" );
    Debug(command->text[p]);
   }
  }
}


void S_ExecScript( void )
{
 int p,r;
 
 Debug( "Start S_ExecScript" );

 clrscr();
 
 for(p=0;p<SCRIPTSIZE;p++)
 {
  if(script[p].cmdnum == 0) //If it's not there...
   break;
  Debug( "Certified Command" );
  Debug( commands[script[p].cmdnum].name ); 
 
  switch(script[p].cmdnum)
  {
   case 1:
    defaults.startloc = script[p].loc;
    break;
   case 2:
    goalloc = script[p].loc;
    break;
   case 3:
    defaults.maxtime = script[p].value;
    break;
   case 4:
    defaults.wait = script[p].value;
    break;
   case 5:
    defaults.debug = script[p].value;
    break;
   case 6:
    sleep(script[p].value);
    break;
   case 7:
    I_LoadMap(script[p].value);
    break;    
   case 8:
    Debug( "Copying Text" );
    for(r=0;r<LINES;r++)
    {
     sprintf(text[r], script[p].text[r]);
     Debug( "New text" );
     Debug( text[r] );
     Debug( "script text" );
     Debug( script[p].text[r] );
    }
    break;
   case 9:
    G_GameLoop();
    break;
   case 10:
    D_DrawMap();
    break;
   case 11:
    player.loc = script[p].loc;
    break;
   case 12:
    player.ai = script[p].ai;
    break;
   case 13:
    player.ai.number = script[p].value;
    break;
   case 14:
    player.goal = script[p].value;
    break;
   case 15:
    player.state.thrifty = script[p].value;
    break;
   case 16:
    player.state.updown = script[p].value;
    break;
   case 17:
    player.state.annoyed = script[p].value;
    break;
   case 18:
    player.state.upfailed = script[p].value;
    break;    
   case 19:
    player.state.downfailed = script[p].value;
    break;
   case 20:
    sprintf(player.state.action, script[p].text[0]);
    break;
   case 21:
    clrscr();
    break;
   case 22:
    nextloc = script[p].loc; 
    break;
  }
 }
}

void S_NewLine( void ) //Prepares all variables and clears the next file line
{
 printf(".");
 character = 0;
 S_ClearLine();

} 

void S_ClearLine( void )
{
 int q;

  for(q=0;q<80;q++)
  line[q] = '\0';
}

void S_ClearData( void )
{
 int p,q;
 for(p=0;p<LINES;p++)
  for(q=0;q<80;q++)
   data[p][q] = '\0';
} 


