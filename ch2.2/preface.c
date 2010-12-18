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
    int whole[5];  // I, X, C, M, empty  -- Takes values 0-4, OVERFLOW
    int half[4];   // V, L, D, empty -- Takes values 0-1 
} num_t;

void inc_whole(num_t *num, int loc);
void inc_half(num_t *num, int loc);

/* Given a num and a loc specificying if we are incrementing I, X, C, M,
 * increments the given placevalue.
 */
void inc_whole(num_t *num, int loc){
    num->whole[loc]++;
    int i = num->whole[loc]; //Note that this does not get updated!
    //Did we create 4?  If so, increment the half step. 
    if (i == 4){
        inc_half(num, loc);
    }
    //Did we create 5?  (IV --> V)? That's just bullshit.  Revert to 0.
    if (i == 5){
        num->whole[loc] = 0;
        //Did we have an overflow state like XXXIX?  If so, goto XL
        if (num->whole[loc+1] == OVERFLOW){
            num->whole[loc+1] = 4;
            inc_half(num, loc+1);
        }
    }
    return;
}

void inc_half(num_t *num, int loc){
    num->half[loc]++;
    int i = num->half[loc];
    //Did we create 2?  If so, increment the next whole setp
    if (i == 2){
        num->half[loc] = 0;
        //are we creating an overflow case?
        if (num->whole[loc+1] == 3){
            num->whole[loc+1] = OVERFLOW;
        }
        else {
            inc_whole(num, loc+1);
        }
    }
}

void inc_all(num_t *num_inc, num_t *num_total){
    int i = 0;
    
    inc_whole(num_inc, 0);
    
    for (i = 0; i < 4; i++){
        if (num_inc->whole[i] == OVERFLOW){
            num_total->whole[i] += 4;
        }
        else if (num_inc->whole[i] == 4){
            num_total->whole[i] += 1;
        }
        else{
            num_total->whole[i] += num_inc->whole[i];
        }
    }
    for (i = 0; i < 3; i++){
        num_total->half[i] += num_inc->half[i];
    }
    
}

void fprint_num(FILE *stream, num_t num){

    if (num.whole[0] != 0) {
        fprintf(stream, "I %d\n", num.whole[0]);
    }
    if (num.half[0] != 0) {
        fprintf(stream, "V %d\n", num.half[0]);
    }
    if (num.whole[1] != 0) {
        fprintf(stream, "X %d\n", num.whole[1]);
    }
    if (num.half[1] != 0) {
        fprintf(stream, "L %d\n", num.half[1]);
    }
    if (num.whole[2] != 0) {
        fprintf(stream, "C %d\n", num.whole[2]);
    }
    if (num.half[2] != 0) {
        fprintf(stream, "D %d\n", num.half[2]);
    }
    if (num.whole[3] != 0) {
        fprintf(stream, "M %d\n", num.whole[3]);
    }

}

int main(){

    FILE *fin = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");

    int inVal;
    int i;
    fscanf(fin, "%d\n", &inVal);
    printf("%d\n\n", inVal);

    num_t numInc, numTotal;
    for (i = 0; i < 5; i++){
        numInc.whole[i] = 0;
        numTotal.whole[i] = 0;
    }
    for (i = 0; i < 4; i++){
        numInc.half[i] = 0;
        numTotal.half[i] = 0;
    }


    printf("\nInc starts:\n");
    fprint_num(stdout, numInc);
    printf("\nTotal starts:\n");
    fprint_num(stdout, numTotal);


    for (i = 0; i < inVal; i++){
        inc_all(&numInc, &numTotal); 
    }
    
    printf("\nInc ends:\n");
    fprint_num(stdout, numInc);
    printf("\nTotal ends:\n");
    fprint_num(stdout, numTotal);

    fprint_num(fout, numTotal);

}
