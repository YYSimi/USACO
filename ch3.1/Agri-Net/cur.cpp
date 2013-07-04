/*
ID:  ysimidjiy1
LANG: C++
TASK: agrinet
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <queue>
#include <vector>

#define DEBUG2
//Debug levels...  Level 2 shows all debug text.
#ifdef DEBUG2
#define DEBUG
#endif

//Use dprintf2 for old debug code you probably won't need
#ifdef DEBUG2
#define dprintf2(x) printf x
#else
#define dprintf2(x) do {} while (0)
#endif

struct QueueEntry {
    int nNewFarm;
    int nWeight;
};

#define MAX_FARMS 100
int g_ConnectivityMatrix[MAX_FARMS][MAX_FARMS] = {0};
int g_fIsInComponent[MAX_FARMS] = {0};
int g_nFarmsConnected = 0;
int g_nFarmsTotal = 0;
int g_nCurrentLength = 0;

class CompareEntries {
 public:
    bool operator()(QueueEntry &a, QueueEntry &b){
        return a.nWeight > b.nWeight;
    }
};

std::priority_queue<QueueEntry, std::vector<QueueEntry>, CompareEntries> g_PrQuToSearch;

void ReadData(){
    FILE *fIn = fopen("agrinet.in", "r");
    
    assert(fIn != NULL);
    fscanf(fIn, "%d\n", &g_nFarmsTotal); //Read in the number of farms
    
    //Fill in the array one farm at a time.
    for (int i = 0; i < g_nFarmsTotal; i++){
        for (int j = 0; j < g_nFarmsTotal; j++) {
            fscanf(fIn, "%d", &g_ConnectivityMatrix[i][j]);
            dprintf2(("%d %d: %d \n", i, j, g_ConnectivityMatrix[i][j]));            
        }
    }

    return;
}

//Given a farm, add adjacent farms into our heap.
void ProcessFarm(int nFarm){

    dprintf2(("Processing farm %d\n", nFarm));

    static QueueEntry QuEnNextLength;

    //Add entries from our connectivity matrix
    for (int i = 0; i < g_nFarmsTotal; i++){
        if (i == nFarm ) {continue;}
        QuEnNextLength.nNewFarm = i;
        QuEnNextLength.nWeight = g_ConnectivityMatrix[nFarm][i];
        g_PrQuToSearch.push(QuEnNextLength);
    }

    return;
}

//Check our heap for the next farm that should be connected
int ProcessHeap(){
    static int nCalls = 0;
    nCalls++;
    dprintf2(("nCalls: %d\n", nCalls));
    static QueueEntry QuEnNextFarm;
    //Get the top element of the heap
    do {
        assert(!g_PrQuToSearch.empty());
        QuEnNextFarm=g_PrQuToSearch.top();
        g_PrQuToSearch.pop();
    }
    //If the new farm is already in our component, try try again.
    while (g_fIsInComponent[QuEnNextFarm.nNewFarm]);

    //Otherwise, add the length of the component to g_nCurrentLength
    g_nCurrentLength += QuEnNextFarm.nWeight;

    //Update g_nFarmsConnected and g_fIsInComponent;
    g_nFarmsConnected++;
    g_fIsInComponent[QuEnNextFarm.nNewFarm] = 1;

    //Return the next farm to be processed.
    return QuEnNextFarm.nNewFarm;
}

int main(){

    ReadData();

    //Prime our data by "connecting" farm 1 to itself.
    int nNextFarm = 0;
    g_nFarmsConnected++;
    g_fIsInComponent[nNextFarm] = 1;
    ProcessFarm(nNextFarm);

    //While there are still farms to process...
    while (g_nFarmsConnected < g_nFarmsTotal) {
        nNextFarm = ProcessHeap();
        dprintf2(("next farm to process: %d\n", nNextFarm));
        ProcessFarm(nNextFarm);
    }

    //Print our output
    dprintf2(("%d\n", g_nCurrentLength));

    FILE *fOut = fopen("agrinet.out", "w");
    assert(fOut != NULL);
    fprintf(fOut, "%d\n", g_nCurrentLength);

    return 0;

}
