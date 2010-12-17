/*
ID:  ysimidjiy1
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <string.h>

int main(){

  int np;
  char cur_name[16];
  int i, j, k, m; //loop indices

  FILE *input = fopen("gift1.in", "r");
  FILE *output = fopen("gift1.out", "w");
  
  //get the correct number of people
  fscanf(input, "%d\n", &np);

  //Declare appropriate data structures
  char people[np][16];
  int costs[np];
  
  //zero out our array
  for(i=0; i<np; i++){
    costs[i] = 0;
     // printf("initial costs[%d] is %d", i, costs[i]);
  }

  //store their names
  for(i = 0; i<np; i++){
    fgets(people[i], 15, input);
    people[i][strlen(people[i]) -1] = '\0'; //kill the terminal newline
    printf("person %d entered, name %s\n", i, people[i]);
  }
  
  //Calculate the costs
  for(i = 0; i<np; i++) {
    fgets(cur_name, 15, input);
    cur_name[strlen(cur_name) -1] = '\0'; //kill the terminal newline
    //Find the right person in our people array.
    for(j = 0; j<np; j++){
      if (!strcmp(cur_name, people[j])){
	int cash; 
	int friends;
	
	//remove the correct amount from the current person's coffer.
	fscanf(input, "%d %d\n", &cash, &friends);
	if (friends != 0) cash = cash - (cash%friends); 
	costs[j] = costs[j] - cash;
	if (friends != 0) cash = cash/friends;
	
	printf("It's time for %s to pay %d to his %d friends!\n",
	       people[j], cash, friends);
	
	//add the correct amount to his friends' coffers
	for (k = 0; k<friends; k++){
	  fgets(cur_name, 15, input);
	  cur_name[strlen(cur_name) -1] = '\0';
	  printf("pay out to %s\n", cur_name);
	  
	  for (m = 0; m<np; m++) {
	    if (!strcmp(cur_name, people[m])) {
	      printf("%s makes %d from %s\n", people[m], cash, people[j]);
	      costs[m] = costs[m] + cash;
	      break;
	    }
	  }
	  
	}
      break;
      }
    } 
    
  }

  //print our results
  //fprintf(output, "%s\n", people[3]); 
  for (i = 0; i<np; i++){
    fprintf(output, "%s %d\n", people[i], costs[i]);
  }

  exit(0);
  
}
