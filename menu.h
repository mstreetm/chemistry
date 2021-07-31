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
extern std::map<std::string, float> cmpdList;
extern std::ifstream fin;
extern bool doFileInput;
extern bool elemChanged;
extern bool cmpdChanged;
void getElementMolarMasses();
void getCompoundMolarMasses();
void updateFiles();
