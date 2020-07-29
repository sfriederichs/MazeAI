#include <stdio.h>
#include "main.h"
#include "S_Script.h"
#include <string.h>

int main()
{
 S_InitCommands();

 I_Debug( "Past InitCommands" );

 S_LoadScript();

 I_Debug( "Past LoadScript" );

 S_ExecScript();

 I_Debug( "Past ExecScript" );

 return 1;
}

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
 
 char c;

 int i;

 scriptcmd_t* command;

 S_ClearLine();
 
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

  I_Debug( "Character" );
  I_IntDebug( character );
  I_Debug( "Line" );
  I_Debug( line );

  character++;

  for(i=0;i<COMMANDS;i++)
   if(strcmp(line, commands[i].name) == 0)
   {
    I_Debug( "Found" );
    I_Debug( line );

    sprintf(script[scriptnum].name, commands[i].name);

    command = &script[scriptnum];
    S_LoadValues(command, bah);
    S_AssignValues(command);
    S_NewLine();
    scriptnum++;
   }
 
 I_Debug( "\n" );

 }while(!feof(bah));
}

void S_LoadValues( scriptcmd_t *command, FILE* bah )
{
 char c;

 int i = -1;

 cmdcounter = 0;

 S_ClearData();

 do
 {
  c = fgetc(bah);

  if(c == ',')
  {
   cmdcounter++;
   i = -1;
   continue;
  }      

  if(c == ';' )
   break;
  
  i++;
 
  data[cmdcounter][i] = c; //Add the current character (while not a \n or a ,) to the raw value

  I_Debug( "Current Data" );
  I_Debug( data[cmdcounter]);
  I_Debug( "i" );
  I_IntDebug( i );
  I_Debug( "Command Counter" );
  I_IntDebug( cmdcounter );

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
     for(i=0;i<LINES;i++)
      strcpy(command->text[i], data[i]);
     break;
   }       
  }
 }
}


void S_ExecScript( void )
{
 int p,q;
 
 I_Debug( "Start S_ExecScript" );

 for(p=0;p<SCRIPTSIZE;p++)
 {

  I_Debug( "At ScriptSize Loop" );
 
  if(script[p].name == '\0') //If it's not there...
   continue;
  for(q=0;q<COMMANDS;q++)
  {
  
   I_Debug( "At Commands Loop" );

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
//     case 8:
//      G_GameLoop();
//      break;
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

void S_NewLine( void ) //Prepares all variables and clears the next file line
{
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
 for(p=0;p<3;p++)
  for(q=0;q<80;q++)
   data[p][q] = '\0';
} 


