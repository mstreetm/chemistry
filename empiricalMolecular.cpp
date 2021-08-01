#include "compound.h"
#include "menu.h"
#include "helpers.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

void runEmpiricalMolecular(){
  bool doMolecular = false;
  Compound compound;
  compound.getElementAmounts();
  compound.addElementMolarMasses();
  compound.elementsMassToMoles();
  compound.elementsMolesDivideBySmall();
  compound.elementsMolesMultiplyTillWhole();
  compound.addCompoundFormula('e');
  cout << compound.empiricalData.symbol << "\n";
  if(!doFileInput){
    cout << "Would you like the molecular formula (1/0): ";
    cin >> doMolecular;
  }else if(!fin.eof()){
    fin >> doMolecular;
  }
  if(doMolecular){
    compound.addCompoundMolarMass('e');
    compound.getCompoundMolarMass();
    compound.molecularFromEmpirical();
    cout << compound.compoundData.symbol << "\n";
    doMolecular = false;
  }
}
