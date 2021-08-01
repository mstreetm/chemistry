#include <cmath>
#include <string>
#include <iostream>
#include <unordered_set>
#include "helpers.h"
#include "menu.h"

using namespace std;

unordered_set<int> multiplySet;

bool isNumber(char a){
  int ia = a;
  int diff = ia - '0';
  if((diff > 9) || (diff < 0)){
    return false;
  }
  return true;
}

bool isLowerLetter(char a){
  int ia = a;
  int diff = ia - 'a';
  if((diff >= 0) && (diff < 26)){
    return true;
  }
  return false;
}

bool isUpperLetter(char a){
  int ia = a;
  int diff = ia - 'A';
  if((diff >= 0) && (diff < 26)){
    return true;
  }
  return false;
}

bool isOpenParentheses(char a){
  if(a == '('){
    return true;
  }
  return false;
}

bool isClosedParentheses(char a){
  if(a == ')'){
    return true;
  }
  return false;
}

int stringToNum(std::string snum){
  if(snum == ""){
    return 1;
  }
  int nnum = 0;
  int len = snum.length();
  for(int i = 0; i < len; i++){
    int base = snum[i] - '0';
    nnum += base * pow(10, len - 1 - i);
  }
  return nnum;
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
