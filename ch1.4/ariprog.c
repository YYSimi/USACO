/*
ID:  ysimidjiy1
LANG: C
TASK: ariprog
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXPQ 250
#define MAXSEQ 10000

int global = 0; //This is here for profiling purposes.

typedef struct pair{
  int a; //common difference
  int b; //initial element
} pair;

int compare_pair(pair *first, pair *second){
  return (first->a - second->a);
}

int main(){

  int i, j, k, l, m, n, p = 0 ;
  int seqlen;
  int flag = 0; //Flag if we need to write "NONE"
  int maxpq; //The actual maximum given to us.  maxpq satisfies maxpq <= MAXPQ.
  int maxlist; //max meaningful entry in list. 
  char vals[2*MAXPQ*MAXPQ] = {0};  //~125KB
  int list[2*MAXPQ*MAXPQ] = {0};   //~1MB
  pair foundlist[MAXSEQ];
 
  FILE *fin = fopen("ariprog.in", "r");
  FILE *fout = fopen("ariprog.out", "w");

  fscanf(fin, "%d %d\n", &seqlen, &maxpq);

  /*  //The line below is unneeded, I think...
  for (i = 0; i<=2*MAXPQ*MAXPQ; i++) {
    vals[i] = 0;
  }*/

  //This loop generates our vals array
  for (i = 0; i<=maxpq; i++) {
    for (j = 0; j<=maxpq; j++) {
      vals[i*i + j*j] = 1;
    }
  }

  //This loop generates our list "list"
  j=0;
  for (i = 0; i<=2*MAXPQ*MAXPQ; i++) {
    if(vals[i]) {
      list[j] = i;
      j++;
    }    
  } 
  maxlist = j;

  //Initialize the foundlist
  for (i = 0; i<MAXSEQ; i++) {
    foundlist[i].a = 0; foundlist[i].b = 0;
  }

  //Debugging output.
  /*
  for (i = 0; i<=maxlist; i++)
    printf("list[%d] = %d, vals[list[%d]] = %d\n", i, list[i], i, vals[list[i]]);
  */

  //Walk along our array, checking for sequences.
  for (i = 0; i<maxlist; i++){
    for (j=i+1; j<maxlist; j++) {
      //We have now chosen list[i] = c_0 and list[j] = c_1.  Scan for seqs.
      k = list[j] - list[i]; //k is the common difference
      //l is the counter for the length of the sequence we are searching for
      m = 1; //m flags success by default.  Switched to 0 on failure.
      n = list[j]; //n is the "current" element that we are examining
      //printf("testing l1[%d] = %d and l2[%d] = %d\n", i, list[i], j, list[j]);

      //Optimize inner loop.
      
      if (n+(seqlen-2)*k > 2*MAXPQ*MAXPQ) {
	break;
	}

      for(l=0; l<seqlen-2; l++){
	n += k;
	global++;
	/*
	if (n > 2*MAXPQ*MAXPQ) {
	   m = 0; break;
	}*/
	if (!vals[n]) {
	  m = 0;
	  break;
	}      
      }

      //were we successful?
      if(m) {
	flag = 1;
	foundlist[p].a = k; foundlist[p].b = list[i];
	p++;
      }
      
    }
  }
  
  qsort(foundlist, MAXSEQ, sizeof(pair), compare_pair);
  
  for (i = 0; i<MAXSEQ; i++){
    if (foundlist[i].a !=0)
      fprintf(fout, "%d %d\n", foundlist[i].b, foundlist[i].a);
  }

  if (flag ==0) fprintf(fout, "NONE\n");
  printf("Global = %d\n", global);
  exit(0);

}
