/*
ID:  ysimidjiy1
LANG: C++11
TASK: fence
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <functional>

const auto TASKNAME = std::string("fence");
const auto MAXFENCE = 500;

auto g_nFences = 0;
auto g_maxFence = 0;
auto g_minFence = MAXFENCE + 1;

struct node {
    
    int id;
    std::priority_queue<int, std::vector<int>, std::greater<int> > m_fenceEdges;
    int m_deferredRemoveFenceIds[MAXFENCE] = {0};
};

node g_nodes[MAXFENCE + 1];
std::stack<int> g_path;

void findCycle(int nodeId) {
    node &currentNode = g_nodes[nodeId];
    if (currentNode.m_fenceEdges.empty()) {
        g_path.push(nodeId);
    }
    else {
        while(!currentNode.m_fenceEdges.empty()) {
            // Attempt to remove this edge.
            auto nextNodeId = currentNode.m_fenceEdges.top();
            if (currentNode.m_deferredRemoveFenceIds[nextNodeId]) //Has this edge already been removed by processing on another node?
            {
                --currentNode.m_deferredRemoveFenceIds[nextNodeId];
                currentNode.m_fenceEdges.pop();
                continue;
            }
            else {
                currentNode.m_fenceEdges.pop();
                ++(g_nodes[nextNodeId].m_deferredRemoveFenceIds[nodeId]);
                findCycle(nextNodeId);
            }
        }
        g_path.push(nodeId);
    }
}

int main(){

    auto fInStream = std::ifstream(TASKNAME + ".in");
    auto fOutStream = std::ofstream(TASKNAME + ".out");
    
    fInStream >> g_nFences;
    for (int i = 0; i < g_nFences; ++i) {
        int start, end;
        fInStream >> start;
        fInStream >> end;
        if (g_maxFence < start) {g_maxFence = start;}
        if (g_maxFence < end) {g_maxFence = end;}
        if (g_minFence > start) {g_minFence = start;}
        if (g_minFence > end) {g_minFence = end;}
        g_nodes[start].m_fenceEdges.push(end);
        g_nodes[end].m_fenceEdges.push(start);
    }

    auto firstFenceId = 0;
    for (int i = g_minFence; i <= g_maxFence; ++i) {
        if (g_nodes[i].m_fenceEdges.size() % 2) { //Do we have odd degree?  Start there if so.
            firstFenceId = i;
            break;
        }
        else {
            firstFenceId = g_minFence;
        }
    }
    
    findCycle(firstFenceId);
    while(!g_path.empty()) {
        fOutStream << g_path.top() << std::endl;
        g_path.pop();
    }
    
    return 0;

}