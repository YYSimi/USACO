/*
ID:  ysimidjiy1
LANG: C
TASK: combo
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LockLocation {
    int x1;
    int x2;
    int x3;
} LockLocation;

int CalculateDimensionalOverlap(int x, int y, int gridSize) {
    int preDistance = 0;
//    printf("%d %d %d\n", x, y, gridSize);
    preDistance = ((x - y + gridSize) % gridSize);
//    printf("%d\n", preDistance);
    if (gridSize - preDistance <= 4) {
        preDistance = gridSize - preDistance;
//        printf("%d\n", preDistance);
    }
    
    preDistance = 5 - preDistance;
//    printf("%d\n", preDistance);
    if (preDistance < 0) {preDistance = 0;}
//    printf("%d\n", preDistance);
    return preDistance;
}

int main(){
    unsigned int nValidCombos = 0;
    unsigned int nGridSize = 0;
    LockLocation lockLoc1, lockLoc2;

    //Read data
    FILE *fin = fopen("combo.in", "r");
    FILE *fout = fopen("combo.out", "w");

    fscanf(fin, "%u\n", &nGridSize);
    fscanf(fin, "%d %d %d", &(lockLoc1.x1), &(lockLoc1.x2), &(lockLoc1.x3));
    fscanf(fin, "%d %d %d", &(lockLoc2.x1), &(lockLoc2.x2), &(lockLoc2.x3));

    // Calculate valid combos
    if (nGridSize <= 5) {
        nValidCombos = nGridSize * nGridSize * nGridSize;
    }
    else {
        nValidCombos = 250 - 
            CalculateDimensionalOverlap(lockLoc1.x1, lockLoc2.x1, nGridSize) *
            CalculateDimensionalOverlap(lockLoc1.x2, lockLoc2.x2, nGridSize) *
            CalculateDimensionalOverlap(lockLoc1.x3, lockLoc2.x3, nGridSize);
    }
    
    printf("%d\n", nValidCombos);
    fprintf(fout, "%d\n", nValidCombos);

    exit(0);

}











