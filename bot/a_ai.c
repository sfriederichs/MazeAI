//AI experiment
//
//This module contains:
//Artificial Intelligence, and everything needed for it, movement,
//loc checking, move logging, etc.  Plus, it has the ai main loop

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include <unistd.h>

//Makes a move towards the goal you give it

int A_ResolveGoal( int modifier )
{
 int goal2,check;
 loc_t i;
 
 goal2 = player.goal * modifier;

 if(goal2 == 1)
 {
  check = (goalloc.x - player.loc.x);
  if(check != 0)
   i.x = (goalloc.x - player.loc.x)/abs(goalloc.x - player.loc.x);
  else
   return 0;
 }
 else
 {
  check = (goalloc.y - player.loc.y);
  if(check != 0)
   i.y = (goalloc.y - player.loc.y)/abs(goalloc.y - player.loc.y);
  else
   return 0;
 }

 if(goal2 == 1)
  nextloc.x += i.x;
 else
  nextloc.y += i.y;

 return 1;

}

//Makes a move by incrementing the current loc by +1 on said axis

void A_MoveUp( void )
{
 up = 1;
 if(player.goal == 1)
  nextloc.y += 1;
 else
  nextloc.x += 1;
}

//Makes a move by incrementing the current loc by -1 on said axis

void A_MoveDown( void )
{
 down = 1;
 if(player.goal == 1)
  nextloc.y -= 1;
 else
  nextloc.x -= 1;
}

//Determines the state of the bot based on its traits, 
//pretty self-explanitory, traits are 1,2, or 3.  1 is always
//do something, 2 is random between the do, and 3 would be always dont
//do something.

int A_CheckTrait( int trait )
{
 int i;
 time_t seconds;
 switch(trait)
 {
  case 1:
   i = 1;
   break; 
  case 2:
   time(&seconds);
   srand((unsigned int) seconds);
   i = rand()%2;
   break;
  case 3:
   i = 0;
   break;
 }
 return i;
}

//Annoyance is a special trait that needs to be checked, because it 
//compares the last 4 moves to the first 4 moves, and if they're the
//same, it gets annoyed

int A_CheckAnnoyance( void )
{
 int i = 0,p=0,annoyloop=0;
 loc_t q, r;

 do
 {
  q = movelog[i];
  r = movelog[i+4];

  if((q.x == r.x && q.y == r.y) && ((q.x * q.y * r.x * r.y) != 0)) //Null entries don't count
   annoyloop++;
  i++;
 }while(i<4);
 
 if(annoyloop == 4)
 {
  annoyloop = 0;
  annoycount++;
 }

 if(annoycount == player.ai.annoyance)
 {
  annoycount = 0;
  p = 1;
  failedspec = 1;
 }
  
 if(player.state.annoyed == 1) //Extra hack to make annoyance for 4
 {			       //turns	
  annoycounter++;
  p = 1;
 }
 else if(player.state.annoyed == 0)
  annoycounter = 0;


 if(annoycounter == 4)
 {
  annoycounter = 0;
  p = 0;
 }

 return p;
}

int A_CheckDoubleAnnoyance( void )
{
 int i = 0,p=0,annoyloop=0;
 loc_t q, r;

 do
 {
  q = annoyedlog[i];
  r = annoyedlog[i+4];

  if((q.x == r.x && q.y == r.y) && ((q.x * q.y * r.x * r.y) != 0)) //Null entries don't count
   annoyloop++;
  i++;
 }while(i<4);
 
 if(annoyloop == 4)
 {
  player.goal *= -1;

  p = 1;
  
  failedspec = 0;
  failed = 0;
  annoycounter = 0;
  player.state.annoyed = 0;

  for(i=0;i<8;i++)
  {
   annoyedlog[i].x = 0;
   annoyedlog[i].y = 0;
  }

  for(i=0;i<8;i++)
  {
   movelog[i].x = 0;
   movelog[i].y = 0;
  }
 }

 return p;
}

int A_Lookahead( void )
{
 int direction = 0, i = 0, p = 0, axis = 0;
 int checking_x, checking_y;

 loc_t checkloc;
 checkloc = player.loc;

 if(player.loc.x != nextloc.x)
 {
  if((nextloc.x - player.loc.x) == 0)
   return 0;

  direction = (nextloc.x - player.loc.x)/abs(nextloc.x - player.loc.x);
  //interesting math there, huh?
  axis = 1;
 }
 else
 {
  if((nextloc.y - player.loc.y) == 0)
   return 0;

  direction = (nextloc.y - player.loc.y)/abs(nextloc.y - player.loc.y);
  axis = 0;
 }

 for(i = 1; i<player.ai.lookahead+1; i++)
 {
  if(axis == 1)
   checkloc.x += direction;
  else
   checkloc.y += direction;

  checking_x = checkloc.x;
  checking_y = checkloc.y;

  if(map[checking_y][checking_x] == '*')
  {
   p = 1;
   break;
  } 
 }

 return p;
}

void A_LogMove( void )
{

 int i = 0;

 for(i=0;i<8;i++)
  logcopy[i] = movelog[i];

 for(i=0; i<7; i++)
  movelog[i] = logcopy[i+1];

 movelog[7] = nextloc;

}

//Steve - Added new 3/19/99 for double annoyance 

void A_LogAnnoyedMove( void )
{

 int i = 0;

 for(i=0;i<8;i++)
  logcopy[i] = annoyedlog[i];

 for(i=0; i<7; i++)
  annoyedlog[i] = logcopy[i+1];

 annoyedlog[7] = nextloc;

}


