#include <stdio.h>
#include "main.h"

int main()
{
 char c;
 int i=0,p=0;
 char input[20][80], values[20][80];
 FILE *config = fopen("ai.cfg", "rt");


 do
 {
  fgets(input[i], 20, config);
  i++;
 } while(!feof(config));

 fclose(config);

 for(p = 0; p<i; p++)
  printf("%d\n", strpbrk(input[p], '#')); 









/*
 do
 {
  c = fgetc( config );
  
  if( c == '\n' || c == '#')
   c = '\0';

  strcat(input[i], c); 

  if( c == '\0')
   i++;

 }while(!feof(config));

 defaults.startloc.x = atoi(input[0]);
 defaults.startloc.y = atoi(input[1]);
 defaults.goalloc.x = atoi(input[2]);
 defaults.goalloc.y = atoi(input[3]);
 defaults.debug = atoi(input[4]);
 defaults.startgoal = atoi(input[5]);
 defaults.counter[0] = atoi(input[6]);
 defaults.counter[1] = atoi(input[8]);
 defaults.counter[2] = atoi(input[9]);
 defaults.counter[3] = atoi(input[10]);
 defaults.counter[4] = atoi(input[11]);
 defaults.counter[5] = atoi(input[12]);
 defaults.counter[6] = atoi(input[13]);


 for(i=0; i<13; i++)
  printf("%d\n", atoi(input[i]));

*/

 return 1;
}
