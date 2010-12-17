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
#define MAX(a, b) ((a)>(b)?(a):(b))


//Tester:  Tests if the given word is a palindrome.
//Length is the number of chars in [start of word, middle of word].
inline int tester(char *left, char *right, int length, int *speedup){
  //fprintf(stderr, "really, no segfaulting!\n");
  int cursize = 0;
  *speedup = 0;

  if(left == right) cursize = -1;

  while (length > 0) {
    //printf("comparing %c at %ld to %c at %ld\n", *left, left, *right, right);
    if (*left != *right) break;
    cursize+=2;
    left--;
    right++;   
    length--;
    (*speedup)++;
  }
  
  return cursize;
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
  int result1 = 0, result2 = 0;
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
  char *head = 0;
  char *tail = 0;
  int fastmaxsize;
  int speedup1, speedup2;

  fscanf(fin, "%" NOQUOTES(MAXCHARS) "c", input);
  int maxsize = strlen(input);
  fprintf(stderr, "we read %d characters\n", maxsize);
  
  // Create an array telling us where letters occur 

  for (i = 0; i<maxsize; i++) {
    a = translateinput(input[i]);
    //printf("a is %d\n", a);
    if (a == -1) continue;
    fastinput[temp2] = trans2(input[i]);
    fastlookup[temp2] = i;
    temp2++;    
  }
  
  fastmaxsize = strlen(fastinput);

  // Loop over the string, but use the above array to make lookups quick.
  for (i = 0; i<fastmaxsize; i++) {
    //printf("reading i=%d at %c\n", i, fastinput[i]);
    
    result1 = tester(&fastinput[i], &fastinput[i], i+1, &speedup1);
    result2 = tester(&fastinput[i], &fastinput[i+1], i+1, &speedup2);
    
    if (result1 > maxlen){
      maxlen = result1;
      //printf("Maxlen is now %d\n", result1);
      //printf("Speedup is %d\n", speedup1);
      maxptr = &input[fastlookup[i-speedup1+1]];
      maxendptr = &input[fastlookup[i+speedup1-1]];
      truemaxlen = maxendptr - maxptr+1;
    }

  if (result2 > maxlen){
      maxlen = result2;
      //printf("Maxlen is now %d\n", result2);
      //printf("Speedup is %d\n", speedup2);
      maxptr = &input[fastlookup[i-speedup2+1]];
      maxendptr = &input[fastlookup[i+speedup2]];
      truemaxlen = maxendptr - maxptr+1;
    }
  }
  
  if (maxlen == 0 ) {fprintf(fout, "0\n"); exit(0);}

  //printf("INPUT:\n%s\n", input);
  fprintf(fout, "%d\n", maxlen);
  //printf("truemaxlen is %d\n", truemaxlen);
  memcpy(finalstr, maxptr, truemaxlen*sizeof(char));
  finalstr[truemaxlen+1] = '\0';
  fprintf(fout, "%s\n", finalstr);
  
  exit(0);
 
}

