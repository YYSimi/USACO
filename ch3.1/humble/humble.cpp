/*
ID:  ysimidjiy1
LANG: C++
TASK: humble
*/

#include <cstdio>
#include <cstdlib>
#include <cassert>

//#define DEBUG

#ifdef DEBUG
#define dprintf(x) printf x
#else
#define dprintf(x) if(0) {}
#endif

#define MAX_SET_SIZE 100
#define MAX_HUMBLE_NUMBERS 100000

struct PrimeEntry{
    int nPrime;
    int nHumbleNumberIndex;
};

int g_HumbleNumbers[MAX_HUMBLE_NUMBERS];
PrimeEntry g_Primes[MAX_SET_SIZE];
int g_nPrimes;

int CalculateNextHumbleNumber(int nCurrentMaxIndex) {
    uint nCurrentCandidate = -1;

    dprintf(("Calculating %dth humble number\n", nCurrentMaxIndex));

    //Find the smallest new humble number
    for (int i = 0; i < g_nPrimes; i++){
        int nTemp = g_Primes[i].nPrime*g_HumbleNumbers[g_Primes[i].nHumbleNumberIndex];
        dprintf(("\t Temp Candidate is %d\n", nTemp));
        if (nTemp < nCurrentCandidate) {nCurrentCandidate = nTemp;}
    }

    //Update the humble number indices for all of the primes in our list.
    for (int i = 0; i < g_nPrimes; i++){
        int nTemp = g_Primes[i].nPrime*g_HumbleNumbers[g_Primes[i].nHumbleNumberIndex];
        if (nTemp == nCurrentCandidate) {g_Primes[i].nHumbleNumberIndex++;}
    }

    dprintf(("\t Returning %d\n", nCurrentCandidate));
    return nCurrentCandidate;
}

int main(){

    //read in our data
    FILE *fin = fopen("humble.in", "r");
    FILE *fout = fopen("humble.out", "w");

    assert(fin);
    assert(fout);

    int nHumbleNumbers = 0;

    fscanf(fin, "%d %d\n", &g_nPrimes, &nHumbleNumbers);
    dprintf(("nPrimes: %d, nHumbleNumbers: %d\n", g_nPrimes, nHumbleNumbers));
    g_HumbleNumbers[0] = 1; //Hack to make initialization work properly.
    nHumbleNumbers++; //Compensate for our hack.

    for (int i = 0; i < g_nPrimes; i++){
        fscanf(fin, "%d", &g_Primes[i].nPrime);
        g_Primes[i].nHumbleNumberIndex = 0;
    }


    for (int i = 1; i < nHumbleNumbers; i++){
         g_HumbleNumbers[i] = CalculateNextHumbleNumber(i);
    }

    fprintf(fout, "%d\n", g_HumbleNumbers[nHumbleNumbers-1]);

    exit(0);

}
