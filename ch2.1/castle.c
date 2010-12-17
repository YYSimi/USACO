/*
ID:  ysimidjiy1
LANG: C
TASK: castle
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50
#define MAX_AREA 50*50

#define MASK_W 0x1  //Mask West
#define MASK_N 0x2  //Mask North
#define MASK_E 0x4  //Mask East
#define MASK_S 0x8  //Mask South
#define MASK_VISITED 0x10 //Mask visited


//++++++++++++++++++++++Find components+++++++++++++++++++++++++++++++++++//

void flood_fill(int rooms[MAX_HEIGHT][MAX_WIDTH][2], int comps[MAX_AREA],
		int true_w, int true_h, int cur_i, int cur_j, int cur_c){

  int i, j;
  //printf("rooms[%d][%d][0] = %d\n", cur_i, cur_j, rooms[cur_i][cur_j][0]);
  int *cur_ptr = &rooms[cur_i][cur_j][0];
  //printf("*cur_ptr = %d\n", *cur_ptr);
  *cur_ptr = *cur_ptr | MASK_VISITED;
  cur_ptr[1] = cur_c;
  comps[cur_c]++;
  
  if ( !(*cur_ptr & MASK_W) ){
    //printf("%d, %d has no western wall.  Value: %d\n", cur_i, cur_j, *cur_ptr);
    assert(cur_j - 1 >= 0);
    if ( !(rooms[cur_i][cur_j - 1][0] & MASK_VISITED) ){
      flood_fill(rooms, comps, true_w, true_h, cur_i, cur_j-1, cur_c);
    }
  }

  if ( !(*cur_ptr & MASK_E) ){
    //printf("%d, %d has no eastern wall.  Value: %d\n", cur_i, cur_j, *cur_ptr);
    assert(cur_j + 1 >= 0);
    if ( !(rooms[cur_i][cur_j + 1][0] & MASK_VISITED) ){
      flood_fill(rooms, comps, true_w, true_h, cur_i, cur_j+1, cur_c);
    }
  }

  if ( !(*cur_ptr & MASK_N) ){
    //printf("%d, %d has no north wall.  Value: %d\n", cur_i, cur_j, *cur_ptr);
    assert(cur_i - 1 >= 0);
    if ( !(rooms[cur_i - 1][cur_j][0] & MASK_VISITED) ){
      flood_fill(rooms, comps, true_w, true_h, cur_i - 1, cur_j, cur_c);
    }
  }
  
  if ( !(*cur_ptr & MASK_S) ){
    //printf("%d, %d has no south wall.  Value: %d\n", cur_i, cur_j, *cur_ptr);
    assert(cur_i + 1 >= 0);
    if ( !(rooms[cur_i + 1][cur_j][0] & MASK_VISITED) ){
      flood_fill(rooms, comps, true_w, true_h, cur_i + 1, cur_j, cur_c);
    }
  }

  return;
  
}


void find_components(int rooms[MAX_HEIGHT][MAX_WIDTH][2], int comps[MAX_AREA],
		     int true_w, int true_h, int *total_comps){

  int i, j;

  for (i = 0; i < true_h; i++){
    for (j = 0; j < true_w; j++){
      if ( !(rooms[i][j][0] & MASK_VISITED) ) {
	flood_fill(rooms, comps, true_w, true_h, i, j, *total_comps);
	(*total_comps)++;
      }

    }

  }

}


//Find adjacent components

void find_adj(int rooms[MAX_HEIGHT][MAX_WIDTH][2], int true_w, int true_h,
	      char adj_comps[MAX_AREA][MAX_AREA]){

  int i, j;
  int cur_component;

  for (i = 0; i < true_h; i++){
    for (j = 0; j < true_w; j++){
      cur_component = rooms[i][j][1];
      
      if (i-1 >= 0) {
	if (cur_component != rooms[i-1][j][1]){
	  adj_comps[cur_component][rooms[i-1][j][1]] = 1;
	}
      }
      
      if (i+1 < true_h) {
	if (cur_component != rooms[i+1][j][1]){
	  adj_comps[cur_component][rooms[i+1][j][1]] = 1;
	}
      }
      
      if (j-1 >= 0) {
	if (cur_component != rooms[i][j-1][1]){
	  adj_comps[cur_component][rooms[i][j-1][1]] = 1;
	}
      }
      
      if (j+1 < true_w) {
	if (cur_component != rooms[i][j+1][1]){
	  adj_comps[cur_component][rooms[i][j+1][1]] = 1;
	}
      }
      
    } 

  }


}

//Find westmost, then southmost wall.  Just finds max room size for now.
int find_wall(int rooms[MAX_HEIGHT][MAX_WIDTH][2], int comps[MAX_AREA],
	      int true_width, int true_height, int *i_loc, int *j_loc,
	      int *direction){

  int i, j;
  int max_i, max_j;
  int max_area = 0;
  int dir;

  for (i = true_width-1; i>=0; i--){
    //check southern walls
    for (j = 0; j < true_height; j++){
      if (rooms[j][i][0] & MASK_S) {
	//Don't remove the southernmost wall!
	if (j+1 >= true_height) {
	  continue;
	}
	if (rooms[j][i][1] == rooms[j+1][i][1]) {
	  continue;
	}/*
	printf("S - checking height: %d, width: %d.  Sum is %d\n", j, i, 
	comps[rooms[j][i][1]] + comps[rooms[j][i+1][1]]);*/
	if (comps[rooms[j][i][1]] + comps[rooms[j+1][i][1]] >= max_area){
	  max_area = comps[rooms[j][i][1]] + comps[rooms[j+1][i][1]];
	  max_i = i; max_j = j+1;
	  dir = MASK_N;
	  //printf("new max %d at i: %d, j: %d, N\n", max_area, max_i, max_j);
	}
      }
    }

    //check western walls
    for (j = 0; j < true_height; j++){
      if (rooms[j][i][0] & MASK_W) {
	//Don't remove the westmost wall!
	if (i-1 < 0) {
	  continue;
	}
	if (rooms[j][i][1] == rooms[j][i-1][1]) {
	  continue;
	}/*
	printf("W - checking height: %d, width: %d.  Sum is %d\n", j, i, 
	comps[rooms[j][i][1]] + comps[rooms[j][i-1][1]]);*/
	if (comps[rooms[j][i][1]] + comps[rooms[j][i-1][1]] >= max_area){
	  max_area = comps[rooms[j][i][1]] + comps[rooms[j][i-1][1]];
	  max_i = i-1; max_j = j;
	  dir = MASK_E;
	  // printf("new max %d at i: %d, j: %d, E\n", max_area, max_i, max_j);
	}
      }
    }
  }

  *i_loc = max_i;
  *j_loc = max_j;
  *direction = dir;
  return max_area;

}


