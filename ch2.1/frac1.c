/*
ID:  ysimidjiy1
LANG: C
TASK: frac1
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_DENOM 160

//Takes two ints, a > b, and tells us if they are relatively prime.
int rp_certificate(int a, int b){

  int k = 1;

  if (b == 0 && a != 1) {
    return 0;
  }
  if (b == 1){
    return 1;
  }

  
  while (k*b <= a){
    k++;
  }

  return rp_certificate(b, a-(k-1)*b);

}

int generate_fracs(unsigned char fracarray[MAX_DENOM*MAX_DENOM][2],
		   unsigned char max){
  
  int i, j; //i is the denomerator, j is the numerator
  int fa_index = 0;

  for (i = 1; i <= max; i++){
    for (j = 1; j < i; j++){
      //printf("testing %d/%d\n", j, i);

      if (rp_certificate(i, j)){
	//printf("adding %d/%d\n", j, i);
	fracarray[fa_index][0] = j;
	fracarray[fa_index][1] = i;
	fa_index++;
      }
      
    }

  }

}


void print_array(unsigned char fracarray[MAX_DENOM*MAX_DENOM][2],
		 FILE *fout){

  int fa_index = 0;

  while(fracarray[fa_index][0] != 0){
    fprintf(fout, "%d/%d\n", fracarray[fa_index][0], fracarray[fa_index][1]);
    fa_index++;
  }

}

int compar(const void *a, const void *b){

  unsigned char *i = (unsigned char *)a;
  unsigned char *j = (unsigned char *)b;

  return (i[0]*j[1] - i[1]*j[0]);

}

int main(){

  FILE *fin = fopen("frac1.in", "r");
  FILE *fout = fopen("frac1.out", "w");
  int max;

  unsigned char frac_array[MAX_DENOM*MAX_DENOM][2];

  fscanf(fin, "%d\n", &max);

  generate_fracs(frac_array, max); 
  qsort(frac_array, MAX_DENOM*MAX_DENOM, 2*sizeof(unsigned char), compar);
  fprintf(fout, "0/1\n");
  print_array(frac_array, fout);
  fprintf(fout, "1/1\n");


  exit(0);

}





















/*
//DFS takes two arguments.  Current frac, previous frac.

int DFS(char left[2], char right[2], int denom, int max, FILE *fout,
	char temp1[2], char temp2[2]){

  char next[2] = {1, denom};  

  //Calculate our initial numerator.
  while (next[0]*left[1] <= next[1]*left[0]){
    next[0]++
  }

  while (next[0]*right[1] < next[1]*right[0]) {
    
    DFS();
    fprintf("%d/%d\n", next[0], next[1]);
    DFS();

  }



}
*/

