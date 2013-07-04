/*
ID:  ysimidjiy1
LANG: C++
TASK: inflate
*/

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <utility>

//#define DEBUG

#ifdef DEBUG
#define dprintf(x) printf x
#else
#define dprintf(x) if (0) {}
#endif

#define UNINITIALIZED -1
#define MAX_LENGTH 10000
#define MAX_PROBLEM_CATEGORIES 10000

int g_HighScores[MAX_LENGTH] = {0};

//Points, then minutes
std::pair<int, int> g_ProblemCategories[MAX_PROBLEM_CATEGORIES];

int CalculatePoints(int nTime) {
    
    int nMaxPoints = 0;
    int nPoints = 0;
    //For each problem categorty...
    for (int i = 0; i < MAX_PROBLEM_CATEGORIES; i++){
        nPoints=0;
        //Check if the category is valid
        if (g_ProblemCategories[i].first == UNINITIALIZED) {break;}
        //Check if we have enough time remaining for the problem
        if (g_ProblemCategories[i].second > nTime) {continue;}
        //Calculate the maximum number of points attainable if we use this problem last.
        nPoints = g_ProblemCategories[i].first + g_HighScores[nTime-g_ProblemCategories[i].second];
        //Update MaxPoints if this will give us more points than our previous partial solutions.
        if (nPoints > nMaxPoints) {nMaxPoints = nPoints;}
    }

    return nMaxPoints;
}

int main(){

    FILE *fin = fopen("inflate.in", "r");
    FILE *fout = fopen("inflate.out","w");

    assert(fin);
    assert(fout);
    
    int nContestLength;
    int nNumClasses;

    fscanf(fin, "%d %d\n", &nContestLength, &nNumClasses);

    //Mark all problem categories as uninitialized
    for (int i = 0; i < MAX_PROBLEM_CATEGORIES; i++){
        g_ProblemCategories[i].first = UNINITIALIZED;
        g_ProblemCategories[i].second = UNINITIALIZED;
    }

    //read in our data
    for (int i=0; EOF != fscanf(fin, "%d %d\n", &g_ProblemCategories[i].first, &g_ProblemCategories[i].second); i++)
        { 
            dprintf(("Read in %d, %d\n", g_ProblemCategories[i].first, g_ProblemCategories[i].second));       
        }
    

    for (int i=0; i<= nContestLength; i++){
        g_HighScores[i] = CalculatePoints(i);
        dprintf(("Partial points for contest length %d: \t %d\n", i, g_HighScores[i]));
    }

    fprintf(fout, "%d\n", g_HighScores[nContestLength]);

    exit(0);

}
