#include <stdio.h>
#include "main.h"

int main()
{
 int i=-1,p=0,f;
 char input[20][80], file[20];
 FILE *config = fopen("ai.cfg", "rt");

 do
 {
  fgets(file, 20, config);
  f = strchr(file, '#');
  if(!f)
  {
   i++;
   strcpy(input[i], file); 
  }
 } while(!feof(config));

 fclose(config);

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

 return 1;
}
