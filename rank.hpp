#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#ifndef RANK_H
#define RANK_H

using namespace std;

struct Data {
  string person;
  string playerClass;
  string rank;
  int karma;
};

enum watchFor {
  PERSON,
  CLASS, 
  RANK, 
  KARMA
};

class Rank
{
  public:
    Rank(bool options[], string filename, string criteria = "");

    bool empty();
    const vector<Data> getRankBook();
  private:
    vector<Data> rankBook;
    inline bool is_int(string input);
    inline int to_int(string input);
};

inline bool Rank::is_int(string input) {
  for (unsigned int i = 0; i < input.length(); i++) {
    if (!isdigit(input[i])) return false;
  }
  return true;
}

inline int Rank::to_int(string input) {
  int answer = 0, tempNum = 0;
  for (unsigned int i = 0; i < input.length(); i++) {
    if (input[i] == '0') tempNum = 0;
    else if (input[i] == '1') tempNum = 1;
    else if (input[i] == '2') tempNum = 2;
    else if (input[i] == '3') tempNum = 3;
    else if (input[i] == '4') tempNum = 4;
    else if (input[i] == '5') tempNum = 5;
    else if (input[i] == '6') tempNum = 6;
    else if (input[i] == '7') tempNum = 7;
    else if (input[i] == '8') tempNum = 8;
    else if (input[i] == '9') tempNum = 9;
    answer += (pow(10, (input.length()-1-i))*tempNum);
  }
  return answer;
}

#endif
