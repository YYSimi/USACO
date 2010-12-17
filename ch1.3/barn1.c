/*
ID:  ysimidjiy1
LANG: C
TASK: barn1
*/

#include <stdio.h>
#include <stdlib.h>

int compar(int *a, int*b) {

  return *b - *a;

}

int compar2(int *a, int*b) {

  return *a - *b;

}

int main(){

  FILE *fin = fopen("barn1.in", "r");
  FILE *fout = fopen("barn1.out", "w");

  int boards, stalls, cows;
  int temp;
  int start, end;

  fscanf(fin, "%d %d %d\n", &boards, &stalls, &cows);

  if (boards >= cows) {fprintf(fout, "%d\n", cows); exit(0);}

  int *gaps = malloc((cows-1)*sizeof(int));
  int *cowarray = malloc((cows)*sizeof(int));
 
  for (temp = 0; temp < cows; temp++){
    fscanf(fin, "%d\n", &cowarray[temp]);
  }

  for (temp = 0; temp < cows; temp++) printf("%d\n", cowarray[temp]);
  qsort(cowarray, cows, sizeof(int), &compar2);
  printf("-----------------------------\n");
  for (temp = 0; temp < cows; temp++) printf("%d\n", cowarray[temp]);
  stalls = cowarray[0];
  start = cowarray[0];
  printf("+++++++++++++++++++++++++++++++++\n");
  for (temp = 0; temp < cows-1; temp++){
    end = cowarray[temp+1];
    gaps[temp] = end-start-1;
    printf("calculating cowarray[%d] (%d) - start (%d)-1\n", temp+1, end, start);
    start = end;
  }

  for (temp = 0; temp < cows -1; temp++) printf("%d\n", gaps[temp]);

  stalls = end - stalls +1;
  qsort(gaps, cows-1, sizeof(int), &compar);
  printf("--------------------------\n");
  
  for (temp = 0; temp < cows -1; temp++) printf("%d\n", gaps[temp]);

  for (temp = 0; temp < boards-1; temp++) {
    printf("stalls is %d\n", stalls);
    stalls -= gaps[temp];
  }

  fprintf(fout, "%d\n", stalls);

  exit(0);

}
