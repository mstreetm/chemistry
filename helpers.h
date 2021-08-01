#include <unordered_set>

const float MAX_DIFFERENCE = 0.05;
const int numRV = 9;
const float roundingValues[numRV] = { 0,1,0.3334,0.6667,0.5,0.2,0.4,0.6,0.8 };
const float multiplyTo[numRV] = { 1,1,3,3,2,5,5,5,5 };

extern std::unordered_set<int> multiplySet;

bool isUpperLetter(char a);
bool isLowerLetter(char a);
bool isNumber(char a);
bool isOpenParentheses(char a);
bool isClosedParentheses(char a);
int stringToNum(std::string snum);
float rounder(float num);
bool isValue(float num, float value);
