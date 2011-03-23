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

#endif
