#include "element.h"
#include "menu.h"

// #include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

ifstream fin("C:/Users/moniq/Desktop/input.txt");

std::map<std::string, float> elemList;

void getElementMasses(){
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
