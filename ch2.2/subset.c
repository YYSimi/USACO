/*
ID:  ysimidjiy1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/* Returns the target value for each of our two subsets of integers
 * starting at "start" and ending at "end."  Returns -1 for invalid targets.
 */
int calculateTarget(int start, int end){

    int sum = (end - start + 1)*(start+end)/2;

    if ( (sum % 2) == 0 ){
        return sum/2;
    }
    else{
        return -1;
    }

}

void DFS(int start, int end, int curVal, int tarVal, int *total){

    int i;
    int newVal;

    for (i = start; i<=end; i++){
        newVal = curVal + i;
        if (newVal == tarVal){
            //printf("%d\n", i);
            (*total)++;
            return;
        } 
        else if (newVal < tarVal) {  
            DFS(i+1, end, newVal, tarVal, total);
        }
        else {
            return;
        }
    }

}

int main(){

    int inVal, tarVal, total = 0;

    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");

    fscanf(fin, "%d\n", &inVal);

    tarVal = calculateTarget(1, inVal);
    printf("target val: %d\n", tarVal);
    
    DFS(2, inVal, 0, tarVal, &total);

    printf("total: %d\n", total);
    fprintf(fout, "%d\n", total);

    exit(0);

}
