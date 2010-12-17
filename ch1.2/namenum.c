/*
ID:  ysimidjiy1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXLENGTH 12

/*  Ok, here's the game plan.  Scan the list until you hit first of first
 *  number.  Then scan until first of second number, etc.  Once you finish,
 *  scan second of last number, then third of last number, etc.  Write a 
 *  scan() function to do the scanning.
 *
 *  Ok, updated game plan:  Keep a giant array of potential names.  Scan for 
 *  the ones we want in order.  Then we are golden.
 *
 */


void generate_names(char giantarray[(int)pow(3,MAXLENGTH)][MAXLENGTH+1],
		    char lu[10][3], char * input, int length);


//Stupid way of doing exponentiation, but hey, 3^12 is the worst we're doing.
int idiot_exp(int a, int b) {

  int i = 0;
  int j = 1;
  while (i < b) {

    j = j*a;
    i++;
  }
  return j;
}

int main(){

  //index 2 is the name, 1 is ind.
  char giantarray[(int)pow(3,MAXLENGTH)][MAXLENGTH+1];
  
  char lookup[10][3] = {{}, {},
			{'A', 'B', 'C'},
			{'D', 'E', 'F'},
			{'G', 'H', 'I'},
			{'J', 'K', 'L'},
			{'M', 'N', 'O'},
			{'P', 'R', 'S'},
			{'T', 'U', 'V'},
			{'W', 'X', 'Y'},
  };
  char input[13];
  int i=0, j=0; //Counters
  char scanning[13];
  int flag = 0;

  FILE *fin = fopen("namenum.in", "r");
  FILE *fout = fopen("namenum.out", "w");
  FILE *names = fopen("dict.txt", "r");
  fscanf(fin, "%s\n", input);
  int inlen = strlen(input);
  generate_names(giantarray, lookup, input, inlen);

  //Ok, we've got our giantarray filled out, now we need to start reading.
  scanning[strlen(input)] = '\0'; //Hey, now scanning is actually a string!
  fscanf(names, "%s\n", scanning);

  //Hey, there's a lot of names to read!
  while (i < idiot_exp(3, inlen) ) {

    while(strcmp(giantarray[i], scanning) >0) {
      // printf("comparing garray[%d] (%s) to scanning (%s)\n", i,
      //     giantarray[i], scanning);
      
      fscanf(names, "%s\n", scanning);
    }
    


    // We've found a match.  May we burn her?
    if (strcmp(giantarray[i], scanning) == 0) {
      fprintf(fout, "%s\n", scanning);
      printf("Match at %s!\n", scanning);
      flag = 1;
    }
    //    printf("incrementing i from %d as garray was %s\n", i, giantarray[i]);
    i++;

  }

  if (flag == 0) {
    fprintf(fout, "%s\n", "NONE");
  }

  exit(0);

}



/* Generate Names:  Given an input, generates a list of possible names
 * that has been ordered so that the rest of the algorithm will resolve
 * nicely.
 */

void generate_names(char giantarray[(int)pow(3,MAXLENGTH)][MAXLENGTH+1],
		    char lu[10][3], char * input, int length)
{

  int progress[length];
  int i=0, j=0, k=0, bigcount=0; //Counters
  /* for each letter, loop 3 times.  1,1,1,1...,1,2 ... 1,1,1,1...1,3 etc.
   * and store this in giantarray[][].  check progress[length].  If <3, then
   * increment and continue.  if = 3, increment prior and continue.  continue
   * until progress [0] is 3. */

  // "zero out" our progress array.
  for (i=0; i<length; i++) {
    progress[i] = 0;
  }

  //Hey, we've got a lot of names to generate, so let's loop forever.
  while(1) { 
  
    //Write to giantarray.
    for (i=0; i<length; i++){
      //Update giantarray letter by letter
      giantarray[bigcount][i] = lu[*(input+i)-48][progress[i]];
      //printf("input is %d\n", *(input+i)-48);
      //printf("%c inserted to giantarray[%d][%d]\n", lu[*(input+i)-48][progress[i]], bigcount, i);
    }
    i = length-1;

    //Increment bigcount.  We're on a new word now.
    bigcount++;
    //printf("bigcount: %d\n", bigcount);

    //Increment progress.  We expect i == length-1 right now.
    while(i>=0) {
      //printf("progress[%d] is: %d\n", i, progress[i]);

      //Are we still on this digit?  If so, next letter and continue.
      if (progress[i] != 2) {
	progress[i]++;
	break;
      }
      //Are we done with this digit?  If so, previous digit and cont.
      else {
	progress[i] = 0;
	i--;
      }
    }

    //If this happens, progress = {2, 2, 2, ..., 2}, so we are done.
    if (i < 0) break;

  }

  //Add '\0' to make our things nice and stringy.
  for(k=0; k<bigcount;k++) {
    giantarray[k][length] = '\0';
  }

  /*  printf("First name:  %s\n Second name:  %s\n Third name: %s\n Fourth name: %s\n Fifth name: %s\n Sixth name: %s\n", giantarray[0], 
	 giantarray[1], giantarray[2], giantarray[3], giantarray[4], giantarray[5]);
      printf("Some values:\n 0,0: %c\n 0,1: %c\n 0,2: %c\n 0,3: %c\n 1,0: %c\n 1,1: %c\n 1,2: %c\n 1,3: %c\n 2,0: %c\n 3,0: %c\n",
	 giantarray[0][0], giantarray[0][1],
	 giantarray[0][2], giantarray[0][3], giantarray[1][0],
	 giantarray[1][1], giantarray[1][2], giantarray[1][3],
	 giantarray[2][0], giantarray[3][0]);
  */
}





/*


  //Loop per letter... why?
  for (i=0; i<=length, i++) {

    if (progress[j] == 3) {
      
      // If we've finished a cycle, return and increment
      if (j == length) {
	progress[j] = 1;
	k = length;
	
	while (progress[k] == 3){
	  
	  progress[k] = 1;
	  k--;
	  if (k == 0) break;
	  
	}
	j = k;	
	progress[j]++;
	if (progress[j] == 4) break; //If p[j] = 4, then j=0, p[j]>3, so done. 
      }
      
    }
   
  }
  
*/
