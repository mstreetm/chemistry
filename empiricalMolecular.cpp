#include "compound.h"
#include "menu.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

#define cin fin

using namespace std;

const float MAX_DIFFERENCE = 0.05;
const int numRV = 9;
const float roundingValues[numRV] = { 0,1,0.3334,0.6667,0.5,0.2,0.4,0.6,0.8 };
const float multiplyTo[numRV] = { 1,1,3,3,2,5,5,5,5 };

// struct ELement {
// 	string symbol;
// 	float molarMass;
//
// 	//used for MM, found in empFormula
// 	int numOfAtoms;
//
// 	//needed for empFormula
// 	float amount;//user-given
// 	float moles;
// 	float dbSmall;
// 	float rounded;
//
// 	//constructor
// 	ELement(string sym)
// 	{
// 		symbol = sym;
// 	}
// };

// void getElementMasses();
string getEmperical();
float rounder(float num);
bool isValue(float num, float value);

// map<string, float> elemList;
unordered_set<int> multiplySet;
// vector<ELement> ELements;

Compound compound;

void runEmpiricalMolecular(){
	getElementMolarMasses();
	cout << "\n" << getEmperical();
  for(auto elem : compound.elements){
    cout << elem.elementData.symbol << "\n";
  }
	updateFiles();
}

string getEmperical(){
  //gets the empirical formula for a compound by prompting the user
	//element input\
	cout << "How many ELements are there in the compound: ";
	cin >> compound.numElements;
	for(int i = 0; i < compound.numElements; i++){
		cout << "Enter the ";
		switch (i + 1){
		case 1:
			cout << "1st ";
			break;
		case 2:
			cout << "2nd ";
			break;
		case 3:
			cout << "3rd ";
			break;
		default:
			cout << i + 1 << "th ";
			break;
		}
		cout << "element symbol: ";
    string elem;
		cin >> elem;
		cout << "How much " << elem << " is there: ";
    float amt;
    cin >> amt;
    Element tempE(elem, amt);
    compound.elements.push_back(tempE);
	}
  compound.addElementMolarMasses();

	//Mass to moles
	for(int i = 0; i < compound.numElements; i++){
		compound.elements[i].amount.moles = compound.elements[i].amount.grams / elemList[compound.elements[i].elementData.symbol];
	}

	//DIVIDE BY SMALL
	//find small
	float small = compound.elements[0].amount.moles;
	for(int i = 1; i < compound.numElements; i++){
		if(compound.elements[i].amount.moles < small){
			small = compound.elements[i].amount.moles;
		}
	}

	//do the division
	for(int i = 0; i < compound.numElements; i++){
		compound.elements[i].amount.moles = compound.elements[i].amount.moles / small;
	}

	//MULTIPLY 'TILL WHOLE
	for(int i = 0; i < compound.numElements; i++){
		compound.elements[i].amount.moles = rounder(compound.elements[i].amount.moles);
	}
	int multiplyValue = 1;
	for(auto i = multiplySet.begin(); i != multiplySet.end(); i++){
		multiplyValue *= *i;
	}
	for(int i = 0; i < compound.numElements; i++){
		compound.elements[i].amount.number = static_cast<int>(compound.elements[i].amount.moles * multiplyValue);
	}

	//determine output
	for(int i = 0; i < compound.numElements; i++){
		compound.compoundData.symbol += compound.elements[i].elementData.symbol;
		if(compound.elements[i].amount.number != 1){
			compound.compoundData.symbol += to_string(static_cast<int>(compound.elements[i].amount.number));
		}
	}

	//ask if molecular formula is wanted
	//cout << "Do you want the Molecular formula? Enter 1 for yes or 0 for no: ";
	bool doMolFormula;
	//cin >> doMolFormula;
	//cout << doMolFormula;

	return compound.compoundData.symbol;
}

float rounder(float num){
	int base = num - abs(num - static_cast<int>(num));
	num -= base;
	for(int i = 0; i < numRV; i++){
		if(isValue(num, roundingValues[i])){
			multiplySet.insert(multiplyTo[i]);
			return(base + roundingValues[i]);
		}
	}
	cout << "What should " << num << " be rounded to: ";
	float rounded;
	cin >> rounded;
	return (base + rounder(rounded));
}

bool isValue(float num, float value){
	if((value - MAX_DIFFERENCE < num) && (value + MAX_DIFFERENCE > num)){
		return true;
	}
	return false;
}
