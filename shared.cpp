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
  if(elemChanged){
    ofstream eout("elements.txt");
    for(auto i = elemList.begin(); i != elemList.end(); i++){
      eout << i->first << " " << i->second << "\n";
    }
  }
  if(cmpdChanged){
    ofstream cmout("compounds.txt");
    for(auto i = cmpdList.begin(); i != cmpdList.end(); i++){
      cmout << i->first << " " << i->second << "\n";
    }
  }
}
