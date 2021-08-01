#include "menu.h"
#include "selector.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
  getElementMolarMasses();
  getCompoundMolarMasses();
  getDoFileInput();
  int prgm = selectProgram();
  while(prgm != 0){
    runProgram(prgm);
    prgm = selectProgram();
  }
  updateFiles();
  return 0;
}
