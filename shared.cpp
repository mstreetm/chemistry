#include "element.h"
#include "menu.h"

// #include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

ifstream fin("C:/Users/moniq/Desktop/input.txt");

std::map<std::string, float> elemList;
std::map<std::string, float> cmpdList;

bool doFileInput = false;
bool elemChanged = false;
bool cmpdChanged = false;

void getElementMolarMasses(){
  //gets the element masses from elements.txt and puts them into the map elemList
  elemList.clear();
  ifstream ein("elements.txt");
  string key;
  float value;
  ein >> key;
  while(!ein.eof()){
    ein >> value;
    elemList[key] = value;
    ein >> key;
  }
}

void getCompoundMolarMasses(){
  //gets the compound masses from compounds.txt and puts them into the map cmpdList
  cmpdList.clear();
  ifstream cmin("compounds.txt");
  string key;
  float value;
  cmin >> key;
  while(!cmin.eof()){
    cmin >> value;
    cmpdList[key] = value;
    cmin >> key;
  }
}

void updateFiles(){
  //updates the files(elements.txt and compounds.txt) at the end of the program
  if(elemChanged){//updates elements.txt
    ofstream eout("elements.txt");
    for(auto i = elemList.begin(); i != elemList.end(); i++){
      eout << i->first << " " << i->second << "\n";
    }
  }
  if(cmpdChanged){//updates compounds.txt
    ofstream cmout("compounds.txt");
    for(auto i = cmpdList.begin(); i != cmpdList.end(); i++){
      cmout << i->first << " " << i->second << "\n";
    }
  }
}
