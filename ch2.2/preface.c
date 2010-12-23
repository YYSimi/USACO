/*
ID:  ysimidjiy1
LANG: C
TASK: preface
*/

#define OVERFLOW 10 //Rare case where we have 4 of a symbol, e.g. XXXIX.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct num {
    int whole[6];  // I, X, C, M, empty  -- Takes values 0-3
    int half[5];   // V, L, D, empty -- Takes values 0-1 
    int c_whole[5]; //IX, XC, CM, empty -- takes values 0-1
    int c_half[5]; // IV, XL, CD, empty -- takes values 0-1 
} num_t;

void inc_whole(num_t *num, int loc);
void inc_half(num_t *num, int loc);

/* Given a num and a loc specificying if we are incrementing I, X, C, M,
 * increments the given placevalue.
 */
void inc_whole(num_t *num, int loc){
    //Do we have a compound mark that uses us as a prefix?  If so, handle it.
    if (num->c_whole[loc] == 1){
        num->c_whole[loc] = 0;
        inc_whole(num, loc+1);
    }
    else if (num->c_half[loc] == 1){
        num->c_half[loc] = 0;
        inc_half(num, loc);
    }
    //Not a prefix?  Proceed normally.
    else {
        num->whole[loc]++;
        /* Did we create 4?  If so, increment the half step, reset to 0, and 
         * flag a prefix */
        if (num->whole[loc] == 4){
            num->whole[loc] = 0;
            if (num->half[loc] == 0) {
                num->c_half[loc] = 1;
            }
            else {
                num->half[loc] = 0;
                num->c_whole[loc] = 1;
            }
        }
    }
    return;
}

void inc_half(num_t *num, int loc){
    num->half[loc]++;
    //Did we create 2?  If so, increment the next whole setp
    if (num->half[loc] == 2){
        num->half[loc] = 0;
        inc_whole(num, loc+1);
    }
    return;
}

/* Performs an increment on num_inc while tracking the total number of
 * symbols in num_total
 */ 
void inc_all(num_t *num_inc, num_t *num_total){
    int i = 0;
    
    inc_whole(num_inc, 0);
    
    for (i = 0; i < 4; i++){
        
        num_total->whole[i] += num_inc->whole[i];
        num_total->whole[i] += num_inc->c_whole[i]; //Don't forget compounds!
        num_total->whole[i] += num_inc->c_half[i]; //or these compounds
        num_total->half[i] += num_inc->c_half[i]; //or these...
        if (i > 0){
            num_total->whole[i] += num_inc->c_whole[i-1]; //more compounds!
        }
    }
    for (i = 0; i < 3; i++){
        num_total->half[i] += num_inc->half[i];
    }
    
    return;
}

void fprint_num(FILE *stream, num_t num){

    if (num.whole[0] + num.c_whole[0] + num.c_half[0] != 0) {
        fprintf(stream, "I %d\n", num.whole[0]+num.c_whole[0]+num.c_half[0]);
    }
    //printf("works after whole[0]\n");
    if (num.half[0] + num.c_half[0] != 0) {
        fprintf(stream, "V %d\n", num.half[0] + num.c_half[0]);
    }
    if (num.whole[1]+num.c_whole[0]+num.c_whole[1]+num.c_half[1] != 0) {
        fprintf(stream, "X %d\n", num.whole[1]+num.c_whole[0]+num.c_whole[1]+
                num.c_half[1]);
    }
    //printf("works after whole[1]\n");
    if (num.half[1]+num.c_half[1] != 0) {
        fprintf(stream, "L %d\n", num.half[1]+num.c_half[1]);
    }
    if (num.whole[2]+num.c_whole[1]+num.c_whole[2]+num.c_half[2] != 0) {
        fprintf(stream, "C %d\n", num.whole[2]+num.c_whole[1]+num.c_whole[2]+
                num.c_half[2]);
    }
    //printf("works after whole[2]\n");
    if (num.half[2]+num.c_half[2] != 0) {
        fprintf(stream, "D %d\n", num.half[2]+num.c_half[2]);
    }
    //printf("Works after half[2]\n");
    if (num.whole[3]+num.c_whole[2]+num.c_whole[3]+num.c_half[3] != 0) {
        fprintf(stream, "M %d\n",
                num.whole[3]+num.c_whole[2]+num.c_whole[3]+num.c_half[3]);
    }
    //printf("works after whole[3]\n");    
     
    return;
}

int main(){

    FILE *fin = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");

    int inVal;
    int i;
    fscanf(fin, "%d\n", &inVal);
    //printf("%d\n\n", inVal);

    num_t numInc, numTotal;
    for (i = 0; i < 5; i++){
        numInc.whole[i] = 0;
        numTotal.whole[i] = 0;
    }
    for (i = 0; i < 4; i++){
        numInc.half[i] = 0;
        numInc.c_whole[i] = 0;
        numInc.c_half[i] = 0;
        numTotal.half[i] = 0;
        numTotal.c_whole[i] = 0;
        numTotal.c_half[i] = 0;
    }

    /*
    printf("\nInc starts:\n");
    fprint_num(stdout, numInc);
    printf("\nTotal starts:\n");
    fprint_num(stdout, numTotal);
    */

    for (i = 0; i < inVal; i++){
        inc_all(&numInc, &numTotal); 
    }
    
    
    printf("\nInc ends:\n");
    fprint_num(stdout, numInc);
    printf("\nTotal ends:\n");
    fprint_num(stdout, numTotal);
    fprint_num(fout, numTotal);
    
    
    
    
    exit(0);

}
