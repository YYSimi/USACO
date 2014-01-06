/*
  ID:  ysimidjiy1
  LANG: C++
  TASK: kimbits
*/

#define NDEBUG

#ifndef NDEBUG
#define DEBUG
#endif

#define TASKNAME kimbits

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
#include <iomanip>

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

//g_DpTable[i][j] = number of strings with at most i digits and at most j 1's.

class DpSolver {

public:
    DpSolver() {Initialize(); Generate();}
    int Locate(unsigned int nPosition, int nOnes) {
        int result = 0;
        for (int nBit = 31; nBit >= 0; nBit--) {
            if (m_DpTable[nBit][nOnes] < nPosition) {
                unsigned int bitToSet = 1 << nBit;
                DBGRUN(std::cout << "subtracting " << m_DpTable[nBit][nOnes] << " from nPosition" << std::endl);
                nPosition -= m_DpTable[nBit][nOnes];
                nOnes--;
                DBGRUN(std::cout << "Bit " << nBit << " needs to be set" << std::endl);
                DBGRUN(std::cout << "new nPosition: " << nPosition << ", new nOnes: " << nOnes << std::endl);
                result = result | bitToSet;
                DBGRUN(std::cout << "bit " << bitToSet << " is being set" << std::endl);
            }
        }
        return result;
    }

private:
    void Initialize() {
        for (int i = 0; i < TABLESIZE; i++) {
            m_DpTable[0][i] = 1;
            m_DpTable[i][0] = 1;
        }
    }

    void Generate() {
        assert(TABLESIZE > 0);
        for (int i = 1; i < TABLESIZE; i++) {
            for (int j = 1; j < TABLESIZE; j++) {
                m_DpTable[i][j] = m_DpTable[i-1][j-1] + m_DpTable[i-1][j];
            }
        }
        DBGRUN(std::cout << "Table Initialized.  Printing..." << std::endl);
        //DBGRUN(PrettyPrintTable();)
    }

    void PrettyPrintTable() {
        for (int j = 0; j < TABLESIZE; j++) {
            for (int i = 0; i < TABLESIZE; i++) {
                std::cout << m_DpTable[i][j];
                if (i != TABLESIZE-1) { std::cout << " ";}
            }
            std::cout << std::endl;
        }
    }

    //Private Member variables
    static const int TABLESIZE = 32;
    unsigned int m_DpTable[TABLESIZE][TABLESIZE];
};

class CDpSolverTest: public IUnitTests {
public:
    CDpSolverTest(int nPosition, int nOnes): IUnitTests("DpSolverTest"), 
                                             nPosition(nPosition), nOnes(nOnes) {}
private:
    int nPosition, nOnes;
    DpSolver dpSolver;
    void PrintParametersHook() {std::cout << "nPosition: " << nPosition << ", nOnes: " << nOnes << std::endl; }
    void TestFunction() {std::cout << "DpSolver.Locate() returned " << dpSolver.Locate(nPosition, nOnes)
                                   << std::endl;}
};

int main(){

#ifdef DEBUG
    CSampleTest SampleTest(3, 5);
    SampleTest.Execute();
#endif

#ifdef DEBUG
    CDpSolverTest dpsTest(6,2);
    dpsTest.Execute();
#endif
    
    unsigned int nPosition, nPrecision, nOnes;

    std::ifstream fIn("kimbits.in");
    std::ofstream fOut("kimbits.out");
    fIn >> nPrecision >> nOnes >> nPosition;
    DBGRUN(std::cout << "read input: " << nPrecision << " " << nOnes << " " << nPosition << std::endl);
    DpSolver dpSolver;
    int nAns = dpSolver.Locate(nPosition, nOnes);
    //fOut << std::setfill('0') << std::setw(nPrecision) << dpSolver.Locate(nPosition, nOnes) << std::endl;
    for (int i = nPrecision -1; i >= 0; i--){
        fOut << !!(nAns & 1 << i);
    }
    fOut << std::endl;

    exit(0);

}
