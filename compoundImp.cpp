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
  //default constructor, sets blank objects or 0/"Not Specified"
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
  //constructor for elements(takes vector and length)
  //sets those, then everything else blank
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
  //copy constructor
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
  //asks the user for the compound formula
  if(doFileInput){
    fin >> compoundData.symbol;
  }else{
    cout << "Enter the compound formula: ";
    cin >> compoundData.symbol;
  }
}

void Compound::parseFormula(){
  //parses the compound formula(assumes it exists)
  if(compoundData.symbol == "Not Specified"){//quits if compoundData is not set
    return;
  }
  elements.clear();
  stack<int> parenStack;
  for(int i = 0; i < compoundData.symbol.length(); i++){//for each character in compoundData.symbol(skips some)
    if(isUpperLetter(compoundData.symbol[i])){//checks for an uppercase letter(start of an element)
      string key = "";
      key += compoundData.symbol[i];
      string number = "";
      int num;
      if(isLowerLetter(compoundData.symbol[i + 1])){//checks for a second letter in the element symbol
        key += compoundData.symbol[i + 1];
        i++;
      }
      while(isNumber(compoundData.symbol[i + 1])){
        //gets the number of atoms of the element(of no number, eventually gets set to 1)
        number += compoundData.symbol[i + 1];
        i++;
      }
      //number handeling
      num = stringToNum(number);
      //builds the element and adds it to the elements vector
      Element tempElem(key, num);
      elements.push_back(tempElem);
      numElements++;
    }else if(isOpenParentheses(compoundData.symbol[i])){//checks for an open parenthesis, adds position(in elements) to a stack
      parenStack.push(numElements);
    }else if(isClosedParentheses(compoundData.symbol[i])){//checks for a closed parenthesis, then a number, then multiplies the number of a bunch of atoms
      //finds previous parenthesis location
      int start = parenStack.top();
      parenStack.pop();
      //gets the number(assumes 1 if no number)
      string number = "";
      int num;
      while(isNumber(compoundData.symbol[i + 1])){
        number += compoundData.symbol[i + 1];
        i++;
      }
      num = stringToNum(number);
      //multiplies element numbers
      for(int i = start; i < numElements; i++){
        elements[i].amount.number *= num;
      }
    }
  }
}

void Compound::addElementMolarMasses(){
  //puts in the molar mass of the elements
  for(int i = 0; i < numElements; i++){
    elements[i].addMolarMass();
  }
}

void Compound::addCompoundMolarMass(char a){
  //gets the molar mass of a compound
  //a is the mode, m is molecular, e is empirical
  float mm = 0;
  string sym;
  switch(a){//gets the correct element symbol
    case 'm':
      sym = compoundData.symbol;
      break;
    case 'e':
      sym = empiricalData.symbol;
      break;
  }
  if(!(cmpdList.find(sym) != cmpdList.end())){//if the mass is not on the compoundList
    for(auto elem : elements){
      mm += elem.elementData.molarMass * elem.amount.number;
    }
    cmpdList[sym] = mm;
    cmpdChanged = true;
  }else{//if it is
    mm = cmpdList[sym];
  }
  switch(a){//sets it to the correct variable
    case 'm':
      compoundData.molarMass = mm;
      break;
    case 'e':
      empiricalData.molarMass = mm;
      break;
  }
}

void Compound::getElementAmounts(int numElem){
  //gets element names and amounts from the user
  if(doFileInput){//for file input
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
  }else{//for console input
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
  //for each element, turns mass into moles, assumes elements have molar masses
  for(int i = 0; i < numElements; i++){
		elements[i].amount.moles = elements[i].amount.grams / elemList[elements[i].elementData.symbol];
	}
}

void Compound::elementsMolesDivideBySmall(){
  //divides the moles of each element by the smallest number of moles in the compound
  float small = elements[0].amount.moles;
	for(int i = 1; i < numElements; i++){//find smallest number of moles
		if(elements[i].amount.moles < small){
			small = elements[i].amount.moles;
		}
	}
	for(int i = 0; i < numElements; i++){//the dividing
		elements[i].amount.moles = elements[i].amount.moles / small;
	}
}

void Compound::elementsMolesMultiplyTillWhole(){
  //multiplies the number of moles util it is a whole number(for all elements) and stores it in amount.number
  //assumes multiplySet is populated
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
  //gets the compound formula from the elements vector
  //assumes amount.number is both set, and represents the number of atoms of that type PER MOLECULE, not total
  //a selects empirical(e) or molecular(m), and defaults to molecular
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
  //gets the (molecular) molar mass of the compound from the user
  if(!doFileInput){
    cout << "Enter the molar mass of the compound: ";
    cin >> compoundData.molarMass;
  }else{
    fin >> compoundData.molarMass;
  }
}

void Compound::molecularFromEmpirical(){
  //gets the molecular formula for the compound from the empirical formula and the molecular molar mass
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
