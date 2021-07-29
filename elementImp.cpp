#include "element.h"
#include <string>

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

float Amount::ATOMS_PER_MOLE = 6.022e23;
float Amount::LITERS_PER_MOLE = 22.4;

Amount::Amount(){
  atoms = -1;
  moles = -1;
  liters = -1;
  grams = -1;
}

Amount::Amount(char s, int a){
  switch(s){
    case 'a':
      atoms = a;
      moles = a/ATOMS_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      atoms = a*ATOMS_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      atoms = moles*ATOMS_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      atoms = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(char s, float a){
  switch(s){
    case 'a':
      atoms = a;
      moles = a/ATOMS_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      atoms = a*ATOMS_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      atoms = moles*ATOMS_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      atoms = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(char s, double a){
  switch(s){
    case 'a':
      atoms = a;
      moles = a/ATOMS_PER_MOLE;
      liters = moles*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'm':
      atoms = a*ATOMS_PER_MOLE;
      moles = a;
      liters = a*LITERS_PER_MOLE;
      grams = -1;
      break;
    case 'l':
      moles = a/LITERS_PER_MOLE;
      atoms = moles*ATOMS_PER_MOLE;
      liters = a;
      grams = -1;
      break;
    case 'g':
      atoms = -1;
      moles = -1;
      liters = -1;
      grams = a;
      break;
  }
}

Amount::Amount(const Amount& a){
  atoms = a.atoms;
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