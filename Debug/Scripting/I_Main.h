
#ifndef __I_MAIN__
#define __I_MAIN__

void I_WriteDebugFile( char* message );
void I_Quit( void );
void I_Error( char* message );
void I_ClearAIDeubg( void );
void I_ClearDebug( void );
void I_ClearResults( void );
void I_AIDebug( char *message );
void I_IntAIDebug( int value );
void I_LoadMap( int mapnumber );
void I_WriteResults( int mapnum );
void I_WriteStats( void );
void I_WriteTimes( void );
void I_WriteTraits( void );
void I_WriteHeader( void );
void I_LoadDefaults( void );
void I_WriteBests( void );
void I_Startup( void );

#endif
