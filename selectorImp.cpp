#include "selector.h"
#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

std::map<string, int> optionList = {
  {"-1", -1}, {"help", -1}, {"h", -1},
  {"0", 0}, {"exit", 0}, {"e", 0},
  {"1", 1}, {"compoundMolarMass", 1}, {"cMM", 1},
  {"2", 2}, {"empiricalMolecular", 2}, {"eM", 2}
};

void getDoFileInput(){
  cout << "Would you like file input (1/0): ";
  cin >> doFileInput;
}

int selectProgram(){
  string input;
  if(!doFileInput){
    cout << "Please select a program: ";
    cin >> input;
  }else if(!fin.eof()){
    fin >> input;
    if(fin.eof()){
      return 0;
    }
  }else{
    return 0;
  }
  int prgm;
  if(optionList.find(input) == optionList.end()){
    prgm = -2;
  }else{
    prgm = optionList[input];
  }
  switch(prgm){
    case -2:
      cout << "Invalid response.\n";
    case -1:
      cout << "Valid responses include the following:\n";
      cout << "For the help page: -1, help, h\n";
      cout << "To exit: 0, exit, e\n";
      cout << "For compound molar mass: 1, compoundMolarMass, cMM\n";
      cout << "For empirical/molecular formulas: 2, empiricalMolecular, eM\n";
      return selectProgram();
      break;
    default:
      return prgm;
      break;
  }
}

void runProgram(int program){
  switch(program){
    case 1:
      runCompoundMolarMass();
      break;
    case 2:
      runEmpiricalMolecular();
      break;
  }
}
