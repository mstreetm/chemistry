#include "element.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
  ElementData a("C", 12.01);
  Amount b('a', 7e23);
  GroupOf c(a, b);
  cout << a.symbol << " " << a.molarMass << "\n";
  cout << b.atoms << " " << b.moles << " " << b.liters << " " << b.grams << "\n";
  cout << c.elementData.symbol << " " << c.amount.atoms << "\n";
  return 0;
}
