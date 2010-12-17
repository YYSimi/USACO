/*
ID:  ysimidjiy1
LANG: C
TASK: dualpal
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
  FILE *fin = fopen("dualpal.in", "r");
  FILE *fout = fopen("dualpal.out", "w");
  int count, min, current=1, base=2, flag=0;

  char map[21] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};

  fscanf(fin, "%d %d\n", &count, &min);
  min++;

  while (count >0) {
    // printf("Current is: %d, base is: %d\n", current, base);
    
    for (base=2; base <= 10; base++) {
      convertbase(result, min, base, map);
      
      if (testresult(result) && (flag <2)) {
	printf("%s is a palindrome in base %d, so we like %d\n", result, base, min);
	flag++;
      }
    }

    if (flag == 2) {
      fprintf(fout, "%d\n", min);
      count--;
    }

    flag=0;
    min++;
    printf("count is %d\n", count);
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
