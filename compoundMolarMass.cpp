#include "element.h"
#include "menu.h"

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
bool isUpperLetter(char a);
bool isLowerLetter(char a);
bool isNumber(char a);
bool isOpenParentheses(char a);
bool isClosedParentheses(char a);
int stringToNum(string snum);
void addMolarMasses();
float getCompoundMolarMass();
void getPreviousCompounds();
bool checkCmpdList(string compound);

// map<string, float> elemList;
map<string, float> cmpdList;
bool cmpdChanged = false;
bool elemChanged = false;
vector<Element> elements;
int numElem = 0;
bool doFileInput = false;
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
  string compound;
  if(doFileInput){
    fin >> compound;
  }else{
    cout << "Enter the compound: \n";
    cin >> compound;
  }
  return compound;
}

void parseCompoundString(string compound){
  //elements.clear();
  stack<int> parenStack;
  for(int i = 0; i < compound.length(); i++){
    if(isUpperLetter(compound[i])){
      string key = "";
      key += compound[i];
      string number = "";
      int num;
      if(isLowerLetter(compound[i + 1])){
        key += compound[i + 1];
        i++;
      }
      while(isNumber(compound[i + 1])){
        number += compound[i + 1];
        i++;
      }
      num = stringToNum(number);
      Element tempElem(key, num);
      elements.push_back(tempElem);
      numElem++;
    }else if(isOpenParentheses(compound[i])){
      parenStack.push(numElem);
    }else if(isClosedParentheses(compound[i])){
      int start = parenStack.top();
      parenStack.pop();
      string number = "";
      int num;
      while(isNumber(compound[i + 1])){
        number += compound[i + 1];
        i++;
      }
      num = stringToNum(number);
      for(int i = start; i < numElem; i++){
        elements[i].amount.number *= num;
      }
    }
  }
}

void addMolarMasses(){
  for(int i = 0; i < numElem; i++){
    if(elemList.find(elements[i].elementData.symbol) == elemList.end()){
      cout << "There is no molar mass for " << elements[i].elementData.symbol << " in the system, please enter one: \n";
      cin >> elemList[elements[i].elementData.symbol];
      elemChanged = true;
    }
    elements[i].elementData.molarMass = elemList[elements[i].elementData.symbol];
  }
}

float getCompoundMolarMass(){
  string compound = getCompoundString();
  float molarMass = 0;
  if(!checkCmpdList(compound)){
    parseCompoundString(compound);
    addMolarMasses();
    for(auto elem : elements){
      molarMass += elem.elementData.molarMass * elem.amount.number;
    }
    cmpdList[compound] = molarMass;
    cmpdChanged = true;
  }else{
    molarMass = cmpdList[compound];
  }
  return molarMass;
}

bool isNumber(char a){
  int ia = a;
  int diff = ia - '0';
  if((diff > 9) || (diff < 0)){
    return false;
  }
  return true;
}

bool isLowerLetter(char a){
  int ia = a;
  int diff = ia - 'a';
  if((diff >= 0) && (diff < 26)){
    return true;
  }
  return false;
}

bool isUpperLetter(char a){
  int ia = a;
  int diff = ia - 'A';
  if((diff >= 0) && (diff < 26)){
    return true;
  }
  return false;
}

bool isOpenParentheses(char a){
  if(a == '('){
    return true;
  }
  return false;
}

bool isClosedParentheses(char a){
  if(a == ')'){
    return true;
  }
  return false;
}

int stringToNum(string snum){
  if(snum == ""){
    return 1;
  }
  int nnum = 0;
  int len = snum.length();
  for(int i = 0; i < len; i++){
    int base = snum[i] - '0';
    nnum += base * pow(10, len - 1 - i);
  }
  return nnum;
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
