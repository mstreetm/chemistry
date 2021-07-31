#include <string>
#include <vector>

struct Compound{
  std::vector<Element> elements;
  int numElements;
  std::string name;
  ElementData compoundData;
  Amount amount;
  //will probably need to add more constructors later
  Compound();
  Compound(std::vector<Element> elems, int num);
  Compound(const Compound& a);
  //functions
  void getFormula();
  void parseFormula();
  void addElementMolarMasses();
  void addCompoundMolarMass();
};
