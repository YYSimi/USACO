/*
ID:  ysimidjiy1
LANG: C++11
TASK: butter
*/

#define NDEBUG

#ifndef NDEBUG
#define DEBUG
#endif

#define TASKNAME butter

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
#include <cstdint>

using namespace std;

static const int MAXCOWS = 500;
static const int MAXPASTURES = 800;
static const int MAXPATHS = 1450;

static const int INFINITE = 500000;
static const int NONE = -1;

int g_nCows;
int g_nPastures;
int g_nPaths;

long g_pastureDistances[MAXPASTURES][MAXPASTURES]; //statically allocating for expedience.
                                                   //Always traverse using the second coordinate first!

int *g_cowLocs; //dynamically allocating an array of cow locations for practice.

void PrintPastureMatrix(){
	for (int i = 0; i < g_nPastures; i++) {
		for (int j = 0; j < g_nPastures; j++) {
			cout << g_pastureDistances[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void PrintCowLocs() {
	for (int i = 0; i < g_nCows; i++) {
		cout << g_cowLocs[i] << " ";
	}
	cout << endl;
	return;
}

void FloydWarshall() {
	static int nFirstHalf = 0;
	static int nSecondHalf = 0;
	static int nSum = 0;
	static int nCurrentDistance = 0;

	for (int k = 0; k < g_nPastures; k++) {
		for (int i = 0; i < g_nPastures; i++) {
			for (int f = i+1; f < g_nPastures; f++){
				if (i > k) { 
					nFirstHalf = g_pastureDistances[k][i];
					nSecondHalf = g_pastureDistances[k][f];
				}
				else {
					nFirstHalf = g_pastureDistances[i][k];

					if (f <= k) { nSecondHalf = g_pastureDistances[f][k]; }
					else { nSecondHalf = g_pastureDistances[k][f]; }
				}
				nSum = nFirstHalf + nSecondHalf;
				nCurrentDistance = g_pastureDistances[i][f];
				if (nSum < nCurrentDistance){
					g_pastureDistances[i][f] = nSum;
				}
			}
		}
	}

}

int FindBest() {
	int nBestSoFar = INFINITE;
	int bestPasture = -1;
	int cowlocCurrent = 0;

	int nTotalPath = 0;
	for (int targetPasture = 0; targetPasture < g_nPastures; targetPasture++) {
		nTotalPath = 0;
		for (int j = 0; j < g_nCows; j++) {
			cowlocCurrent = g_cowLocs[j];
			if (targetPasture < cowlocCurrent){
				nTotalPath += g_pastureDistances[targetPasture][cowlocCurrent];
			}
			else {
				nTotalPath += g_pastureDistances[cowlocCurrent][targetPasture];
			}
		}
		if (nTotalPath < nBestSoFar || nBestSoFar == INFINITE) { 
			nBestSoFar = nTotalPath; 
			bestPasture = targetPasture; 
		}
	}

	DBGRUN(cout << "Best Pasture: " << bestPasture << endl);
	return nBestSoFar;
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

void IUnitTests::Execute(){
    std::cout << std::endl;
    std::cout << "Executing " << strTestName << " unit tests." << std::endl;
    PrintParametersHook();
    TestFunction();
    std::cout << strTestName << " unit tests finished executing." << std::endl;
    std::cout << std::endl;
}

int main(){

	//Read Input
	ifstream fIn("butter.in");
	fIn >> g_nCows >> g_nPastures >> g_nPaths;
	g_cowLocs = new int[g_nCows];

	for (int i = 0; i < g_nCows; i++) {
		fIn >> g_cowLocs[i];
		--g_cowLocs[i];
	}

	//sanity checks
	assert(g_nCows < MAXCOWS);
	assert(g_nPastures < MAXPASTURES);
	assert(g_nPaths < MAXPATHS);

	//Init pastureDistances matrix 
	for (int i = 0; i < g_nPastures; i++) {
		for (int j = 0; j < g_nPastures; j++) {
			if (i == j) { g_pastureDistances[i][j] = 0; }
			else { g_pastureDistances[i][j] = INFINITE; }
		}
	}

	//Read in path lengths
	for (int i = 0; i < g_nPaths; i++) {
		int pastureInitial = 0;
		int pastureFinal = 0;
		int pathLength = 0;

		fIn >> pastureInitial >> pastureFinal;
		fIn >> pathLength;

		//Subtract 1 from the pasture numbers to make them zero-indexed.
		pastureInitial--;
		pastureFinal--;

		g_pastureDistances[pastureInitial][pastureFinal] = pathLength;
		g_pastureDistances[pastureFinal][pastureInitial] = pathLength;
	}

	DBGRUN(cout << "Initial Read:" << endl);
	DBGRUN(PrintPastureMatrix());
	DBGRUN(PrintCowLocs());

	//Perform Calculation
	FloydWarshall();

	DBGRUN(cout << endl);
	DBGRUN(cout << "FloydWarshall result:" << endl);
	DBGRUN(PrintPastureMatrix());

	int outval = FindBest();

	//Write Output
	DBGRUN(cout << "answer: " << outval << endl;)
	ofstream fOut("butter.out");
	fOut << outval << endl;


#ifdef DEBUG
    CSampleTest SampleTest(3, 5);
    SampleTest.Execute();
#endif
  exit(0);

}
