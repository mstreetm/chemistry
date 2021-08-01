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
  getElementMolarMasses();
  bool doAnother = true;
  bool doMolecular = false;
  cout << "Would you like file input (1/0): ";
  cin >> doFileInput;
  int nextNumElem = -1;
  while(doAnother){
    Compound compound;
    compound.getElementAmounts(nextNumElem);
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
    if(!doFileInput){
      cout << "Would you like to do another (1/0): ";
      cin >> doAnother;
    }else if(fin.eof()){
      doAnother = false;
    }else{
      string newl;
      fin >> newl;
      if(fin.eof()){
        doAnother = false;
        break;
      }
      for(auto c : newl){
        if(!isNumber(c)){
          cout << "Error, eM.cpp line 58, see comment.\n";
          doAnother = false;
          break;
        }
        //COMMENT: error has something to do with file input, see what it is triggering on, and make another case or something?, It triggers if anything in the next line is not a number and it is not the end of the file.
      }
      nextNumElem = stringToNum(newl);
    }
  }
	updateFiles();
}
