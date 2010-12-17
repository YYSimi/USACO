/*
ID:  ysimidjiy1
LANG: C
TASK: test
*/

#include <stdio.h>

int main(){

  int a;
  int b;
  FILE *fin = fopen("test.in", "r");
  FILE *fout = fopen("test.out", "w");
  fscanf(fin, "%d %d", &a, &b);
  fprintf(fout, "%d\n", a+b);

  exit(0);

}
