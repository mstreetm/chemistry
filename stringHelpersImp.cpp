#include <cmath>
#include <string>
#include "stringHelpers.h"

using namespace std;

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
