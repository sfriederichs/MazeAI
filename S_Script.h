#ifndef __S_SCRIPT__
#define __S_SCRIPT__

typedef struct
{
 int cmdnum;
 int value;
 char text[LINES][80]; //These will change based upon the requirements of the text box
 loc_t loc;
 ai_t ai;

} scriptcmd_t;

typedef struct
{
 char name[80];
 int inputype;
} cmdinfo_t;

scriptcmd_t script[SCRIPTSIZE];

cmdinfo_t commands[COMMANDS];

int character, datacounter;

char line[80], data[LINES][80];

void S_InitCommands( void );
void S_LoadScript( void );
void S_LoadValues( FILE *bah);
void S_AssignValues( scriptcmd_t *command );
void S_ClearArray( void );
void S_NewLine( void );
void S_ExecScript( void );
void S_ClearData( void );
void S_ClearLine( void );


#endif