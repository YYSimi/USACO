/*
ID:  ysimidjiy1
LANG: C++11
TASK: skidesign
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

const auto TASKNAME = std::string("skidesign");
const auto MAXHILLS = 1000;
const auto MAXHEIGHT = 100;

int g_heights[MAXHILLS];
int g_hillCount;

int calculateCost(int newMinHeight) {
    int newMaxHeight = newMinHeight + 17;
    int costSoFar = 0;
    
    for (int i = 0; i < g_hillCount; ++i) {
        if (g_heights[i] < newMinHeight) {
            costSoFar += (newMinHeight - g_heights[i]) * (newMinHeight - g_heights[i]);
        }
        else if (g_heights[i] > newMaxHeight) {
            costSoFar += (g_heights[i] - newMaxHeight) * (g_heights[i] - newMaxHeight);
        }
    }
    
    return costSoFar;
}

int main(){

    auto fInStream = std::ifstream(TASKNAME + ".in");
    auto fOutStream = std::ofstream(TASKNAME + ".out");

    fInStream >> g_hillCount;
    for(int i = 0; i < g_hillCount; ++i) {
        fInStream >> g_heights[i];
    }
    
    // std::cout << g_heights[0] << " " << g_heights[1] << " " << g_heights[2] << std::endl;
    
    int minCost = -1;
    for (int i = 0; i < 84; ++i) {
        auto cost = calculateCost(i);
        if (minCost == -1 || cost < minCost) {
            minCost = cost;
        }
    }
    
    fOutStream << minCost << std::endl;

    return 0;

}
