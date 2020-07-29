#ifndef __MAIN__
#define __MAIN__

#define MAPS 2
#define COMMANDS 18 //Current # of commands
#define SCRIPTSIZE 25 //max # of script commands
#define LINES 5 //# of lines of text box


#include <stdio.h>

//-----Main-----\\

typedef struct
{
 int x;
 int y;
} loc_t;

typedef struct
{
 int number;
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
 int doubleann;
 char action[80]; //Steve - 4/3/99 - What the robot is currently doing
 int upfailed; 
 int downfailed; //Steve 4/3/99 - For backtracking behavior removal
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
 ai_t ai;
 int number;
 int loop;
 int loops;
 int maxtime;
 int wait;
 int waitime;
 int demo;
}defaults_t;

typedef struct
{
 int times[MAPS];
 int number[MAPS];
}results_t;

results_t bests, result;

int number,looper,mapnum,i,p,counter[7], up, down;

player_t player;

defaults_t defaults;

char defaultfile[80], resultsfile[80], base, map[22][22], null[36];

FILE *results;

void I_IntDebug( int value );
void I_Debug( char* message );

//-----A_Ai-----\\

int A_ResolveGoal( int modifier );
void A_MoveUp( void );
void A_MoveDown( void );
int A_CheckTrait(int trait);
int A_CheckAnnoyance( void );
int A_LookAhead( void );
void A_BotThink( void );
void A_LogMove( void );
void A_LogAnnoyedMove( void );
int A_CheckDoubleAnnoyance( void );

int failed, annoycounter, failedspec,up,down;

loc_t nextloc, goalloc, failedloc;

//-----G_Game-----\\

int G_GameLoop( void );
int gamecount, annoycount;
loc_t movelog[8], logcopy[8], annoyedlog[8];


#endif
