/*
ID:  ysimidjiy1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAXPALS 100000
#define MAXDIGS 9

//a^b
int stupid_exp(int a, int b){

  int i;
  int result=1;
  for (i = 0; i<b; i++){
    result *= a;
  }

  return result;
}

void generate_pals_size(int *palstart, int total_digits, int cur_digit
			){

  //printf("Entered Generate_pals_size\n");

  if (cur_digit*2 > (total_digits +1)) {
    return;
  }

  int total_nums = stupid_exp(10, (total_digits + (total_digits %2))/2);
  int i,j;
  //int shazzam;
  int flag = (cur_digit*2 == total_digits+1); //1 iff cur == "middle" digit.
  //printf("Cur_digit: %d, total_digits: %d, flag: %d\n",
  // cur_digit, total_digits, flag);

  for (i = 0; i < 10; i++){
    for (j = i*(total_nums/stupid_exp(10,cur_digit));
	 j < (i+1)*(total_nums/stupid_exp(10,cur_digit));
	 j+= 1) {
      if (!flag){
	//printf("flagged!\n");
	palstart[j] += i*stupid_exp(10,cur_digit-1);
	palstart[j] += i*stupid_exp(10, total_digits - cur_digit);
      }
      else {
	//printf("Not flagged!\n");
	palstart[j] += i*stupid_exp(10, cur_digit-1);
      }
      //printf("generated %d\n", palstart[j]);
    }
  }


  for (i = 0; i<10; i++){

    generate_pals_size(palstart+i*(total_nums/stupid_exp(10, cur_digit)),
				   total_digits, cur_digit+1);
  }

  return;
}

int stupid_prime(int a){

  int i;

  for (i = 2; i<=sqrt(a); i++)
    if (!(a%i)) return 0;

  return 1;
}

void generate_pals(int pals[MAXPALS]){

  int i;
  int *palstart = pals;

  for (i = 1; i <= MAXDIGS-1; i++){
    generate_pals_size(palstart, i, 1);
    palstart+=stupid_exp(10, (i+(i%2))/2);
  }

}

		   

int main(){

  int pals[MAXPALS] = {0};
  int i = 0;
  int a; int b;
  
  FILE *fin = fopen("pprime.in", "r");
  FILE *fout = fopen("pprime.out", "w");

  fscanf(fin, "%d %d\n", &a, &b);

  generate_pals(pals);

  while(i < 22222){
    if (a > pals[i]) {
      i++;
      continue;
    }
    if (b < pals[i]) {
      i++;
      continue;
    }
    if (stupid_prime(pals[i]))
      fprintf(fout, "%d\n", pals[i]);
    //printf("%d: %d\n", pals[i], stupid_prime(pals[i]));
    i++;
  }

  exit(0);

}
