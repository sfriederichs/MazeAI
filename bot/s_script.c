#include <stdio.h>
#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int character = -1, linenum = 0,scriptnum = 0;

void S_InitCommands( void )
{

//GameState or .cfg things

 sprintf(commands[0].name, "StartLoc =");
 commands[0].inputype = 2;

 sprintf(commands[1].name, "GoalLoc =");
 commands[1].inputype = 2;

 sprintf(commands[2].name, "TimeLimit =");
 commands[2].inputype = 1;

 sprintf(commands[3].name, "Slow =");
 commands[3].inputype = 1;

 sprintf(commands[4].name, "Debug =");
 commands[4].inputype = 1;
 
//General Commands

 sprintf(commands[5].name, "Pause");
 commands[5].inputype = 1;

 sprintf(commands[6].name, "LoadMap");
 commands[6].inputype = 1;

 sprintf(commands[7].name, "Text =");
 commands[7].inputype = 4;

 sprintf(commands[8].name, "GameLoop");
 commands[8].inputype = 5;

 sprintf(commands[9].name, "Redraw");
 commands[9].inputype = 5;

//BotState

 sprintf(commands[10].name, "BotLoc =");
 commands[10].inputype = 2;

 sprintf(commands[11].name, "Traits =");
 commands[11].inputype = 3;

 sprintf(commands[12].name, "AINum =");
 commands[12].inputype = 1;

 sprintf(commands[13].name, "Goal =");
 commands[13].inputype = 1;

 sprintf(commands[14].name, "Thrifty =");
 commands[14].inputype = 1;

 sprintf(commands[15].name, "Updown =" );
 commands[15].inputype = 1;

 sprintf(commands[16].name, "Annoyed =");
 commands[16].inputype = 1;

 sprintf(commands[17].name, "UpFailed =");
 commands[17].inputype = 1;

 sprintf(commands[18].name, "DownFailed =");
 commands[18].inputype = 1;


}

void S_LoadScript( void )
{

 FILE *bah = fopen("ai.dem", "rt+");

 int p;
 char c;

 scriptcmd_t *current;

 do
 {
 
  c = fgetc(bah);

  character++; //Character counter

  for(p=0;p<COMMANDS;p++) //At end of line check for command
  { 
   if(strcmp(file[linenum], commands[p].name) == 0) //Are they the same?
   {

    sprintf(script[scriptnum].name, file[linenum]); //Copy the command found in the file to the parsed data

    S_NewLine();

    current = &script[scriptnum];

    S_LoadValues(current, bah);

    S_AssignValues(current);

    scriptnum++;

    S_NewLine();

    }
   }

   if (c == '\n') //End of line check //Note, this is needed
    S_NewLine();
   else
    file[linenum][character] = c; //If the line isn't finished, and it's not a newline, add it to the raw

   I_Debug( "\n" );

  }while(!feof(bah));

 fclose(bah);
}

void S_LoadValues( scriptcmd_t *command, FILE* bah )
{
 char c;

 do
 {
  c = fgetc(bah);

  if(c == ',')
  {
   command->counter++;
   character = -1;
   continue;
  }      

  if(c == '\n' )
   break;
  
  character++;

  command->raw[command->counter][character] = c; //Add the current character (while not a \n or a ,) to the raw value

 }while(c != '\n'); //I really don't need that while, but it's required
}


void S_AssignValues( scriptcmd_t *command )
{

 int i;

 for(i = 0; i<COMMANDS;i++)
 {
  if(strcmp(command->name, commands[i].name) == 0)
  { 
   switch(commands[i].inputype)
   {

    case 1: //Simple Value
     command->value = atoi(command->raw[0]);
     break;

    case 2: //A loc
     command->loc.x = atoi(command->raw[0]);
     command->loc.y = atoi(command->raw[1]);
     break;

    case 3: //AI Traits
     command->ai.thriftyness = atoi(command->raw[0]);
     command->ai.updown = atoi(command->raw[1]);
     command->ai.annoyance = atoi(command->raw[2]);
     command->ai.resolutness = atoi(command->raw[3]);
     command->ai.lookahead = atoi(command->raw[4]);
     break;      
           
    case 4:
     for(i=0;i<LINES;i++)
      strcpy(command->text[i], command->raw[i]);
     break;
   }       
  }
 }
}


void S_ExecScript( void )
{
 int p,q;
 
 for(p=0;p<SCRIPTSIZE;p++)
 {
  if(script[p].name == '\0') //If it's not there...
   continue;
  for(q=0;q<COMMANDS;q++)
  {
   if(strcmp(script[p].name, commands[q].name) == 0)
    switch(q)
    {
     case 0: 
      defaults.startloc = script[p].loc;
      break;
     case 1:
      goalloc = script[p].loc;
      break;
     case 2:
      defaults.maxtime = script[p].value;
      break;
     case 3:
      defaults.wait = script[p].value;
      break;
     case 4:
      defaults.debug = script[p].value;
      break;
     case 5:
      sleep(script[p].value);
      break;
     case 6:
      I_LoadMap(script[p].value);
      break;    
     case 8:
      G_GameLoop();
      break;
     case 9:
      D_DrawMap();
      break;
     case 10:
      player.loc = script[p].loc;
      break;
     case 11:
      player.ai = script[p].ai;
      break;
     case 12:
      player.ai.number = script[p].value;
      break;
     case 13:
      player.goal = script[p].value;
      break;
     case 14:
      player.state.thrifty = script[p].value;
      break;
     case 15:
      player.state.updown = script[p].value;
      break;
     case 16:
      player.state.annoyed = script[p].value;
      break;
     case 17:
      player.state.upfailed = script[p].value;
      break;    
     case 18:
      player.state.downfailed = script[p].value;
      break;
     case 19:
      sprintf(player.state.action, script[p].text[0]);
      break;
   }
  }
 }
}

void S_ClearArray( void ) //Initially clear the entire file array
{
 int p,i;
 for(i=0;i<80;i++)
  for(p=0;p<80;p++)
   file[i][p] = '\0';
}

void S_NewLine( void ) //Prepares all variables and clears the next file line
{
 int q;

 linenum++;
 character = -1;

 for(q=0;q<80;q++)
  file[linenum][q] = '\0';
} 

