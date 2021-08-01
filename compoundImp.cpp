#include "compound.h"
#include "menu.h"
#include "helpers.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

Compound::Compound(){
  //no init on elements
  numElements = 0;
  name = "Not Specified";
  ElementData tempCD;
  compoundData = tempCD;
  Amount tempA;
  amount = tempA;
  ElementData tempED;
  empiricalData = tempED;
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
  ElementData tempED;
  empiricalData = tempED;
}

Compound::Compound(const Compound& a){
  for(int i = 0; i < a.numElements; i++){
    elements.push_back(a.elements[i]);
  }
  numElements = a.numElements;
  name = a.name;
  compoundData = a.compoundData;
  amount = a.amount;
  empiricalData = a.empiricalData;
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

void Compound::addCompoundMolarMass(char a){
  float mm = 0;
  string sym;
  switch(a){
    case 'm':
      sym = compoundData.symbol;
      break;
    case 'e':
      sym = empiricalData.symbol;
      break;
  }
  if(!(cmpdList.find(sym) != cmpdList.end())){
    for(auto elem : elements){
      mm += elem.elementData.molarMass * elem.amount.number;
    }
    cmpdList[sym] = mm;
    cmpdChanged = true;
  }else{
    mm = cmpdList[sym];
  }
  switch(a){
    case 'm':
      compoundData.molarMass = mm;
      break;
    case 'e':
      empiricalData.molarMass = mm;
      break;
  }
}

void Compound::getElementAmounts(int numElem){
  if(doFileInput){
    if(numElem != -1){
      numElements = numElem;
    }else{
      fin >> numElements;
    }
    for(int i = 0; i < numElements; i++){
      string elem;
  		fin >> elem;
      float amt;
      fin >> amt;
      Element tempE(elem, amt);
      elements.push_back(tempE);
    }
  }else{
    cout << "How many elements are there in the compound: ";
  	cin >> numElements;
  	for(int i = 0; i < numElements; i++){
  		cout << "Enter the ";
  		switch (i + 1){
  		case 1:
  			cout << "1st ";
  			break;
  		case 2:
  			cout << "2nd ";
  			break;
  		case 3:
  			cout << "3rd ";
  			break;
  		default:
  			cout << i + 1 << "th ";
  			break;
  		}
  		cout << "element symbol: ";
      string elem;
  		cin >> elem;
  		cout << "How much " << elem << " is there: ";
      float amt;
      cin >> amt;
      Element tempE(elem, amt);
      elements.push_back(tempE);
  	}
  }
}

void Compound::elementsMassToMoles(){
  for(int i = 0; i < numElements; i++){
		elements[i].amount.moles = elements[i].amount.grams / elemList[elements[i].elementData.symbol];
	}
}

void Compound::elementsMolesDivideBySmall(){
  float small = elements[0].amount.moles;
	for(int i = 1; i < numElements; i++){
		if(elements[i].amount.moles < small){
			small = elements[i].amount.moles;
		}
	}
	for(int i = 0; i < numElements; i++){
		elements[i].amount.moles = elements[i].amount.moles / small;
	}
}

void Compound::elementsMolesMultiplyTillWhole(){
  for(int i = 0; i < numElements; i++){
		elements[i].amount.moles = rounder(elements[i].amount.moles);
	}
	int multiplyValue = 1;
	for(auto i = multiplySet.begin(); i != multiplySet.end(); i++){
		multiplyValue *= *i;
	}
	for(int i = 0; i < numElements; i++){
		elements[i].amount.number = static_cast<int>(elements[i].amount.moles * multiplyValue);
	}
}

void Compound::addCompoundFormula(char a){
  string formula = "";
  for(int i = 0; i < numElements; i++){
		formula += elements[i].elementData.symbol;
		if(elements[i].amount.number != 1){
			formula += to_string(static_cast<int>(elements[i].amount.number));
		}
	}
  switch(a){
    case 'm':
      compoundData.symbol = formula;
      break;
    case 'e':
      empiricalData.symbol = formula;
      break;
  }
}

void Compound::getCompoundMolarMass(){
  if(!doFileInput){
    cout << "Enter the molar mass of the compound: ";
    cin >> compoundData.molarMass;
  }else{
    fin >> compoundData.molarMass;
  }
}

void Compound::molecularFromEmpirical(){
  if(isValue(compoundData.molarMass, empiricalData.molarMass)){
    compoundData.symbol = empiricalData.symbol;
  }else{
    int multiplyBy = round(compoundData.molarMass/empiricalData.molarMass);
    for(auto elem : elements){
      elem.amount.number *= multiplyBy;
    }
    addCompoundFormula();
  }
}
