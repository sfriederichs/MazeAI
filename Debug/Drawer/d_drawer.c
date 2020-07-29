#include <stdio.h>
#include <conio.h>
#include "main.h"

int main(void)
{
 int i,p;

 FILE *bah = fopen("drawer.dbg", "at+");

 sleep(5);
 clrscr();
 gotoxy(1,1);

 for(p=0;p<58;p++)
  printf("a");
 
 gotoxy(1,2);



 for(p=0;p<22;p++)
  printf("a");  

/*
 for(i=1;i<22;i++)
 {
  for(p=1;p<22;p++)
  {
   printf("a");
   fprintf(bah,"%2d,%2d ",p,i);
   sleep(1);
  }

 gotoxy(1,i);
 fprintf(bah,"\n");
 }
*/

 fclose(bah);

 return 1;
}