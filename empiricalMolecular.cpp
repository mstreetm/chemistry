#include "element.h"
#include "menu.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

//uncomment to get input from the file
#define cin fin
// std::ifstream fin ("C:\\Users\\moniq\\Desktop\\input.txt");

using namespace std;

const float MAX_DIFFERENCE = 0.05;
const int numRV = 9;
const float roundingValues[numRV] = { 0,1,0.3334,0.6667,0.5,0.2,0.4,0.6,0.8 };
const float multiplyTo[numRV] = { 1,1,3,3,2,5,5,5,5 };

struct ELement {
	string symbol;
	float molarMass;

	//used for MM, found in empFormula
	int numOfAtoms;

	//needed for empFormula
	float amount;//user-given
	float moles;
	float dbSmall;
	float rounded;

	//constructor
	ELement(string sym)
	{
		symbol = sym;
	}
};

// void getElementMasses();
string getEmperical();
float rounder(float num);
bool isValue(float num, float value);
void updateFile();
float getMM();

// map<string, float> elemList;
bool mapChanged = false;
unordered_set<int> multiplySet;
vector<ELement> ELements;

void runEmpiricalMolecular(){
	getElementMasses();
	cout << getEmperical();
	updateFile();
}

// void getElementMasses(){
//   //gets the element masses from ELements.txt and puts them into the map elemList
// 	ifstream ein("ELements.txt");
// 	string key;
// 	float value;
// 	ein >> key;
// 	while(!ein.eof())
// 	{
// 		ein >> value;
// 		elemList[key] = value;
// 		ein >> key;
// 	}
// }

string getEmperical(){
  //gets the empirical formula for a compound by prompting the user
	//element input
	int numELements;
	cout << "How many ELements are there in the compound: ";
	cin >> numELements;
	string elem;
	for(int i = 0; i < numELements; i++){
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
		cin >> elem;
		ELements.push_back(elem);
		if(elemList.find(elem) == elemList.end()){
			cout << "There is no molar mass for " << elem << " in the system, please enter one: ";
			cin >> elemList[elem];
			mapChanged = true;
		}
		ELements[i].molarMass = elemList[elem];
		cout << "How much " << elem << " is there: ";
		cin >> ELements[i].amount;
	}

	//Mass to moles
	for(int i = 0; i < numELements; i++){
		ELements[i].moles = ELements[i].amount / elemList[ELements[i].symbol];
	}

	//DIVIDE BY SMALL
	//find small
	float small = ELements[0].moles;
	for(int i = 1; i < numELements; i++){
		if(ELements[i].moles < small){
			small = ELements[i].moles;
		}
	}

	//do the division
	for(int i = 0; i < numELements; i++){
		ELements[i].dbSmall = ELements[i].moles / small;
	}

	//MULTIPLY 'TILL WHOLE
	for(int i = 0; i < numELements; i++){
		ELements[i].rounded = rounder(ELements[i].dbSmall);
	}
	int multiplyValue = 1;
	for(auto i = multiplySet.begin(); i != multiplySet.end(); i++){
		multiplyValue *= *i;
	}
	for(int i = 0; i < numELements; i++){
		ELements[i].numOfAtoms = static_cast<int>(ELements[i].rounded * multiplyValue);
	}

	//determine output
	string empFormula = "";
	for(int i = 0; i < numELements; i++){
		empFormula += ELements[i].symbol;
		if(ELements[i].numOfAtoms != 1){
			empFormula += to_string(ELements[i].numOfAtoms);
		}
	}

	//ask if molecular formula is wanted
	//cout << "Do you want the Molecular formula? Enter 1 for yes or 0 for no: ";
	bool doMolFormula;
	//cin >> doMolFormula;
	//cout << doMolFormula;

	return empFormula;
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

void updateFile(){
	if(mapChanged){
		ofstream eout("ELements.txt");
		for(auto i = elemList.begin(); i != elemList.end(); i++){
			eout << i->first << " " << i->second << "\n";
		}
	}
}
