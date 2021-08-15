#include "element.h"
#include "menu.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

ElementData::ElementData(){
  //default constructor for ElementData, sets sym to not specified and mm to -1
  symbol = "Not Specified";
  molarMass = -1;
}

ElementData::ElementData(std::string s, float mm){
  //constructor foe elementData using sym and mm
  symbol = s;
  molarMass = mm;
}

ElementData::ElementData(std::string s){
  //constructor for elementData using sym, and not mm
  symbol = s;
  molarMass = -1;
}

ElementData::ElementData(const ElementData& a){
  //copy constructor for elementData
  symbol = a.symbol;
  molarMass = a.molarMass;
}

float Amount::NUMBER_PER_MOLE = 6.022e23;//avogadros #
float Amount::LITERS_PER_MOLE = 22.4;//at STP

Amount::Amount(){
  //default constructor for amount, sets everything to -1
  number = -1;
  moles = -1;
  liters = -1;
  grams = -1;
}

Amount::Amount(char s, int a){
  //constructor for amount, a indicates what value is provided
  //a is amount, m is moles, l is liters, and g is grams
  //sets as much as possible with the information provided
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
  //the same as the previous, butgiven a float
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
  //see above, but for doubles
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
  //copy constructor for amount
  number = a.number;
  moles = a.moles;
  liters = a.liters;
  grams = a.grams;
}

Element::Element(){
  //default constructor for Element, uses default constructors for members
  ElementData tempED;
  elementData = tempED;
  Amount tempA;
  amount = tempA;
}

Element::Element(ElementData e, Amount a){
  //constructor for element using provided data
  elementData = e;
  amount = a;
}

Element::Element(const Element& a){
  //copy constructor for Element
  elementData = a.elementData;
  amount = a.amount;
}

void Amount::setGrams(float mm){
  //sets the grams based on moles and provided mm, assumes moles is set
  if(grams == -1){
    grams = moles * mm;
  }
}

void Element::setGrams(){
  //sets the grams based on moles and molarMass, assumes both are set
  if(amount.grams == -1){
    amount.grams = amount.moles * elementData.molarMass;
  }
}

void Element::addMolarMass(){
  //adds the molar mass to elementData, gets from elemList or asks the user
  if(elemList.find(elementData.symbol) == elemList.end()){//not in elemList
    cout << "There is no molar mass for " << elementData.symbol << " in the system, please enter one: \n";
    cin >> elementData.molarMass;
    elemChanged = true;
    elemList[elementData.symbol] = elementData.molarMass;
  }
  elementData.molarMass = elemList[elementData.symbol];
}

Element::Element(std::string symbol, int num){
  //constructor for Element, sets symbol and amount
  ElementData tempED(symbol);
  elementData = tempED;
  Amount tempA('a', num);
  amount = tempA;
}

Element::Element(std::string symbol, float num){
  //constructor for Element, sets symbol and grams
  ElementData tempED(symbol);
  elementData = tempED;
  Amount tempA('g', num);
  amount = tempA;
}
