#ifndef __MAIN__
#define __MAIN__

#define MAPS 2
#define SCRIPTSIZE 500
#define COMMANDS 22
#define LINES 5

#include <stdio.h>

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

int number,looper,mapnum,p,counter[7], up, down,q;

player_t player;

defaults_t defaults;
loc_t goalloc;
char defaultfile[80], resultsfile[80], base, map[22][22], null[36];

FILE *results;

void IntDebug( int value );
void Debug( char* message );
void ClearDebug( void );

#endif
