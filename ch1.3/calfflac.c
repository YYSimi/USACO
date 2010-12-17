/*
ID:  ysimidjiy1
LANG: C
TASK: calfflac
*/


#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define NOQUOTES(x) _NOQUOTES(x)
#define _NOQUOTES(x) #x
#define MAXCHARS 20000

long global = 0;
long global2 = 0;

//Tester:  Tests if the given word is a palindrome.
//Wants a pointer to the start and end of the word
inline int tester(char *a, char *b){
  //fprintf(stderr, "really, no segfaulting!\n");
  global2++;
  if (!(global2 %10000)) printf("entered tester for the %dth time\n\n", global2);

  while (a <= b) {
    global++;
    if (!(global %100000000)) printf("Global is %ld\n", global);
    //printf("Comparing %c to %c\n", *a, *b);
    //printf("Pointer values are %ld and %ld\n", a, b); 
    if (*a == *b) {
      a++;
      b--;
    }
    else {
      //      printf("Done testing. Failure.\n\n");
      return 0;
    }
  }
  //printf("Done testing.  Success.  Length = %d\n\n", i);
  return 1;
}


inline int translateinput(char a) {

  //fprintf(stderr, "You gave me a = %c = %d\n", a, a);
  if (65<=a && a<=90) return (a-65);
  else if (97<=a && a <=122) return (a-97);
  
  return -1;

}

inline int trans2(char a) {
  //fprintf(stderr, "You gave me a = %c = %d\n", a, a);
  if (97<=a && a<=122) {
    //fprintf(stderr, "I'm giving back a = %c = %d\n", a-32, a-32);
    return a - 32;
  }
  else return a;
}

int compar(int *a, int *b) {
  return a-b;
}

int main(){

  FILE *fin = fopen("calfflac.in", "r");
  FILE *fout = fopen("calfflac.out", "w");

  int temp2 = 0;
  int result = 0;
  char a;
  int i=0, j=0;
  int truemaxlen = 0;
  int maxlen = 0;
  char *maxptr = 0;
  char *maxendptr = 0;
  char input[MAXCHARS+5] = {0};
  char fastinput[MAXCHARS+5] = {0};
  int fastlookup[MAXCHARS+5] = {0};
  char finalstr[MAXCHARS+5] = {0};
  int lookup[2][26][MAXCHARS+5] = {0};
  char *head = 0;
  char *tail = 0;
  int fastmaxsize;

  /*
  //Initialize some arrays
  for (i = 0; i<MAXCHARS+5;i++) {
    input[i] = 0;
    for(j = 0; j<26; j++) {
      lookup[j][i] = 0;
    }
    }*/

  fscanf(fin, "%" NOQUOTES(MAXCHARS) "c", input);
  int maxsize = strlen(input);
  fprintf(stderr, "we read %d characters\n", maxsize);
  //initialize our lookup array to begin {1, -1} for all rows 
  for (i = 0; i<26; i++) {
    lookup[0][i][0] = 1;
    lookup[0][i][1] = -1;
  }
  
  // Create an array telling us where letters occur 

  //printf("are we there yet?\n");
  //printf("maxsize is %d\n", maxsize);
  //  printf("i is %d\n", i);
  for (i = 0; i<maxsize; i++) {
    a = translateinput(input[i]);
    //printf("a is %d\n", a);
    if (a == -1) continue;
    fastinput[temp2] = trans2(input[i]);
    fastlookup[temp2] = i;
    //printf("input[i=%d] is %c\n", i, input[i]);
    //printf("fastinput[temp2] is %c, fastlookup[temp2] is %d\n",
    //   fastinput[temp2], fastlookup[temp2]);
    //fprintf(stderr, "input[%d] is %c\n", i, input[i]);
    //fprintf(stderr, "fastinput[%d] is %c = %d\n\n", temp2, fastinput[temp2], fastinput[temp2]);
    lookup[0][a][lookup[0][a][0]+1] = temp2;
    lookup[1][a][lookup[0][a][0]+1] = i;
    //printf("fastinput[temp2] is %c, input[i] is %c\n",
    //  fastinput[temp2], input[i]);
    lookup[0][a][0]++;
    temp2++;

    //printf("lookup[%c][lookup[%c][0]] is %d, i is d\n",
    //   input[i], input[i], lookup[a][lookup[a][0]], i);
    //printf("lookup[%c][0] is %d\n\n", input[i], lookup[a][0]);
    
  }
  

  //printf("Yeah, I guess we are.\n");
  fastmaxsize = strlen(fastinput);
  //fprintf(stderr, "fastmaxsize is %d\n", fastmaxsize);
  //printf("i is %d\n i<fastmaxsize returns %d\n", i, i<fastmaxsize);

  // Loop over the string, but use the above array to make lookups quick.
  for (i = 0; i<fastmaxsize; i++) {
    //fprintf(stderr, "i is %d\n", i);
    //fprintf(stderr, "fastinput[%d] is %d\n", i, fastinput[i]);
    a = fastinput[i]-65;
    //fprintf(stderr, "a is %d\n",a);
    //fprintf(stderr, "lookup[0][a][0] is %d\n", lookup[0][a][0]);
    //fprintf(stderr, "lookup[0][a][l[0][a][0]] is %d\n", lookup[0][a][lookup[0][a][3]]);
    for (j = lookup[0][a][0]; lookup[0][a][j] > i-1; j--){
      //printf("j is %d, i is %d, finput[i] is %c, lookup[finput[i]][j] is %d\n",
	     //     j, i, fastinput[i], lookup[0][fastinput[i]][j]);
      //printf("j is %d\n", j);
      result = tester(&fastinput[i], &fastinput[lookup[0][a][j]]);
      if (result > 0) {
	if ((result = &fastinput[lookup[0][a][j]] - &fastinput[i] +1) > maxlen){
	  maxlen = result;
	  maxptr = &input[fastlookup[i]];
	  maxendptr = &input[lookup[1][a][j]];
	  truemaxlen = maxendptr - maxptr+1;
	  //printf("we tested %c versus %c\n",
	  // fastinput[i], fastinput[lookup[0][a][j]]);
	  //printf("looks like maxptr points to %c\n", *maxptr);
	  //printf("and maxendpointer points to %c\n", *maxendptr);
	  //printf("but maxendpointer's double is %c\n\n", 
	  // input[lookup[0][a][j]]);
	  //printf("maxlen is %d\n", maxlen);
	  //printf("truemaxlen is %d\n", truemaxlen);

	}
	break;
      }
    }
  }
  //printf("what the hell?\n");
  
  if (maxlen == 0 ) {fprintf(fout, "0\n"); exit(0);}

  //printf("INPUT:\n%s\n", input);
  fprintf(fout, "%d\n", maxlen);
  //printf("truemaxlen is %d\n", truemaxlen);
  memcpy(finalstr, maxptr, truemaxlen*sizeof(char));
  finalstr[truemaxlen+1] = '\0';
  fprintf(fout, "%s\n", finalstr);
  
  exit(0);
 
}

