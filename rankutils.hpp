#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#ifndef RANKUTILS_HPP
#define RANKUTILS_HPP

struct Data {
  //main Data struct
  string person;
  string playerClass;
  string rank;
  int karma;
};

enum watchFor {
  //enum used to clarify data extraction in constructor
  PERSON,
  CLASS, 
  RANK, 
  KARMA
};

class RankUtils
{
  //Utility functions used for both main rank classes.
  public:
    RankUtils(); //does not instantiate rankBook
    RankUtils(string filename);

    void makeRankBook(string filename); //utility function to instantiate rankBook
    bool empty() const; //returns true if rankBook is empty
    const vector <Data> & getRankBook() const;

  protected:
    inline bool is_int(string input) const;
    inline int to_int(string input);
    inline string to_lowercase(string input);

  private:
    vector<Data> rankBook; //main data structure  
};

//This doesn't link correctly unless it is in the header, for whatever reason.
inline string RankUtils::to_lowercase(string input)
{
  //returns an all lower-case string.
  for (unsigned int i=0; i<input.length(); i++) {
    input[i] = (char) tolower(input[i]);
  }

  return input;
}

inline bool RankUtils::is_int(string input) const
{
  for (unsigned int i = 0; i < input.length(); i++) {
    if (!isdigit(input[i])) return false;
  }
  return true;
}

inline int RankUtils::to_int(string input) {
  //converts integer string to int
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
