#include "menu.h"
#include "compound.h"

#include <iostream>
#include <fstream>

using namespace std;

void runCompoundMolarMass(){
  //gets the molar mass of a compound by adking the user for the formula
  Compound compound;
  compound.getFormula();
  compound.parseFormula();
  compound.addElementMolarMasses();
  compound.addCompoundMolarMass();
  cout << compound.compoundData.molarMass << "\n";
}
