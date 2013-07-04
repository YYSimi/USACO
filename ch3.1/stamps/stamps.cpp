/*
ID:  ysimidjiy1
LANG: C++
TASK: stamps
*/

#define TASKNAME stamps

#include <cstdio>
#include <cstdlib>
#include <cassert>

#define MAX_STAMPS_PER_ENVELOPE 200
#define MAX_STAMP_VALUES 50
#define MAX_CONTIGUOUS_STAMPS 3000000 //Damn well better not exceed 3M values...

//#define DEBUG

#ifdef DEBUG
#define dprintf(x) printf x
#else
#define dprintf(x) if(0) {};
#endif

int g_nStampsPerEnvelope = 0;
int g_nStampValues = 0;

int g_StampValues[MAX_STAMP_VALUES] = {0}; 
int g_NumberOfStampsNeeded[MAX_CONTIGUOUS_STAMPS]; //Initialize everything except 0 to -1.

int CalculateBest(int nValue){
    unsigned int nBest = -1;
    unsigned int nCurrentCandidate = 0;
    for (int i = 0; i < g_nStampValues; i++){
        if (nValue - g_StampValues[i] < 0){ 
            dprintf(("nValue-g_StampValues[%d] = %d - %d = %d\n",
                     i, nValue, g_StampValues[i], nValue-g_StampValues[i]));
            continue; 
        }
        nCurrentCandidate = g_NumberOfStampsNeeded[nValue - g_StampValues[i]];
        dprintf(("nCurrentCandidate is %d\n", nCurrentCandidate));
        if (nCurrentCandidate != -1) {
            nCurrentCandidate++; //We're adding one more stamp...
            if (nCurrentCandidate < nBest && nCurrentCandidate <= g_nStampsPerEnvelope ) {
                nBest = nCurrentCandidate;
                dprintf(("Current nBest is %d\n", nBest));
            }
        }
    }

    return nBest;
}

int main(){

    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");
    
    fscanf(fin, "%d %d\n", &g_nStampsPerEnvelope, &g_nStampValues);

    for (int i = 0; i < g_nStampValues; i++) {
        fscanf(fin, "%d", &g_StampValues[i]);
        
    }
   
    g_NumberOfStampsNeeded[0] = 0;
    //Initialize g_NumberOfStampsNeeded array
    for (int i = 1; i < MAX_CONTIGUOUS_STAMPS; i++) {
        g_NumberOfStampsNeeded[i] = -1;
    }

    int nNextToCalculate = 1;
    int nBest = 0;
    while ((nBest = CalculateBest(nNextToCalculate)) != -1) {
        g_NumberOfStampsNeeded[nNextToCalculate] = nBest;
        nNextToCalculate++;
    }

    fprintf(fout, "%d\n", nNextToCalculate-1);
    exit(0);

}
