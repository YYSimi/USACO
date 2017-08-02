/*
ID:  ysimidjiy1
LANG: C++
TASK: wormhole
*/

#include <stdio.h>        // STYLE:  You're using C++.  Use iostream instead.
#include <stdlib.h>       // STYLE:  Do you need this?  No, no you don't.
                          // STYLE:  <cstdio, cstlib>.

typedef struct wormhole { //STYLE:  Should be capitalized, since type name.
    unsigned long x;
    unsigned long y;
} wormhole;

wormhole wormholes[12];
unsigned int nWormholes = 0; //STYLE:  Should have g_ prefix, since global.
unsigned int nBadPaths = 0; // STYLE: ibid.
#define NO_PARTNER -1
#define MAX_GRID 1000000001

int wormhole_partner[] = {NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER}; //STYLE:  Pluralize, g_

//  Next wormhole, if walking left to right.
int wormhole_next[] = {NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER,
                            NO_PARTNER, NO_PARTNER, NO_PARTNER};
                            // STYLE:  Pluralize, g_

// Create wormhole pairings using DFS.
// Then check for cow loops by starting bessie as entering each wormhole 
// and checking if she ever takes that wormhole again.
//   No?  Try another starting wormhole.  When you run out, move to next wormhole setup.
//   Yes? Increment bad wormhole setup counter and BREAK current wormhole setup check

int FindNextWormhole(unsigned int whCurrent) {
    int whClosestSoFar = NO_PARTNER;        //STYLE:  Not a wormhole.  Don't start with wh.
    long whClosestLocation = MAX_GRID + 1;  //STYLE:  Ibid.

    for (int i = 0; i < nWormholes; ++i) {
        if (wormholes[i].y == wormholes[whCurrent].y &&
            wormholes[i].x > wormholes[whCurrent].x &&
            wormholes[i].x < whClosestLocation)
        {
            whClosestLocation = wormholes[i].x;
            whClosestSoFar = i;
        }
    }
    
    return whClosestSoFar;
}

void FillNextWormholes() {
    for (int i = 0; i < nWormholes; ++i) {
        wormhole_next[i] = FindNextWormhole(i);
    }
    
    printf("next wormholes:\n");
    for (int i = 0; i < nWormholes; ++i) {
        printf("%d: %d\n", i, wormhole_next[i]);
    }

}

void pathCheck() {
//    printf("pathcheck\n");
    
//    printf("wormhole partners:\n");
//    for(int i = 0; i < nWormholes; ++i) {
//        printf("%d: %d\n", i, wormhole_partner[i]);
//    }
    
    for (int whStart = 0; whStart < nWormholes; ++whStart){
        int whCurrent = whStart;
        int nWhVisited = 0;
        do {
            if (wormhole_next[whCurrent] == NO_PARTNER) {
                whCurrent = NO_PARTNER;
                break;
            }
            else {
                whCurrent = wormhole_partner[wormhole_next[whCurrent]];
                ++nWhVisited;
            }
        } while (whCurrent != whStart &&
                 whCurrent != NO_PARTNER &&
                 nWhVisited <= nWormholes);
                 
        if (whCurrent != NO_PARTNER) {
            ++nBadPaths;
            break;
        }
    }
}

void dfs(int nCurrentWormhole) {
//    printf("dfs on wormhole %d\n", nCurrentWormhole);
    //Are we at the last wormhole?
    if (nCurrentWormhole == nWormholes) {
        pathCheck();
        return;
    }
    
    // Is our current wormhole already partnered?
    if (wormhole_partner[nCurrentWormhole] != NO_PARTNER) {
        dfs(nCurrentWormhole+1);
        return;
    }
    
    // Perform DFS.
    for (int i = nCurrentWormhole + 1; i < nWormholes; ++i) {
        if (wormhole_partner[i] == NO_PARTNER) {
            wormhole_partner[i] = nCurrentWormhole;
            wormhole_partner[nCurrentWormhole] = i;
            dfs(nCurrentWormhole + 1);
            wormhole_partner[nCurrentWormhole] = NO_PARTNER;
            wormhole_partner[i] = NO_PARTNER;
        }
    }
}

int main(){
    
    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");

    fscanf(fin, "%u\n", &nWormholes);
    for (int i = 0; i<nWormholes; i++) {
        fscanf(fin, "%lu %lu", &(wormholes[i].x), &(wormholes[i].y));
    }

    FillNextWormholes();
    dfs(0);
    
    printf("nWormholes: %u\n", nWormholes);
    printf("nBadPaths: %u\n", nBadPaths);
    
    fprintf(fout, "%d\n", nBadPaths);

    exit(0);

}











