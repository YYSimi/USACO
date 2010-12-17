/*
ID:  ysimidjiy1
LANG: C
TASK: friday
*/

#include <stdio.h>


enum MONTH {
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};
  
int main(){
  
  enum MONTH month = JANUARY;
  int i = 0;
    
  int count[7] = {1, 0, 0, 0, 0, 0, 0};
  
  int year = 1900, last13th = 0, tocheck;
  
  FILE *input = fopen("friday.in", "r");
  FILE *output = fopen("friday.out", "w");
  
  fscanf(input, "%d", &tocheck);

  tocheck = tocheck+1899;

  if (tocheck < 1900) {
    fprintf(output, "0 0 0 0 0 0 0\n");
    exit(0);
  }

  while(year <= tocheck) {

    i++;
    //printf("%dth time around\n", i);
    
    switch (month) {
    case SEPTEMBER:
    case APRIL:
    case JUNE:
    case NOVEMBER:
      last13th = (last13th +2) %7;
      break;
    case FEBRUARY:
      printf("feb!\n");
      //if it is a leap year (divisible by 4, but not 100)
      if ( !(year%4) && ((year %100) || !(year %400)) ) {
	printf("leap!\n");
	last13th = (last13th + 1) %7; 
	}
      //otherwise, 28 days, so do nothing.
      break;
    case DECEMBER:
      last13th = (last13th + 3) %7;
      year++;
      break;
    default: 
      last13th = (last13th +3) %7;
    }
    
    month = (month + 1) %12;
    count[last13th]++;
    //printf("inc %d!\n", last13th);
  }
  
  count[last13th]--;
  fprintf(output, "%d %d %d %d %d %d %d\n", count[0], count[1], count[2],
	  count[3], count[4], count[5], count[6]);
  exit(0);
  
  
}
