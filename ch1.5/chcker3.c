/*
ID:  ysimidjiy1
LANG: C
TASK: checker
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE_TOT 13

int update_cols(int cur_col, int cur_row, int max_size,
	       int board[MAXSIZE_TOT][MAXSIZE_TOT], int inc){

  int i;
  //printf("rowincs!\n");
  for (i = cur_col+1; i < max_size; i++){
    board[i][cur_row] += inc;
   //printf("board[%d][%d] = %d\n", i, cur_row, board[i][cur_row]);
  }

  //printf("+++Done Row incs!+++\n");
  return 1;

}

void update_diags(int cur_col, int cur_row,
		  int board[MAXSIZE_TOT][MAXSIZE_TOT], int max_size, int inc){
  //printf("Diag incs!\n");

  int i = cur_col-1;
  int j = cur_row-1;
  while(i >= 0 && j >=0){
    board[i][j] += inc;
    //printf("board[%d][%d] = %d\n", i, j, board[i][j]);
    i--; j--;
  } 

  i = cur_col-1; j = cur_row+1;
  while (i >=0 && j < max_size){
    board[i][j] += inc;
    //printf("board[%d][%d] = %d\n", i, j, board[i][j]);
    i--; j++;

  }

  i = cur_col+1; j = cur_row-1;
  while (i < max_size && j >= 0){
    board[i][j] += inc;
    //printf("board[%d][%d] = %d\n", i, j, board[i][j]);
    i++; j--;
  }
  
  i = cur_col+1; j=cur_row+1;
  while (i < max_size && j < max_size){
    board[i][j] += inc;
    //printf("board[%d][%d] = %d\n", i, j, board[i][j]);
    i++; j++;
  }

  //printf("----------------Done incing!---------------\n");

}

void scan_pos(int cur_col, int board[MAXSIZE_TOT][MAXSIZE_TOT],
	      int sols[MAXSIZE_TOT], int max_size, FILE *fout, int *flag){

  int i;

  if (cur_col == max_size){
    //print sols
    //printf("Incing flag from %d", *flag);
    (*flag) = (*flag) + 1;
    //printf(" to %d\n", *flag);
    if (*flag <= 3){
      //fprintf(fout, "flagged\n");
      for (i = 0; i < max_size; i++){
	if (i == max_size-1) fprintf(fout, "%d\n", sols[i]+1);
	else fprintf(fout, "%d ", sols[i]+1);
      }  
    }
    return;
  }
  
  for (i = 0; i<max_size; i++){
    //printf("Scanning (%d, %d)\n", cur_col, i);
    
    if ( !board[cur_col][i] ){
      //printf("Success!  board[%d][%d] = %d\n", cur_col, i, board[cur_col][i]);
      update_diags(cur_col, i, board, max_size, 1);
      update_cols(cur_col, i, max_size, board, 1);
      board[cur_col][i] = 1;
      sols[cur_col] = i;
      scan_pos(cur_col+1, board, sols, max_size, fout, flag);
      board[cur_col][i] = 0;
      update_cols(cur_col, i, max_size, board, -1);
      update_diags(cur_col, i, board, max_size, -1);
    }
    
    
    
  }



}


int main(){

  int board[MAXSIZE_TOT][MAXSIZE_TOT] = {0};
  int sols[MAXSIZE_TOT] = {0};
  
  int max_size;
  int flag = 0;

  FILE *fin = fopen("checker.in", "r");
  FILE *fout = fopen("checker.out", "w");

  fscanf(fin, "%d\n", &max_size);

  scan_pos(0, board, sols, max_size, fout, &flag);

  fprintf(fout, "%d\n", flag);
  exit(0);

}
