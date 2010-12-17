/*
ID:  ysimidjiy1
LANG: C
TASK: clocks
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXCLOCKS 400000

typedef struct clock_state {

  char clocks[3][3];
  char moves[3][3];
  char maxi, maxj;

} clock_state;

//*****************Functions*******************//


void print_states(char clocks[3][3]){

  int i; int j;
  for (i = 0; i<3; i++) {
    for (j=0; j<3; j++) {
      printf("%d ", clocks[i][j]);  
    }
    printf("\n");
  }
  printf("\n");
}

void printf_final(char clocks[3][3], FILE *target){

  int i, j, k, flag=0;

  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      for (k=clocks[i][j]; k>0; k--){
	if (flag == 0) {
	  fprintf(target, "%d", 3*i+j+1);
	  flag=1;
	}
	else fprintf(target, " %d", 3*i+j+1);
      }
    }
  }
  fprintf(target, "\n");
}

inline void rotate_clock(char clocks[3][3], int i, int j) {
  clocks[i][j] = (clocks[i][j]+1)%4;
}

inline void rotate_clock_rev(char clocks[3][3], int i, int j) {
  clocks[i][j] = (clocks[i][j]+3)%4;
}

void rotate_clocks(char clocks[3][3], int i, int j){

  rotate_clock(clocks, i, j);
  if (i+1 < 3) rotate_clock(clocks, i+1, j);
  if (i-1 > -1) rotate_clock(clocks, i-1, j);
  if (j+1 < 3) rotate_clock(clocks, i, j+1);
  if (j-1 > -1) rotate_clock(clocks, i, j-1);
  if ( (j != 1) && (i != 1) ) rotate_clock(clocks, 1, 1);
  else if ( !((j ==1) && (i==1)) ) rotate_clock_rev(clocks, 1, 1);

}

int check_next(clock_state states[10000], int *curstate, int *maxstate){

  //printf("checking next.  curstate = %d\n", *curstate);
  //print_states(states[*curstate].clocks);
  //printf("Moves were: \n");
  //print_states(states[*curstate].moves);
  //printf("\n");

  int i = 0, j=0;
  int flag = 0;
  char maxi = states[*curstate].maxi;
  char maxj = states[*curstate].maxj;


  for (i=0; i<3; i++){
    for (j = 0; j<3; j++)
      if (states[*curstate].clocks[i][j] > 0) {
	flag = 1;
	break;
      }
  }

  if (flag == 0) return 0; //Hey, everything works, we're done!

  for (i = maxi; i<3; i++) {
    for (j = 0; j<3; j++) {
      
      //assert(*maxstate < MAXCLOCKS);
      
      if ( (i == maxi) && (j < maxj)) continue;
      if (states[*curstate].moves[i][j] > 2) continue;

      (*maxstate)++;
      memcpy(states[*maxstate].clocks, states[*curstate].clocks,
	     9*sizeof(char));
      memcpy(states[*maxstate].moves, states[*curstate].moves,
	     9*sizeof(char));
      states[*maxstate].maxi = i;
      states[*maxstate].maxj = j;
      states[*maxstate].moves[i][j] = states[*curstate].moves[i][j] + 1;
      rotate_clocks(states[*maxstate].clocks, i, j);
      //printf("Created state:\n");
      //print_states(states[*maxstate].clocks);
      
    }
  }
  //printf("\n");

  return 1; //We've enqueued our states, and we are not yet done.  
}


int main(){
  
  int i, j;

  char clocks[3][3];
  
  clock_state allclocks[MAXCLOCKS];
  int curstate = 0, maxstate = 0;
  
  FILE *fin = fopen("clocks.in", "r");
  FILE *fout = fopen("clocks.out", "w");

  for (i=0; i<3; i++){
    fscanf(fin, "%hhd %hhd %hhd\n", &clocks[i][0], &clocks[i][1], &clocks[i][2]);
  }

  print_states(clocks);

  //Convert clocks to mod 4
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++){ 
      clocks[i][j] = (clocks[i][j]/3)%4;
    }
  }
  
  print_states(clocks);
  
  //Enqueue initial state
  allclocks[0].maxi = 0;
  allclocks[0].maxj = 0;
  
  for (i=0; i<3; i++){
    for(j=0; j<3; j++) { 
      allclocks[0].clocks[i][j] = clocks[i][j];
      allclocks[0].moves[i][j] = 0;
    }
  }
  
  while(check_next(allclocks, &curstate, &maxstate)) {
    curstate++;    
  }
  
  //fprintf(stdout, "done after curstate = %d attempts\n", curstate);
  //fprintf(stderr, "done after curstate = %d attempts\n", curstate);

  print_states(allclocks[curstate].moves);
  printf_final(allclocks[curstate].moves, fout);


  /*  fprintf(stderr, "1: %d\n2: %d\n3: %d\n4: %d\n5: %d\n6: %d\n7: %d\n8: %d\n9: %d\n",
	 allclocks[curstate].moves[0][0], allclocks[curstate].moves[0][1],
	 allclocks[curstate].moves[0][2], allclocks[curstate].moves[1][0],
	 allclocks[curstate].moves[1][1], allclocks[curstate].moves[1][2],
	 allclocks[curstate].moves[2][0], allclocks[curstate].moves[2][1],
	 allclocks[curstate].moves[2][2]);
  */
  exit(0);

}
