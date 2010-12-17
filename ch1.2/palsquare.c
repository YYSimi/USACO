/*
ID:  ysimidjiy1
LANG: C
TASK: palsquare
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int smartpow(int a, int b) {

  int c = 1;

  if (b == 0) return 1;
  while (b > 1) {

    if (b%2) {
      c*=a;
      //      printf("c is %d\n", c);
      b--;
    }
    else {
      a*=a;
      // printf("a is %d\n", a);
      b = b/2;
    }

  }
  //printf("answer:  %d\n", a*c);
  return a*c;
}

void convertbase(char *result, int num, int base, char *map);
int testresult(char *result);

int main(){

  char result[20]; //We will store the current square here.
  char initial[20]; //we will need to convert the initial numbers too
  FILE *fin = fopen("palsquare.in", "r");
  FILE *fout = fopen("palsquare.out", "w");
  int base, square, current=1, i = 0, logger, placeval;

  char map[21] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};

  fscanf(fin, "%d\n", &base);
  //printf("opti: %f\n", opti);

  while (current < 301) {
    // printf("Current is: %d, base is: %d\n", current, base);
    convertbase(result, current*current, base, map);
    if (testresult(result)) {

      convertbase(initial, current, base, map);
      fprintf(fout, "%s %s\n", initial, result);
    }

    current++;
  }


  exit(0);

}


void convertbase(char *result, int num, int base, char *map){

  int logger = (int)floorf(logf(num)/logf(base));
  int cur = num;
  int track = 0;
  int exp = smartpow(base, logger);
  int i = 0; //increments where we are writing our digit

  while (logger >= 0){
    
    //This next routine always overshoots by one.
    while(cur >= 0) {
      cur -= exp;
      track++;
    }
    cur += exp;
    track--;

    //    printf("writing %c to result[%d]\n", map[track], i);
    result[i] = map[track];
    i++;
    track = 0;
    logger--;
    exp = smartpow(base, logger);

  }
  result[i] = '\0';

}

int testresult(char *result) {

  int start=0, finish = strlen(result)-1;
  while(start < finish) {
    if (result[start] != result[finish]) return 0;
    start++;
    finish--;
  }

  return 1;

}
