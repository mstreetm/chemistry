#include "menu.h"
#include "compound.h"

#include <iostream>
#include <fstream>

using namespace std;

void runCompoundMolarMass(){
  Compound compound;
  compound.getFormula();
  compound.parseFormula();
  compound.addElementMolarMasses();
  compound.addCompoundMolarMass();
  cout << compound.compoundData.molarMass << "\n";
}
