/*
ID:  ysimidjiy1
LANG: C++11
TASK: ratios
*/

#define NDEBUG

#ifndef NDEBUG
#define DEBUG
#endif

#define TASKNAME ratios

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
#include <vector>
#include <queue>

static const int MAXFEEDS = 101;

struct Feed{
	int a;
	int b;
	int c;
};

struct Ratio {
	int f1;
	int f2;
	int f3;
};

struct FeedQuantity {
	Feed feed;
	int quantity;
};

bool g_feedsVisited[100][100][100] = { 0 };
Feed g_feeds[3];
Feed g_targetFeed;

void PrintRatio(const Ratio &r){
	DBGRUN(std::cout << r.f1 << " " << r.f2 << " " << r.f3 << " " << std::endl);
}

bool TestFeedRatio(Ratio r) {
	DBGRUN(std::cout << "Testing Feed Ratio" << std::endl);

	Feed sum;
	if (r.f1 == r.f2 && r.f2 == r.f3 && r.f3 == 0) { return false; }
	sum.a = r.f1*g_feeds[0].a + r.f2*g_feeds[1].a + r.f3*g_feeds[2].a;
	sum.b = r.f1*g_feeds[0].b + r.f2*g_feeds[1].b + r.f3*g_feeds[2].b;
	sum.c = r.f1*g_feeds[0].c + r.f2*g_feeds[1].c + r.f3*g_feeds[2].c;
	

	//Test if sum.a/target.a = sum.b/target.b
	if (sum.a*g_targetFeed.b == sum.b*g_targetFeed.a) {
		//Test if sum.b/target.b = sum.c/target.c
		if (sum.b*g_targetFeed.c == sum.c*g_targetFeed.b) { return true; }
	}
	return false;
}

void MarkVisited(const Ratio &r) {
	Ratio temp = r;
	while (temp.f1 < MAXFEEDS && temp.f2 < MAXFEEDS && temp.f3 < MAXFEEDS) {
		g_feedsVisited[temp.f1][temp.f2][temp.f3] = true;
		temp.f1 += r.f1; temp.f2 += r.f2; temp.f3 += r.f3;
	}
}

void EnqueueRatio(const Ratio &r, std::queue<Ratio> &qRatios) {
	DBGRUN(std::cout << "Enqueue-ing Ratio" << std::endl);
	PrintRatio(r);
	//Check if we've already visited this ratio
	if (!g_feedsVisited[r.f1][r.f2][r.f3]) {
		PrintRatio(r);

		//Mark this ratio and all multiples of this ratio as visited.
		MarkVisited(r);
		PrintRatio(r);

		//Add this ratio to the queue
		qRatios.push(r);
		PrintRatio(r);
	}
	return;

}

void EnqueueChildRatios(const Ratio &r, std::queue<Ratio> &qRatios) {
	DBGRUN(std::cout << "Enqueue-ing Child Ratios" << std::endl);
	Ratio rNew = r;
	rNew.f1 += 1;
	EnqueueRatio(rNew, qRatios);
	rNew.f1 -= 1;
	rNew.f2 += 1;
	EnqueueRatio(rNew, qRatios);
	rNew.f2 -= 1;
	rNew.f3 += 1;
	EnqueueRatio(rNew, qRatios);
	DBGRUN(std::cout << "Enqueued Child Ratios" << std::endl;)

	return;
}

Ratio BFS() {
	std::queue<Ratio> qRatios;
	Ratio rInitial;
	rInitial.f1 = 0; rInitial.f2 = 0; rInitial.f3 = 0;
	qRatios.push(rInitial);
	Ratio rCurrent;
	Ratio retval = rInitial;

	while (!qRatios.empty())
	{
		rCurrent = qRatios.front();
		if (TestFeedRatio(rCurrent)) { retval = rCurrent; break; }
		EnqueueChildRatios(rCurrent, qRatios);
		qRatios.pop();
	}
	return rCurrent;
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

    std::ifstream fIn("ratios.in");
    std::ofstream fOut("ratios.out");

	//g_feeds[3]
	//g_targetFeed

	//Read the Input
	fIn >> g_targetFeed.a >> g_targetFeed.b >> g_targetFeed.c;
	for (int i = 0; i < 3; i++) {
		fIn >> g_feeds[i].a >> g_feeds[i].b >> g_feeds[i].c;
	}

	Ratio target = BFS();

	if (target.f1 == 0 && target.f2 == 0 && target.f3 == 0) { fOut << "NONE" << std::endl;  }
	else { fOut << target.f1 << " " << target.f2 << " " << target.f3 << " " << (target.f1*g_feeds[0].a + target.f2*g_feeds[1].a + target.f3*g_feeds[2].a)/g_targetFeed.a << std::endl; }

#ifdef DEBUG
    CSampleTest SampleTest(3, 5);
    SampleTest.Execute();
#endif
  exit(0);

}
