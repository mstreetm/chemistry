#include "compound.h"
#include "menu.h"
#include "stringHelpers.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

Compound::Compound(){
  //no init on elements
  numElements = 0;
  name = "Not Specified";
  ElementData tempCD;
  compoundData = tempCD;
  Amount tempA;
  amount = tempA;
}

Compound::Compound(std::vector<Element> elems, int num){
  for(int i = 0; i < num; i++){
    elements.push_back(elems[i]);
  }
  numElements = num;
  name = "Not Specified";
  ElementData tempCD;
  compoundData = tempCD;
  Amount tempA;
  amount = tempA;
}

Compound::Compound(const Compound& a){
  for(int i = 0; i < a.numElements; i++){
    elements.push_back(a.elements[i]);
  }
  numElements = a.numElements;
  name = a.name;
  compoundData = a.compoundData;
  amount = a.amount;
}

void Compound::getFormula(){
  if(doFileInput){
    fin >> compoundData.symbol;
  }else{
    cout << "Enter the compound formula: ";
    cin >> compoundData.symbol;
  }
}

void Compound::parseFormula(){
  elements.clear();
  stack<int> parenStack;
  for(int i = 0; i < compoundData.symbol.length(); i++){
    if(isUpperLetter(compoundData.symbol[i])){
      string key = "";
      key += compoundData.symbol[i];
      string number = "";
      int num;
      if(isLowerLetter(compoundData.symbol[i + 1])){
        key += compoundData.symbol[i + 1];
        i++;
      }
      while(isNumber(compoundData.symbol[i + 1])){
        number += compoundData.symbol[i + 1];
        i++;
      }
      num = stringToNum(number);
      Element tempElem(key, num);
      elements.push_back(tempElem);
      numElements++;
    }else if(isOpenParentheses(compoundData.symbol[i])){
      parenStack.push(numElements);
    }else if(isClosedParentheses(compoundData.symbol[i])){
      int start = parenStack.top();
      parenStack.pop();
      string number = "";
      int num;
      while(isNumber(compoundData.symbol[i + 1])){
        number += compoundData.symbol[i + 1];
        i++;
      }
      num = stringToNum(number);
      for(int i = start; i < numElements; i++){
        elements[i].amount.number *= num;
      }
    }
  }
}

void Compound::addElementMolarMasses(){
  for(int i = 0; i < numElements; i++){
    elements[i].addMolarMass();
  }
}

void Compound::addCompoundMolarMass(){
  if(!(cmpdList.find(compoundData.symbol) != cmpdList.end())){
    for(auto elem : elements){
      compoundData.molarMass += elem.elementData.molarMass * elem.amount.number;
    }
    cmpdList[compoundData.symbol] = compoundData.molarMass;
    cmpdChanged = true;
  }else{
    compoundData.molarMass = cmpdList[compoundData.symbol];
  }
}
