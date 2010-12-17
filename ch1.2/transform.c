/*
ID:  ysimidjiy1
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rot90(char *figure, char *trans, int n){ //rotate 90
  
  int i=0, j=0; int k = 0;
  
  while (i<n) {
    while(j<n) {
      trans[i + n*j] = figure[j+n*(n-i-1)];
      j++;
    }
    j=0;
    i++;
  }

}

void flip(char *figure, char *trans, int n){ //flip.
  
  int i=0, j=0;
  while (i<n) {
    
    while(j<n) {
      trans[(n-i-1)+n*(j)] = figure[i+n*j];
      //      printf("j=%d, i=%d, sending %d to %d\n", j,i,i+n*j, i+n*(n-j-1)); 
      j++;
      //printf("j=%d, n=%d\n", j, n);
    }
    i++;
    j=0;
    //    printf("i=%d, n=%d\n", i, n);
  }
}


int runtests(char *figure, char *goal, char *trans, int n){

  printf("startfigure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure, trans, n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 1;
  else strncpy(figure, trans, n*n);
 
  printf("rot90figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure, trans, n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 2;
  else strncpy(figure, trans, n*n);

  printf("rot180figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure,trans,n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 3;
  else strncpy(figure, trans, n*n);
  
  printf("rot270figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure,trans,n); //back to the start
  strncpy(figure, trans, n*n);

  printf("rot360figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  flip(figure, trans, n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 4;
  else strncpy(figure, trans, n*n);  

  printf("flipfigure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure, trans, n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 5;
  else strncpy(figure, trans, n*n);
 
  printf("fliprot90figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure, trans, n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 5;
  else strncpy(figure, trans, n*n);

  printf("fliprot180figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure,trans,n);
  if (strncmp(trans, goal, n*n) == 0)  
    return 5;
  else strncpy(figure, trans, n*n);
  
  printf("fliprot270figure:\n%s\ngoal:\n%s\n\n", figure, goal);

  rot90(figure,trans,n); //back to the start
  strncpy(figure, trans, n*n);
  flip(figure, trans, n);
  strncpy(figure, trans, n*n);

  printf("origfigure:\n%s\ngoal:\n%s\n\n", figure, goal);
    if (strncmp(trans, goal, n*n) == 0)  
    return 6;
    else return 7;

  return 5;

}


int main(){

  FILE *input = fopen("transform.in", "r");
  FILE *output = fopen("transform.out", "w");
  int i = 0; //counter
  int j = 0; //counter
  int n; //number of lines
  fscanf(input, "%d\n", &n);
 
  char *figure = malloc(n*n*sizeof(char) +1); //n by n array, 0 index, an+b format
  char *goal = malloc(n*n*sizeof(char) +1); //our target transformation
  char *trans = malloc(n*n*sizeof(char) +1); //result of the transformation we do
  
  char temp = 'a';
  
  figure[n*n*sizeof(char)] = '\0';
  goal[n*n*sizeof(char)] = '\0';
  trans[n*n*sizeof(char)] = '\0';

  while (j < n) {

    while((temp = fgetc(input)) != '\n') {
      //printf("processing %c", temp);
      printf("i is %d\n", i);
      figure[i] = temp;   
      i++;
      if (i >= n*n) break;
      printf("figure:\n%s\n", figure);
    }
    j++;
    
  }
  j = -1;
  i = 0;
  while (j<n) {
    while((temp = fgetc(input)) != '\n') {
      goal[i] = temp;
      i++;
      printf("Goal:\n%s\n", goal);
      if (i >= n*n) break;
    }
    j++;
    printf("j is %d\n", j);
  }
  
  printf("d\n");
  
  //-----------------------------------------------//
  //                   Run Tests!                  //
  //-----------------------------------------------//

  fprintf(output, "%d\n", runtests(figure, goal, trans, n));

  printf("e\n");

  exit(0);

}
