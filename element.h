#include <string>

struct ElementData{
  std::string symbol;
  float molarMass;
  ElementData();
  ElementData(std::string s, float mm);
  ElementData(const ElementData& a);
};

struct Amount{
  static float ATOMS_PER_MOLE;
  static float LITERS_PER_MOLE;
  float atoms;
  float moles;
  float liters;
  float grams;
  Amount();
  Amount(char s, int a);
  Amount(char s, double a);
  Amount(char s, float a);
  Amount(const Amount& a);
};

struct GroupOf{
  ElementData elementData;
  Amount amount;
  GroupOf();
  GroupOf(ElementData e, Amount a);
  GroupOf(const GroupOf& a);
};
