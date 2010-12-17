/*
ID:  ysimidjiy1
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXTIME 1000000
#define DEBUG1

void addfarmer(int start, int end, char *time){

  while(start < end) {
    time[start] = 1;
    start++;
  }
}

void countmax(int *contig, int *empty, char *time, int end, int start) {

  int i=start;
  int count=0;

  #ifdef DEBUG
  FILE *output = fopen("blah.txt", "w");
  #endif

  while (i<MAXTIME){
    #ifdef DEBUG
    printf("loop at countmax, i = %d\n", i);
    #endif

    if (i == end) break;

    //go through times when no one is milking
    while (time[i] == 0 && i<MAXTIME && i != end){
      count++;
      i++;
      #ifdef DEBUG
      fprintf(output, "empty %d count = %d\n", i, count);
      #endif
    }
    if (count > *empty){
      *empty = count;
    }
    count = 0;

    while (time[i] == 1 &&  i<MAXTIME && i != end) {
      count++;
      i++;
      #ifdef DEBUG
      fprintf(output, "milking %d count = %d\n", i, count);
      #endif
    }
    if (count > *contig) {
      *contig = count;
    }
    count = 0;


#ifdef DEBUG
  printf("and at the end of the day, i=%d\n", i);
#endif
  
   
  }

}

int main(){

  int nf; //number of farmers
  int fp = 0; //farmers processed
  int start, end; //start and end times for current farmer
  int contig=0, empty=0;
  int curend=0, curstart=MAXTIME; //last and first time that a farmer milks

  FILE *input = fopen("milk2.in", "r");
  FILE *output = fopen("milk2.out", "w");

  char *time = calloc(MAXTIME, sizeof(char)); //total amount of time.
  
  fscanf(input, "%d\n", &nf);

  while(fp < nf) {
    printf("loop at addfarmer in main\n");
    fscanf(input, "%d %d\n", &start, &end);
    if (end > curend) curend = end;
    if (start < curstart) curstart = start;
    addfarmer(start, end, time);
    fp++;
  }

  time[curend] = 2;

  countmax(&contig, &empty, time, curend, curstart);
  fprintf(output, "%d %d\n", contig, empty);
  exit(0);

}
