/*
ID:  ysimidjiy1
LANG: C
TASK: holstein
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXVITS 25
#define MAXFEEDS 15



int DFS(char used[MAXFEEDS], int fed[MAXVITS], int feeds[MAXFEEDS][MAXVITS], 
	int maxfeeds, int maxvits, int lastfed, char sols[MAXFEEDS],
	int *sol_num){

  //printf("\nEntering DFS\n");

  int i, j;
  int flag = 0;

  //testing for success (used up all vitamins)
  for (i = 0; i<maxvits; i++){
    //printf("fed[%d] is %d\n", i, fed[i]);
    if (fed[i] > 0){
      flag = 1;
      break;
    }
  }

  //Success!  No more vitamins!
  if (flag == 0) {
    j = 0;
    for (i = 0; i < maxfeeds; i++){
      //printf("used[%d] = %d\n", i, used[i]);
      if (used[i]){
	j++;
      }
    }
    
    printf("j: %d, sol_num: %d\n", j, *sol_num);

    if (j < *sol_num) {
      //printf("Strcpy time!\n");
      flag = 2;
      *sol_num = j;
      memcpy(sols, used, maxfeeds);
    }
    
    if (j == *sol_num){
      for (i = 0; i < maxfeeds; i++){
	if (used[i] > sols[i]){
	  flag = 2;
	  break;
	}
	if (sols[i] > used[i]){
	  flag = 3;
	  break;
	}
      }
    }

    if (flag == 2){
      //printf("Strcpy time!\n");
      memcpy(sols, used, maxfeeds);
    }
    return;
  }

  //printf("passed Success test\n");

  //Testing for failure (used up all feeds)
  flag = 0;
  for (i = lastfed; i < maxfeeds; i++){
    //printf("Entered lastfed loop\n");
    if (used[i] ==0) {
      flag = 1;
      break;
    }
  }

  //failure.  We've used up all of our feeds.
  if (flag == 0) {
    return 0;
  }

  //printf("Entering unused feeds loop\n");

  //Loop over the unused feeds
  for (i = lastfed; i < maxfeeds; i++){
    
    for (j = 0; j < maxvits; j++){
      //printf("Setting fed[%d] = %d to be -= feeds[%d][%d] = %d\n", j, 
      //     fed[j], i, j, feeds[i][j]);
      fed[j] -= feeds[i][j];
    }

    used[i] = 1;
    DFS(used, fed, feeds, maxfeeds, maxvits, i+1, sols, sol_num);
    used[i] = 0;

    for (j = 0; j < maxvits; j++){
      fed[j] += feeds[i][j];
    }
  }
}
	


int main(){

  int maxvits, maxfeeds;
  char feeds_used[MAXFEEDS] = {0};
  int vitamins_needed[MAXVITS] = {0};
  int feeds[MAXFEEDS][MAXVITS] = {0};
  int i, j;
  int sol_num = 100000;
  char sols[MAXFEEDS] = {0};

  FILE *fin = fopen("holstein.in", "r");
  FILE *fout = fopen("holstein.out", "w");


  fscanf(fin, "%d\n", &maxvits);
  for (i = 0; i < maxvits; i++){
    fscanf(fin, "%d   ", &vitamins_needed[i]);
  }

  fscanf(fin, "\n%d\n", &maxfeeds);

  for (j = 0; j < maxfeeds; j++){
    for (i = 0; i < maxvits; i++){
      fscanf(fin, "%d    ", &feeds[j][i]); 
    }
    fscanf(fin, "\n");
  }

  DFS(feeds_used, vitamins_needed, feeds, maxfeeds,
      maxvits, 0, sols, &sol_num);

  fprintf(fout, "%d", sol_num);
  
  j = 0;
  for (i = 0; j < sol_num; i++) {
    if (sols[i] == 1){
      fprintf(fout, " %d", i+1);
      j++;
    }
  }
  fprintf(fout, "\n");

  exit(0);

}
