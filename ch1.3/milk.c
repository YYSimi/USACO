/*
ID:  ysimidjiy1
LANG: C
TASK: milk
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXFARMERS 5000
#define MIN(a,b) (((a)>(b)) ? (b) : (a))

int compar(int **a, int **b){

  //  printf("**a is %d, **b is %d, **a - **b is %d\n", **a, **b, **a-**b);
  return **a - **b;

}

int main(){

  FILE *fin = fopen("milk.in", "r");
  FILE *fout = fopen("milk.out", "w");
  
  //  int farmarray[MAXFARMERS][2]; //fa[0][n] is price, fa[1][n] is number
  int bottles, farmers, totalcost=0;
  int i=0, temp = 0;
  fscanf(fin, "%d %d\n", &bottles, &farmers);
  
  int **pointers = calloc(farmers, sizeof(int *));
  for(temp = 0; temp<farmers; temp++) {

    pointers[temp] = malloc(2*sizeof(int));
    fscanf(fin, "%d %d\n", pointers[temp], pointers[temp]+1);
  }

  //  for(temp = 0; temp<farmers; temp++)
  //printf("%d %d\n", *pointers[temp], *(pointers[temp]+1));


  qsort(pointers, farmers, sizeof(int*), &compar);
  //printf("--------------------------\n");
  
  //for(temp = 0; temp<farmers; temp++)
  //  printf("%d %d\n", *pointers[temp], *(pointers[temp]+1));


  while (bottles > 0) {
    //  printf("-------------------i is %d---------------\n", i);
    totalcost += MIN(bottles,*(pointers[i]+1))*(*pointers[i]);
    //printf("adding %d bottles at %d cost\n", *(pointers[i]+1), *(pointers[i]));
    bottles -= *(pointers[i]+1);
    //printf("Totalcost is %d\n", totalcost);

    i++;
  }
  
  fprintf(fout, "%d\n", totalcost);

  exit(0);

}








/*
int compar (const void *a, const void *b) {

  int ia = *(int *)a; int ib = *(int *)b;

  printf("a is %d, b is %d\n", a-b);
  printf("a-b is %d\n", a-b);
  return 1;

}
*/


  /*
  assert(farmers < MAXFARMERS);
  for (temp = 0; temp < farmers; temp++){
    fscanf(fin, "%d %d\n", &farmarray[temp][0], &farmarray[temp][1]);
    printf("temp is %d\n", temp);
  }
  
  for (temp = 0; temp < farmers; temp++)
    printf("%d %d\n", farmarray[temp][0], farmarray[temp][1]);
  printf("---------------------\n");

  qsort(farmarray, farmers, sizeof(int), &compar);
  
  for (temp = 0; temp < farmers; temp++)
    printf("%d %d\n", farmarray[temp][0], farmarray[temp][0]);

  while (bottles > 0) {
    printf("i is %d\n", i);
    totalcost += MIN(bottles,farmarray[1][i])*farmarray[i][0];
    printf("adding %d bottles at %d cost\n", farmarray[i][1], farmarray[i][0]);
    bottles -= farmarray[i][1];
   
    i++;
  }
  
  fprintf(fout, "%d\n", totalcost);

  exit(0);

}
  */
