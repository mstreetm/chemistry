#include "element.h"
#include <string>
#include <vector>

ElementData::ElementData(){
  symbol = "Not Specified";
  molarMass = -1;
}

ElementData::ElementData(std::string s, float mm){
  symbol = s;
  molarMass = mm;
}

ElementData::ElementData(const ElementData& a){
  symbol = a.symbol;
  molarMass = a.molarMass;
}

float Amount::NUMBER_PER_MOLE = 6.022e23;
float Amount::LITERS_PER_MOLE = 22.4;

Amount::Amount(){
  number = -1;
  moles = -1;
  liters = -1;
  grams = -1;
}

Amount::Amount(char s, int a){
  switch(s){
    case 'a':
      number = a;
      moles = a/NUMBER_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      number = a*NUMBER_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      number = moles*NUMBER_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      number = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(char s, float a){
  switch(s){
    case 'a':
      number = a;
      moles = a/NUMBER_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      number = a*NUMBER_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      number = moles*NUMBER_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      number = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(char s, double a){
  switch(s){
    case 'a':
      number = a;
      moles = a/NUMBER_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      number = a*NUMBER_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      number = moles*NUMBER_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      number = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(const Amount& a){
  number = a.number;
  moles = a.moles;
  liters = a.liters;
  grams = a.grams;
}

GroupOf::GroupOf(){
  ElementData tempED;
  elementData = tempED;
  Amount tempA;
  amount = tempA;
}

GroupOf::GroupOf(ElementData e, Amount a){
  elementData = e;
  amount = a;
}

GroupOf::GroupOf(const GroupOf& a){
  elementData = a.elementData;
  amount = a.amount;
}

void Amount::setGrams(float mm){
  if(grams == -1){
    grams = moles * mm;
  }
}

void GroupOf::setGrams(){
  if(amount.grams == -1){
    amount.grams = amount.moles * elementData.molarMass;
  }
}

Compound::Compound(){
  //no init on elements
  numElements = -1;
  name = "Not Specified";
  ElementData tempCD;
  compoundData = tempCD;
  Amount tempA;
  amount = tempA;
}

Compound::Compound(std::vector<GroupOf> elems, int num){
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
