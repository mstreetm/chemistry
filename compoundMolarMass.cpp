#include "element.h"
#include "menu.h"
#include "stringHelpers.h"
#include "compound.h"

#include <iostream>
#include <fstream>

using namespace std;

void runCompoundMolarMass(){
  getElementMolarMasses();
  getCompoundMolarMasses();
  bool doAnother = 1;
  cout << "Would you like file input?\n";
  cin >> doFileInput;
  while(doAnother){
    Compound compound;
    compound.getFormula();
    compound.parseFormula();
    compound.addElementMolarMasses();
    compound.addCompoundMolarMass();
    cout << compound.compoundData.molarMass << "\n";
    if(!doFileInput){
      cout << "Would you like to do another?\n";
      cin >> doAnother;
    }else if(fin.eof()){
      doAnother = 0;
    }
  }
  updateFiles();
}
