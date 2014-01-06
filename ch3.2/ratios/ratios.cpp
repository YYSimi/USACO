/*
ID:  ysimidjiy1
LANG: C++
TASK: ratios
*/

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

class Ratio {
public:
    //Ratio(): a(0), b(0), c(0) {}
    explicit Ratio(int a): a(a), b(a), c(a) {}
    Ratio(int a, int b, int c): a(a), b(b), c(c) {}
    Ratio(const Ratio &rhs): a(rhs.a), b(rhs.b), c(rhs.c) {}
    Ratio& operator*=(const Ratio &rhs) {
        a *= rhs.a;
        b *= rhs.b;
        c *= rhs.c;
        return *this;
    }
    Ratio& operator+=(const Ratio &rhs) {
        a += rhs.a;
        b += rhs.b;
        c += rhs.c;
        return *this;
    }
    int a;
    int b;
    int c;
};

Ratio operator*(Ratio lhs, const Ratio& rhs) {
    lhs *= rhs;
    return lhs;
}

Ratio operator+(Ratio lhs, const Ratio& rhs) {
    lhs += rhs;
    return lhs;
}

static const int TARGETID = 3;
static const int MAXUNITS = 99;
std::vector<Ratio> g_ratios;

bool Validate(int x, int y, int z) {
    Ratio totalRatio(Ratio(x)*g_ratios[0]+Ratio(y)*g_ratios[1]+Ratio(z)*g_ratios[2]);
    int prodA, prodB, prodC;
    prodA = totalRatio.a*g_ratios[TARGETID].b*g_ratios[TARGETID].c;
    prodB = totalRatio.b*g_ratios[TARGETID].a*g_ratios[TARGETID].c;
    prodC = totalRatio.c*g_ratios[TARGETID].a*g_ratios[TARGETID].b;
    if ( prodA == prodB && prodB == prodC) {return true; }
    return false;
}

bool Iterate() {
    int j, k;
    for (int sum1 = 1; sum1 <= 3*MAXUNITS; sum1++) { //i+j+k
        for (int sum2 = 1; sum2 < sum1; sum2++) {//i+j
            for (int i = 1; i < sum2; i++) {//i
                j = sum2 - i;
                k = sum1 - sum2;
                if (Validate(i, j, k)) {
                    DBGRUN(std::cout << "Found it!: (" << i << ", " << j << ", " << k << ")" << std::endl);
                    break;
                }
            }
        }
    }
}

int main(){

    std::ifstream fIn("ratios.in");
    std::ofstream fOut("ratios.out");

    int a, b, c;
    for (int i = 0; i < 4; i++) {
        fIn >> a >> b >> c;
        g_ratios.push_back(Ratio(a, b, c));
    }

    Iterate();

#ifdef DEBUG
    CSampleTest SampleTest(3, 5);
    SampleTest.Execute();
#endif
  exit(0);

}
