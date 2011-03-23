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
    RankUtils(string filename);
    bool empty() const;
    const vector <Data> & getRankBook() const;
  protected:
    inline bool is_int(string input) const;
    inline int to_int(string input);
  private:
    vector<Data> rankBook; //main data structure  
};

#endif
