/*
ID:  ysimidjiy1
LANG: C++11
TASK: msquare
*/

//#define NDEBUG

#ifndef NDEBUG
#define DEBUG
#endif

#define TASKNAME msquare

#ifdef DEBUG
#define DBGRUN(x) x
#else
#define DBGRUN(x) 
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

static const int nNumbers = 8;
static const int nMoves = 3;

int g_nStatesVisited = 0;

typedef struct state { uint8_t nums[nNumbers]; std::list<char> moves; } state;
std::unordered_map<uint32_t, bool> g_stateMap;
state g_targetState;
state g_initialState;
std::queue<state> g_bfsQueue;

void PrintState(const state &inputState) {
	for (int i = 0; i < nNumbers; i++) {
		std::cout << (inputState.nums[i] +1);
	}
} 

void PrintMoves(const state &inputState, ostream &outStream = std::cout) {
	int nCharsPrinted = 0;
	for (auto it = inputState.moves.begin(); it != inputState.moves.end(); ++it){
		outStream << *it;
		++nCharsPrinted;
		//Add a newline after every 60 chars
		if (nCharsPrinted == 60) {
			outStream << std::endl;
			nCharsPrinted = 0;
		}
	}
	outStream << std::endl;
};

int PackState(const state &inState) {
	int retval = 0;
	int current = 0;
	for (int i = 0; i < nNumbers; i++) {
		retval |= inState.nums[i] << (3 * i);
	}
	return retval;

}

int StateCmp(const state &s1, const state &s2){
	for (int i = 0; i < nNumbers; i++){
		if (s1.nums[i] != s2.nums[i]) { return s1.nums[i] - s2.nums[i]; }
	}
	return 0;
}

void ReadData() {
	std::ifstream myIfStream("msquare.in");
	int nReadIn = 0;
	for (int i = 0; i < nNumbers; i++) {
		myIfStream >> nReadIn;
		g_targetState.nums[i] = nReadIn - 1;
		g_initialState.nums[i] = i;
	}
#ifdef DEBUG
	std::cout << "Read in data:" << std::endl;
	PrintState(g_targetState);
	std::cout << std::endl;
	std::cout << "Initial state set to:" << std::endl;
	PrintState(g_initialState);
	std::cout << std::endl;
#endif
}

void WriteData(state &outState) {
	std::ofstream myOfStream("msquare.out");
	myOfStream << outState.moves.size() << endl;
	PrintMoves(outState, myOfStream);
}

//Applies MoveA to the passed-in state
void MoveA(state &inState) {
	state oldstate = inState;
	inState.nums[0] = oldstate.nums[7];
	inState.nums[1] = oldstate.nums[6];
	inState.nums[2] = oldstate.nums[5];
	inState.nums[3] = oldstate.nums[4];
	inState.nums[4] = oldstate.nums[3];
	inState.nums[5] = oldstate.nums[2];
	inState.nums[6] = oldstate.nums[1];
	inState.nums[7] = oldstate.nums[0];

	inState.moves.push_back('A');
}

void MoveB(state &inState) {
	state oldstate = inState;
	inState.nums[0] = oldstate.nums[3];
	inState.nums[1] = oldstate.nums[0];
	inState.nums[2] = oldstate.nums[1];
	inState.nums[3] = oldstate.nums[2];
	inState.nums[4] = oldstate.nums[5];
	inState.nums[5] = oldstate.nums[6];
	inState.nums[6] = oldstate.nums[7];
	inState.nums[7] = oldstate.nums[4];

	inState.moves.push_back('B');
}

void MoveC(state &inState) {
	state oldstate = inState;
	inState.nums[0] = oldstate.nums[0];
	inState.nums[1] = oldstate.nums[6];
	inState.nums[2] = oldstate.nums[1];
	inState.nums[3] = oldstate.nums[3];
	inState.nums[4] = oldstate.nums[4];
	inState.nums[5] = oldstate.nums[2];
	inState.nums[6] = oldstate.nums[5];
	inState.nums[7] = oldstate.nums[7];

	inState.moves.push_back('C');
}


state& RunBfs(){

	assert(!g_bfsQueue.empty());
	state currentState = g_bfsQueue.front();

#ifdef DEBUG
	std::cout << "Current State is ";	PrintState(currentState); std::cout << std::endl;
	std::cout << "Current moves are "; PrintMoves(currentState); std::cout << std::endl;
#endif //DEBUG

	//Are we at our goal?  If so, return our result.
	if (!StateCmp(currentState, g_targetState)) {
		return g_bfsQueue.front();
	}
	//Otherwise, enqueue new states
	else {
		g_bfsQueue.pop();
		state newStates[nMoves];
		for (int i = 0; i < nMoves; i++) {
			newStates[i] = currentState;
		}

		MoveA(newStates[0]);
		MoveB(newStates[1]);
		MoveC(newStates[2]);

		for (int i = 0; i < nMoves; i++) {
			//Check if we've already visited this node
			if (g_stateMap[PackState(newStates[i])] != true){
				//If not, mark it as visited and enqueue it	
				g_bfsQueue.push(newStates[i]);
				g_stateMap[PackState(newStates[i])] = true;

#ifdef DEBUG
				++g_nStatesVisited;
				std::cout << "numStatesVisited:" << g_nStatesVisited << std::endl;
#endif
			}
			else {
				DBGRUN(cout << "Already visited node with moves "; PrintMoves(newStates[i]); cout << endl);
			}
		}
	}

	//If we've gotten this far, Recur.
	return RunBfs();

}

state ExecuteProgram() {
	DBGRUN(cout << "Executing program!" << endl);

	//Initialize the queue
	g_stateMap[PackState(g_initialState)] = true;
	g_bfsQueue.push(g_initialState);

	//Perform our BFS
	return RunBfs();
}







class IUnitTests{
public:
    void Execute();
    IUnitTests(std::string _strTestName): strTestName(_strTestName) {};
    virtual ~IUnitTests() {};
protected:
    const std::string strTestName;
private: //Virtual/template methods and hooks
    virtual void TestFunction() = 0;
    virtual void PrintParametersHook() {}
};

class CSampleTest: public IUnitTests {
public:
    CSampleTest(int a, int b): IUnitTests(std::string("SampleTest")), nArgA(a), nArgB(b) {};

private:
    int nArgA;
    int nArgB;
    void PrintParametersHook() {std::cout << "nArgA: " << nArgA << ", nArgB: " << nArgB << std::endl;}
    void TestFunction() {return;}
};

class CPackStateTest : public IUnitTests {
public:
	CPackStateTest(state s) : IUnitTests(std::string("CPackStateTest")), m_state(s) {};

private:
	state m_state;
	void PrintParametersHook() { std::cout << "state: " << std::endl; PrintState(m_state); }
	void TestFunction() { std::cout << "PackedState: " << PackState(m_state) << std::endl; }
};


void IUnitTests::Execute(){
    std::cout << std::endl;
    std::cout << "Executing " << strTestName << " unit tests." << std::endl;
    PrintParametersHook();
    TestFunction();
    std::cout << strTestName << " unit tests finished executing." << std::endl;
    std::cout << std::endl;
}




int main(){
	state returnedState;

	ReadData();
	returnedState = ExecuteProgram();
	WriteData(returnedState);

#ifdef DEBUG
	CSampleTest SampleTest(3, 5);
	SampleTest.Execute();

	CPackStateTest PackStateTest(g_initialState);
	PackStateTest.Execute();
#endif
	exit(0);

}

