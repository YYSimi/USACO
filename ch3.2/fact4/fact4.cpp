/*
ID:  ysimidjiy1
LANG: C++
TASK: fact4
*/

#define TASKNAME fact4
//#define DEBUG

#ifdef DEBUG
#define dbgrun(x) (x)
#else
#define dbgrun(x) while(0) {};
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

int NumberOfFives(int n){
    int retval = 0;
    dbgrun(std::cout << n << " has ");
    n = n/5;
    while (n >= 1){
        retval += n;
        n = n/5;
    }
    dbgrun(std::cout << retval << " fives." << std::endl);
    return retval;
}

int SpecialFactorial(int nInput, int nTwosToIgnore) {
#ifdef DEBUG 
    int nInputOld = nInput;
    int nTwosToIgnoreOld = nTwosToIgnore;
#endif

    int retval = 0;
    int nNextInput = nInput-1;

    if (nInput == 1) {retval = 1; goto Return;}
    if (nInput == 0) {retval = 1; goto Return;}
    if (nInput < 0) {
        std::cerr << "SpecialFactorial was called with arguments " << nInput << ", " << nTwosToIgnore << std::endl;
        retval = -1;
        goto Return;
    }
    
    //Kill factors of 5
    while ( !(nInput % 5)) {nInput = nInput/5;}
    //Kill factors of 2 if necessary
    while ( !(nInput %2) && (nTwosToIgnore > 0) ) {
        dbgrun(std::cout << "nInputCurrent: " << nInput << " nTwosToIgnoreCurrent: " << nTwosToIgnore << std::endl);
        nInput = nInput/2;
        nTwosToIgnore--;
    }

    retval = (nInput * SpecialFactorial(nNextInput, nTwosToIgnore)) % 10;

 Return:
    dbgrun(std::cout << "nInput: " << nInputOld << " nTwosToIgnore: " << nTwosToIgnore << " retval: " << retval << std::endl);
    return retval;
}

void NumberOfFivesUnitTests(){
    NumberOfFives(0);
    NumberOfFives(1);
    NumberOfFives(5);
    NumberOfFives(7);
    NumberOfFives(12);
    NumberOfFives(25);
    NumberOfFives(26);
    NumberOfFives(125);
    NumberOfFives(130);
}

void SpecialFactorialUnitTests(){
    int n = 0;
    dbgrun(std::cout << "Special Facotrial of " << n << std::endl);
    SpecialFactorial(n, NumberOfFives(n));
    n = 5;
    dbgrun(std::cout << "Special Facotrial of " << n << std::endl);
    SpecialFactorial(n, NumberOfFives(n));
    n = 7;
    dbgrun(std::cout << "Special Facotrial of " << n << std::endl);
    SpecialFactorial(n, NumberOfFives(n));
    n = 12;
    dbgrun(std::cout << "Special Facotrial of " << n << std::endl);
    SpecialFactorial(n, NumberOfFives(n));    
}

void UnitTests() {
    NumberOfFivesUnitTests();
    SpecialFactorialUnitTests();
}

int main(){

#ifdef DEBUG 
    UnitTests();
#endif

  std::ifstream fIn("fact4.in");;
  std::ofstream fOut("fact4.out");
  if (!fIn.is_open() || !fOut.is_open()) {
      std::cerr << "Failed to open file";
      goto Return;
  }

  int nInput;
  fIn >> nInput;
  
  fOut << SpecialFactorial(nInput, NumberOfFives(nInput)) << std::endl;

Return:
  if (fIn.is_open()){
      fIn.close();
  }
  if (fOut.is_open()){
      fOut.close();
  }
  fOut.close();
  
  return 0;
}
