/*
ID:  ysimidjiy1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXINPUT 40   //our actual max input is 39, but just to be safe...
#define MAXTARVAL 400 //390 suffices, actually, but just to be safe...

int sumCounts[MAXINPUT][MAXTARVAL];

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

/* start:  Start value for the DFS.
 * end:  end value for the DFS.
 * parent:  the integer that was added to the set at the parent node.
 * depth:  The current depth of the node
 */
void DFS(int start, int end, int curVal, int tarVal, int *total, int parent,
         int depth){

    assert(start <= end);

    int i;
    int newVal;

    if (start = parent+1){
        for (i = start; i<=end; i++){
            newVal = curVal + i;
            if (newVal == tarVal){
                (*total)++;
                return;
            } 
            else if (newVal < tarVal) {  
                sumCounts[depth][newVal]++;
                DFS(i+1, end, newVal, tarVal, total);
            }
            else {
                return;
            }
        }
    }
    else {
        
    }

}

int main(){

    int inVal, tarVal, total = 0;

    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");

    fscanf(fin, "%d\n", &inVal);

    tarVal = calculateTarget(1, inVal);
    printf("target val: %d\n", tarVal);
    
    DFS(2, inVal, 0, tarVal, &total, 1, 0);

    printf("total: %d\n", total);
    fprintf(fout, "%d\n", total);

    exit(0);

}
