/*
ID:  ysimidjiy1
LANG: C
TASK: milk3
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MG MAXGALS
#define MAXGALS 21

typedef struct bucket{

  char max;
  char contains;
} bucket;

//pour a INTO b
void pour(bucket *a, bucket *b){

  //printf("pouring from in (cur, max) form:  (%d, %d) --> (%d, %d)\n",
  // a->max, a->contains, b->max, b->contains);

  //Case b->remains > a->contains
  if ((b->max - b->contains) > a->contains) {
    b->contains += a->contains;
    a->contains = 0;
  }
  //Case b->remains <= a->contains
  else {
    a->contains -= (b->max - b->contains);
    b->contains = b->max;
    
  }

}

void handle_state(bucket *a, bucket *b, bucket *c, char states[MG][MG][MG],
		  char sols[MG] ){

  int undo_a = a->contains, undo_b = b->contains, undo_c = c->contains;
  
  if (states[a->contains][b->contains][c->contains]) {
    if (a->contains == 0) sols[c->contains] = 1;
    return;
  }
  states[a->contains][b->contains][c->contains] = 1;
  
  pour(a, b);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  pour(a, c);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  pour(b, a);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  pour(b,c);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  pour(c,a);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  pour(c,b);
  handle_state(a, b, c, states, sols);
  a->contains = undo_a; b->contains = undo_b; c->contains = undo_c;

  states[a->contains][b->contains][c->contains] = 0;
  return;

}

int main(){

  char states[MAXGALS][MAXGALS][MAXGALS] = {0};
  char sols[MAXGALS] = {0};
  
  FILE * fin = fopen("milk3.in", "r");
  FILE * fout = fopen("milk3.out", "w");

  bucket a, b, c;
  int i;
  int flag = 0;

  fscanf(fin, "%hhd %hhd %hhd\n", &a.max, &b.max, &c.max);
  c.contains = c.max;
  a.contains = 0;
  b.contains = 0;
  
  //states[a.contains][b.contains][c.contains] = 1;

  handle_state(&a, &b, &c, states, sols);

  for(i = 0; i<MAXGALS; i++){
    if (sols[i]){
      if (flag) 
	fprintf(fout, " %d", i);
    
      else {
	flag = 1;
	fprintf(fout, "%d", i);
      }
    } 
  }
  fprintf(fout, "\n");

  exit(0);

}
