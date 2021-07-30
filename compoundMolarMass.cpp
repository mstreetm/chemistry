#include "element.h"
#include "menu.h"
#include "stringHelpers.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

// void getElementMasses();
void updateFiles();
string getCompoundString();
void parseCompoundString(string compound);
void addMolarMasses();
float getCompoundMolarMass();
void getPreviousCompounds();
bool checkCmpdList(string compound);

// map<string, float> elemList;
map<string, float> cmpdList;
bool cmpdChanged = false;
bool elemChanged = false;
// vector<Element> elements;
// int numElem = 0;
bool doFileInput = false;
Compound compound;
// ifstream fin("C:/Users/moniq/Desktop/input.txt");

void runCompoundMolarMass(){
  getElementMasses();
  getPreviousCompounds();
  bool doAnother = 1;
  cout << "Would you like file input?\n";
  cin >> doFileInput;
  while(doAnother){
  cout << getCompoundMolarMass() << "\n";
    if(!doFileInput){
      cout << "Would you like to do another?\n";
      cin >> doAnother;
    }else if(fin.eof()){
      doAnother = 0;
    }
  }
  updateFiles();
}

void updateFiles(){
  if(elemChanged){
    ofstream eout("elements.txt");
    for(auto i = elemList.begin(); i != elemList.end(); i++){
      eout << i->first << " " << i->second << "\n";
    }
  }
  if(cmpdChanged){
    ofstream cmout("compounds.txt");
    for(auto i = cmpdList.begin(); i != cmpdList.end(); i++){
      cmout << i->first << " " << i->second << "\n";
    }
  }
}

string getCompoundString(){
  if(doFileInput){
    fin >> compound.compoundData.symbol;
  }else{
    cout << "Enter the compound formula: ";
    cin >> compound.compoundData.symbol;
  }
  return compound.compoundData.symbol;
}

void parseCompoundString(Compound cmpd){
  //elements.clear();
  stack<int> parenStack;
  for(int i = 0; i < cmpd.compoundData.symbol.length(); i++){
    if(isUpperLetter(cmpd.compoundData.symbol[i])){
      string key = "";
      key += cmpd.compoundData.symbol[i];
      string number = "";
      int num;
      if(isLowerLetter(cmpd.compoundData.symbol[i + 1])){
        key += cmpd.compoundData.symbol[i + 1];
        i++;
      }
      while(isNumber(cmpd.compoundData.symbol[i + 1])){
        number += cmpd.compoundData.symbol[i + 1];
        i++;
      }
      num = stringToNum(number);
      Element tempElem(key, num);
      cmpd.elements.push_back(tempElem);
      cmpd.numElements++;
    }else if(isOpenParentheses(cmpd.compoundData.symbol[i])){
      parenStack.push(cmpd.numElements);
    }else if(isClosedParentheses(cmpd.compoundData.symbol[i])){
      int start = parenStack.top();
      parenStack.pop();
      string number = "";
      int num;
      while(isNumber(cmpd.compoundData.symbol[i + 1])){
        number += cmpd.compoundData.symbol[i + 1];
        i++;
      }
      num = stringToNum(number);
      for(int i = start; i < cmpd.numElements; i++){
        cmpd.elements[i].amount.number *= num;
      }
    }
  }
}

void addMolarMasses(){
  for(int i = 0; i < compound.numElements; i++){
    if(elemList.find(compound.elements[i].elementData.symbol) == elemList.end()){
      cout << "There is no molar mass for " << compound.elements[i].elementData.symbol << " in the system, please enter one: \n";
      cin >> elemList[compound.elements[i].elementData.symbol];
      elemChanged = true;
    }
    compound.elements[i].elementData.molarMass = elemList[compound.elements[i].elementData.symbol];
  }
}

float getCompoundMolarMass(){
  // string compound = getCompoundString();
  float molarMass = 0;
  if(!checkCmpdList(compound.compoundData.symbol)){
    parseCompoundString(compound);
    addMolarMasses();
    for(auto elem : compound.elements){
      molarMass += elem.elementData.molarMass * elem.amount.number;
    }
    cmpdList[compound.compoundData.symbol] = molarMass;
    cmpdChanged = true;
  }else{
    molarMass = cmpdList[compound.compoundData.symbol];
  }
  return molarMass;
}

void getPreviousCompounds(){
  ifstream cmin("compounds.txt");
  string key;
  float value;
  cmin >> key;
  while(!cmin.eof()){
    cmin >> value;
    cmpdList[key] = value;
    cmin >> key;
  }
}

bool checkCmpdList(string compound){
  if(cmpdList.find(compound) != cmpdList.end()){
    return true;
  }
  return false;
}