void A_CheckGoal( void )
{

 if(goalloc.x == player.loc.x)
 {
  player.goal = -1;
  player.state.upfailed = 0;
  player.state.downfailed = 0;
 }
 if(goalloc.y == player.loc.y)
 {
  player.goal = 1;
  player.state.upfailed = 0;
  player.state.downfailed = 0;
 }

}


//This is the big one, the decision maker

void A_BotThink( void )
{
 int a;
 
 if(failed || failedspec)
 {
  if(defaults.debug)
  {
   I_AIDebug( "AI Loop - Failed" );
   I_IntAIDebug( failed );
   I_AIDebug( "AI Loop - FailedSpec" );
   I_IntAIDebug( failedspec );
  }

  if(player.state.upfailed && player.state.downfailed)
  {
   player.goal *= -1;
   player.state.upfailed = 0;
   player.state.downfailed = 0;
   sprintf(player.state.action, "Bot ran out of UpDown options");
   return;
  }

  if(player.state.doubleann) //Steve 4/3/99 - Moved DblAnn check here
  {
   sprintf(player.state.action, "Bot is Double Annoyed");
   player.goal *= -1;
   player.state.upfailed = 0;
   player.state.downfailed = 0;
   return;
  }

  if(!player.state.resolute && !player.state.annoyed)      
    {                            
     sprintf(player.state.action, "Bot is not resolute, and not annoyed");  
     player.goal *= -1;         
     return;                    
    }                            

  if(player.state.thrifty && !player.state.annoyed)   
    {
     a = A_ResolveGoal(-1);
     if(a)
     {
      sprintf(player.state.action, "Bot is Thrifty");  
      return;
     }
    }

  if(player.state.updown && player.state.annoyed)  
    {
     sprintf(player.state.action, "Bot is Updown, but Annoyed");
     A_MoveDown(); 
     return;
    }

  else if(player.state.updown && player.state.upfailed) 
   {
    sprintf(player.state.action, "Bot is Updown, but UpFailed");
    A_MoveDown();  
    return;
   }

  else if(player.state.updown) 
   {
    sprintf(player.state.action, "Bot is Updown");
    A_MoveUp();  
    return;
   }
 
  if (!player.state.updown && player.state.annoyed) 
     {
      sprintf(player.state.action, "Bot is not Updown, but Annoyed");
      A_MoveUp();
      return;
     }

  else if (!player.state.updown && player.state.downfailed)
    {
     sprintf(player.state.action, "Bot is not Updown, but DownFailed");
     A_MoveUp(); 
     return;
    }

  else if (!player.state.updown)
    {
     sprintf(player.state.action, "Bot is not Updown");
     A_MoveDown(); 
     return;
    }

 }

 else 
  {
   sprintf(player.state.action, "Last move didn't fail");
   a = A_ResolveGoal(1);
  }
}

void A_AiLoop( void )
{
 int i; 
 i = 0;
  
 //Changes goal if current goal is resolved

 A_CheckGoal();

 //Steve 3/19 - Fix of failedspec 1 turn after annoyance

 failedspec = 0;

 do
 {

  i++;
  if(i > 13) 
  {
   gamecount++; 
   return;	
  }		
		
  up=0;
  down=0; //Steve - Reset whether it just used up or down

  if(player.state.upfailed || player.state.downfailed) //Remove upfailed and downfailed if opp axis has changed
  {
   if(player.goal == 1 && failedloc.x != player.loc.x) 
   { 
    player.state.upfailed = 0;
    player.state.downfailed = 0;
   }
  
   else if(player.goal == -1 && failedloc.y != player.loc.y) 
   {
    player.state.upfailed = 0;
    player.state.downfailed = 0;
   }
  }

  //Get the bot's 'temperament'

  player.state.thrifty = A_CheckTrait(player.ai.thriftyness);
  player.state.updown = A_CheckTrait(player.ai.updown);
  player.state.resolute = A_CheckTrait(player.ai.resolutness);
  player.state.annoyed = A_CheckAnnoyance();
  player.state.doubleann = A_CheckDoubleAnnoyance();

  //reset the location you're starting from

  nextloc = player.loc;

  if(player.state.annoyed)
   failedspec = 1;
  else
   failedspec = 0;

  A_BotThink();

  if(defaults.debug)
  {
   I_AIDebug( player.state.action );
   I_AIDebug( "Goal" );
   I_IntAIDebug( player.goal );
   I_AIDebug( "Playerloc x,y" );
   I_IntAIDebug( player.loc.x );
   I_IntAIDebug( player.loc.y );
   I_AIDebug( "Nextloc x,y" );
   I_IntAIDebug( nextloc.x );
   I_IntAIDebug( nextloc.y );
  }

  A_LogMove();

  //Steve - Logmove for double annoyance

  if(player.state.annoyed)
   A_LogAnnoyedMove();

  //and there you have it, did it work?

  failed = A_Lookahead();

  if(defaults.debug)
  {
   I_AIDebug( "Failed" );
   I_IntAIDebug( failed );
   I_AIDebug( "FailedSpec" );
   I_IntAIDebug( failedspec );
   I_AIDebug( "\n" );
  }

  if(failed && (up || down)) //Steve 4/3/99 - New UpDown rehash check
  {
   if(up)
    player.state.upfailed = 1;
   else if(down)
    player.state.downfailed = 1;
  
   if(player.goal == -1)
    failedloc. y = player.loc.y;
   else if(player.goal == 1)
    failedloc.x = player.loc.x;
  }

  if(defaults.wait) 
   sleep(defaults.waitime);

  D_DrawMap();

 }
 while(failed);

 player.loc = nextloc; 

}
 
