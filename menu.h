//The header file for all mini programs, hopfully this will work
#include <map>
#include <string>
#include <iostream>

//Current contents:
//compoundMolarMass
//runEmpiricalMolecular

void runCompoundMolarMass();

void runEmpiricalMolecular();

//shared functions

extern std::map<std::string, float> elemList;
extern std::ifstream fin;
void getElementMasses();
