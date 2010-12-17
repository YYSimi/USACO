/*
ID:  ysimidjiy1
LANG: C
TASK: crypt1
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXGENS 10000

int generate(int a, int b, int c, int d, int e, int result[3],
	 int *nums, int maxnums) {
  if (a == 0) return 0;
  if (d == 0) return 0;
  int x = 100*a + 10*b + c;
  int y = x*d;
  int i, flag = 0;
  char filter[50];
  char *tester = filter;

  result[0] = y;
  result[1] = x*e;
  result[2] = y*10+result[1];
  //printf("generated %d%d%d*%d%d = %d(0) + %d = %d\n", a, b, c, d, e,
  // result[0], result[1], result[2]); 

  if (999 < result[0]) return 0;
  if (999 < result[1]) return 0;
  if (9999 < result[2]) return 0;

  sprintf(filter, "%d%d%d", result[0], result[1], result[2]);
  while (*tester != 0) {
    for (i = 0; i < maxnums; i++) {
      if (*tester == nums[i]) {
	flag = 1;
	break;
      }
    }
    if (flag == 0) {
      //  printf("returning early!\n\n");
      return 0;
    }
    flag = 0;
    tester++;
  }
  //  printf("total++\n\n");
  return 1;
}

int main(){

  FILE *fin = fopen("crypt1.in", "r");
  FILE *fout = fopen("crypt1.out", "w");

  int maxnums;
  int nums[10];
  int numsfast[10];
  int results[3];
  int i, j, k, l, m;
  int solutions = 0;

  fscanf(fin, "%d\n", &maxnums);
  for (i = 0; i<maxnums; i++) fscanf(fin, "%d ", &nums[i]);
  for (i = 0; i<maxnums; i++) numsfast[i] = nums[i] + 48;

  for (i = 0; i<maxnums; i++){
    for (j = 0; j<maxnums; j++) {
      for (k = 0; k<maxnums; k++) {
	for (l = 0; l < maxnums; l++) {
	  for (m = 0; m < maxnums; m++) {
	    solutions += generate(nums[i], nums[j], nums[k],
				  nums[l], nums[m], results,
				  numsfast, maxnums);
	    
	  }
	}
      }
    }
  }

  
  fprintf(fout, "%d\n", solutions);
  exit(0);

}
