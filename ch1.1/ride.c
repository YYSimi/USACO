/*
ID:  ysimidjiy1
LANG: C
TASK: ride
*/

#include <stdio.h>

int main(){

  char buf;
  int comet = 1;
  int group = 1;

  FILE *input = fopen("ride.in", "r");
  FILE *output = fopen("ride.out", "w");

  fscanf(input, "%c", &buf);
  do {
    buf -= 64;
    comet *= buf;
    fscanf(input, "%c", &buf);    
  } while(buf != '\n');  

  fscanf(input, "%c", &buf);
  do {
    buf -= 64;
    group *= buf;
    fscanf(input, "%c", &buf);    
  } while(buf != '\n');

  if ( (group %47) == (comet % 47)) {
    fprintf(output, "GO\n");
  }
  else
    fprintf(output, "STAY\n");

  exit(0);

}
