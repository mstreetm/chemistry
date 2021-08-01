#include "element.h"

#include <string>
#include <vector>

struct Compound{
  std::vector<Element> elements;
  int numElements;
  std::string name;
  ElementData compoundData;
  Amount amount;
  ElementData empiricalData;
  //will probably need to add more constructors later
  Compound();
  Compound(std::vector<Element> elems, int num);
  Compound(const Compound& a);
  //functions
  void getFormula();
  void parseFormula();
  void addElementMolarMasses();
  void addCompoundMolarMass(char a = 'm');
  void getElementAmounts(int numElem = -1);
  void elementsMassToMoles();
  void elementsMolesDivideBySmall();
  void elementsMolesMultiplyTillWhole();
  void addCompoundFormula(char a = 'm');
  void getCompoundMolarMass();
  void molecularFromEmpirical();
};
