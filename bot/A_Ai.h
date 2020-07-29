#ifndef __A_AI__
#define __A_AI__

void A_AiLoop();
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
void A_AiDebug( char* message );
void A_IntAiDebug( int num );

int failed, annoycounter, failedspec,up,down,annoycount;

loc_t movelog[8], logcopy[8], annoyedlog[8];

loc_t nextloc, failedloc, movelog[8], logcopy[8], annoyedlog[8];


#endif
