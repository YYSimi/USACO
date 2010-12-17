/*
ID:  ysimidjiy1
LANG: C
TASK: hamming
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODES 256
#define MAX_WORDS 64

//a^b
int my_pow(int a, int b){

  int i = 0;
  int result = 1;

  for (i = 0; i <b; i++) {
    result *=a;
  }

  return result;

}

char hamming_dist(unsigned char a, unsigned char b){

  int i = 0;
  int result = 0;

  for (i = 0; i < 8*sizeof(char); i++){
    if ( (a ^ b) & 1 ){
      result++;
    }

    //printf("a: %d, b: %d, a^b: %d, (a^b) &1: %d\n", a, b, a^b, (a^b)&1);

    a = a>>1;
    b = b>>1;
  }

  return result;

}

void populate_adj(unsigned char nodes[MAX_NODES][MAX_NODES], int max_nodes){

  int i, j;

  for (i = 0; i < max_nodes; i++){
    for (j = 0; j < max_nodes; j++) {
      nodes[i][j] = hamming_dist(i, j);
      //printf("populated nodes[%d][%d] with %d\n", i, j, nodes[i][j]);
    }
  }

  return;
}

int find_words(unsigned char nodes[MAX_NODES][MAX_NODES], int max_nodes, 
		unsigned char solutions[MAX_WORDS], int max_words,
		int words_found, int prev_check, int distance){

  int i, j;
  int flag = 0;

  //printf("entering find_words.  words found:  %d\n", words_found);

  //Success?
  if (words_found == max_words){
    return 1;
  }

  for (i = prev_check; i < max_nodes; i++){
    flag = 0;
    for (j = 0; j < words_found; j++){
      if (nodes[solutions[j]][i] < distance){
	flag = 1;
	break;
      }
    }

    //Found a goodie.  Add it to the list.
    if (flag != 1){
      //      printf("goodie found!\n");
      solutions[words_found] = i;
      if ( find_words(nodes, max_nodes, solutions, max_words, words_found +1, 
		      i, distance) ){
	return 1;
      }
    }
  }
  return 0;
}

int main(){

  int i, j; //looping variables

  unsigned char nodes[MAX_NODES][MAX_NODES] = {0};
  unsigned char solutions[MAX_WORDS] = {0};

  int max_nodes = 0;
  int max_words = 0;
  int distance = 0;

  FILE *fin = fopen("hamming.in", "r");
  FILE *fout = fopen("hamming.out", "w");

  fscanf(fin, "%d %d %d\n", &max_words, &max_nodes, &distance);

  max_nodes = my_pow(2, max_nodes);

  populate_adj(nodes, max_nodes);
  printf("nodes populated.\n");
  /*
    for (i = 0; i < max_nodes; i++){
    if (nodes[0][i] >= distance){
    break;
    }
    }
  */
  //  solutions[0] = 0;
  
  find_words(nodes, max_nodes, solutions, max_words, 1, 0, distance);


  fprintf(fout, "%d", solutions[0]);
  for (i = 1; i < max_words; i++){
    fprintf(fout, " %d", solutions[i]);
    if ( !((i+1)%10) && (i+1 != max_words) ) {
      i++;
      fprintf(fout, "\n%d", solutions[i]);
    }
  }

  fprintf(fout, "\n");

  exit(0);

}
