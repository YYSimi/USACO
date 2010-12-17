/*
ID:  ysimidjiy1
LANG: C
TASK: numtri
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXROWS 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))


void process_row(char tri[MAXROWS][MAXROWS], int bot[MAXROWS], int bot_row){

  int i;
  int new_row = bot_row-1;
  for (i = 0; i<bot_row; i++){
    
    //printf("Generating (%hhd, %hhd) = %hhd from %d and %d\n",
    // new_row, i, tri[new_row][i], bot[i], bot[i+1]); 
    
    bot[i] = MAX(bot[i], bot[i+1])+tri[new_row][i];
  }

  return;
}

int main(){

  char tri[MAXROWS][MAXROWS]; //[rows][columns]
  int bot[MAXROWS];
  int numrows;
  int i, j;
  
  FILE *fin = fopen("numtri.in", "r");
  FILE *fout = fopen("numtri.out", "w");

  fscanf(fin, "%d\n", &numrows);

  assert(numrows <= MAXROWS);

  for (i = 0; i<numrows; i++){
    
    for (j = 0; j<=i; j++)  {
      fscanf(fin, "%hhd ", &tri[i][j]);
    }
    fscanf(fin, "\n");
  }

  for (i = 0; i<numrows; i++){
    bot[i] = tri[numrows-1][i];
  }

  for (i = numrows-1; i >= 0; i--){
    process_row(tri, bot, i);
  }

  fprintf(fout, "%d\n", bot[0]);

  exit(0);

}