int main(){

  FILE *fin = fopen("castle.in", "r");
  FILE *fout = fopen("castle.out", "w");
  
  int rooms[MAX_HEIGHT][MAX_WIDTH][2] = {0}; //[0] = walls, [1] = component
  int comps[MAX_AREA] = {0};
  char adj_comps[MAX_AREA][MAX_AREA] = {0};

  int true_width, true_height;
  int i, j;
  int total_comps;
  int largest_room = 0;
  int largest_combo;
  int i_loc, j_loc, dir;

  fscanf(fin, "%d %d\n", &true_width, &true_height);
  
  for(i = 0; i<true_height; i++) {
    for (j = 0; j<true_width; j++) {
      fscanf(fin, "%d ", &rooms[i][j][0]);
    }
    fscanf(fin, "\n");
  }

  find_components(rooms, comps, true_width, true_height, &total_comps);

  fprintf(fout, "%d\n", total_comps);
  
  for (i = 0; i < total_comps; i++){
    if (comps[i] > largest_room){
      largest_room = comps[i];
    }
  }
  
  fprintf(fout, "%d\n", largest_room);
  /*
  find_adj(rooms, true_width, true_height, adj_comps);

  printf("\n  ");
  for (i = 0; i < total_comps; i++){
    printf("%d ", i);
  }
  printf("\n");
  for (i = 0; i < 2*(total_comps) + 1; i++){
    printf("-");
  }
  printf("\n");
  for (i = 0; i < total_comps; i++){
    printf("%d|", i);
    for (j = 0; j < total_comps; j++){
      printf("%d ", adj_comps[i][j]);
    }
    printf("\n");
  }
  */

  largest_combo = find_wall(rooms, comps, true_width, true_height,
			    &i_loc, &j_loc, &dir);
  fprintf(fout, "%d\n", largest_combo);
  fprintf(fout, "%d %d", j_loc+1, i_loc+1);
  if (dir == MASK_N){
    fprintf(fout, " N\n");
  }
  else{
    fprintf(fout, " E\n");
  }

  exit(0);

}
