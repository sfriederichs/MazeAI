#ifndef __MAIN__
#define __MAIN__

#define HEIGHT 21;
#define LENGTH 21;

#include <stdio.h>

//-----Main-----\\

typedef struct
{
 int x;
 int y;
} loc_t;

typedef struct
{
 int resolutness;
 int lookahead;
 int updown; 
 int thriftyness;
 int annoyance;
 } ai_t;

typedef struct
{
 int annoyed;
 int lookahead;
 int updown;
 int resolute;
 int thrifty;
} state_t;

typedef struct
{
 loc_t loc;
 int goal;
 ai_t ai;
 state_t state;
} player_t;

typedef struct
{
 loc_t startloc;
 loc_t goalloc;
 int debug;
 int startgoal;
 int counter[6];
 char basedefault[80];
 char defaultresults[80];
}defaults_t;

int maincount, subcount, number,dummy,looper,best1, best1num, best2,
    best2num, maptime;

int counter[7];

char map[22][22];

player_t player;

defaults_t defaults;

char defaultfile[80], resultsfile[80];
char base;

FILE *results;

//-----I_Main-----\\

void I_WriteDebugFile( char* message );
void I_Quit( void );
void I_Error( char* message );
void I_WriteIntDebugFile( int value );
/* void I_IncrementStats( int* counter, int* number, ai_t* ai); */

void I_ClearDeubg( void );
void I_LoadMap( int mapnum );

//-----D_Drawer-----\\


void D_DrawMap( void );
void D_ClearScreen( void );


//-----A_Ai-----\\

int A_ResolveGoal( int modifier );
void A_MoveUp( void );
void A_MoveDown( void );
int A_CheckTrait(int trait);

/*int A_CheckAnnoyance(loc_t log, int annoycount, int annoyance);*/

int A_CheckAnnoyance( void );
int A_LookAhead( void );
void A_BotThink( void );

int failed, annoycounter, failedspec;

loc_t nextloc, goalloc;

//-----G_Game-----\\

int G_GameLoop( void );
int gamecount, annoycount;
loc_t movelog[8], logcopy[8];

#endif
