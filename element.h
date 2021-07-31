#include <string>
#include <vector>

struct ElementData{
  std::string symbol;
  float molarMass;
  ElementData();
  ElementData(std::string s, float mm);
  ElementData(std::string s);
  ElementData(const ElementData& a);
};

struct Amount{
  static float NUMBER_PER_MOLE;
  static float LITERS_PER_MOLE;
  float number;//could be atoms, molecules, foumula units
  float moles;
  float liters;
  float grams;
  Amount();
  Amount(char s, int a);
  Amount(char s, double a);
  Amount(char s, float a);
  Amount(const Amount& a);
  void setGrams(float mm);
};

struct Element{
  ElementData elementData;
  Amount amount;
  Element();
  Element(std::string symbol, int num);
  Element(std::string symbol, float num);
  Element(ElementData e, Amount a);
  Element(const Element& a);
  void setGrams();
  void addMolarMass();
};
