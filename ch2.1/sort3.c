/*
ID:  ysimidjiy1
LANG: C
TASK: sort3
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXREC 1000


void partition(char recs[MAXREC], int parts[4], int max){

  int a;

  for (a = 0; a < max; a++){
    
    if (recs[a] == 1) parts[1]++;
    else if (recs[a] == 2) parts[2]++;
    else (parts[3]++);
  }
  
  return;

}

void swap(char recs[MAXREC], int parts[4], int *swaps, int max){

  int walker;
  int scout;

  //swap 2s in the 1s section
  scout = parts[1];
  for (walker = 0; walker < parts[1]; walker++){

    //we found a 2 in the 1's section
    if (recs[walker] == 2) {
      for (; (recs[scout] != 1) && scout < parts[1] + parts[2]; scout++){
	continue;
      }
      //swap if we found a 1
      if (recs[scout] == 1){
	recs[walker] = 1; recs[scout] = 2;
	(*swaps)++;
      }
      //give up forever if we couldn't find a 1 in the 2's section
      else {
	break;
      }
    }
  }

  //swap 3s in the 1s section
  scout = parts[1] + parts[2];
  for (walker = 0; walker < parts[1]; walker++){

    //we found a 3 in the 1's section
    if (recs[walker] == 3) {
      for (; (recs[scout] != 1) && scout < max; scout++){
	continue;
      }
      //swap if we found a 1
      if (recs[scout] == 1){
	recs[walker] = 1; recs[scout] = 3;
	(*swaps)++;
      }
      //give up forever if we couldn't find a 3 in the 2's section
      else {
	break;
      }
    }
  }


  //swap 3s in the 2s section
  scout = parts[1] + parts[2];
  for (walker = parts[1]; walker < parts[2] + parts[1]; walker++){

    //we found a 3 in the 2's section
    if (recs[walker] == 3) {
      for (; (recs[scout] != 2) && scout < max; scout++){
	continue;
      }
      //swap if we found a 2
      if (recs[scout] == 2){
	recs[walker] = 2; recs[scout] = 3;
	(*swaps)++;
      }
      //give up forever if we couldn't find a 2 in the 3's section
      else {
	break;
      }
    }
  }

  printf("2 way swaps: %d\n", *swaps);

  //three-way swaps
  for (walker = 0; walker < parts[1]; walker ++){
    
    //we found a 3 in the 1's section... I guess we just add 2 to swaps.
    if(recs[walker] == 3){
      (*swaps) += 2;
    }
  }

  for (walker = parts[1] + parts[2]; walker < max; walker++){
    //we found a 1 in the 3's section... I guess we just add 2 to swaps.
    if(recs[walker] == 1){
      (*swaps) += 2;
    }

  }


    //--------------vieux code-----------------//
    /*
    if (recs[walker] == 3){
      for (scout = parts[1]; (recs[scout] != 2) && scout < parts[2]; scout++){
	continue;
      } 
      //quelle chance! we found the target... probably.
      assert(recs[scout] == 2);
    
      
    }
    
    */

  
  return;

}


void fprint_recs(char recs[MAXREC], int max, FILE *fout){

  int i;
  for (i = 0; i < max; i++){
    fprintf(fout, "%hhd\n", recs[i]);
  }

  return;

}

int main(){

  FILE *fin = fopen("sort3.in", "r");
  FILE *fout = fopen("sort3.out", "w");

  char recs[MAXREC];
  int parts[4] = {0};
  int max;
  int i;
  int swaps = 0;

  fscanf(fin, "%d\n", &max);

  for (i = 0; i < max; i++) {
    fscanf(fin, "%hhd\n", recs + i);
  }

  partition(recs, parts, max);

  printf("1: %d\n2:%d\n3:%d\n", parts[1], parts[2], parts[3]);
  
  swap(recs, parts, &swaps, max);
  fprint_recs(recs, max, stdout);
  fprintf(fout, "%d\n", swaps);

  exit(0);

}
