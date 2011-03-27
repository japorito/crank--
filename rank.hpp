#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "rankutils.hpp"

#ifndef RANK_H
#define RANK_H

using namespace std;

struct PersonToRank {
  string person;
  string rankLine;
  string currentRank;
  string currentAbbr;
  string destRank;
  string destAbbr;
  int karma;
};

class Rank
  : public RankUtils
{
  public:
    Rank(bool options[], string filename, string criteria = "");
    void doRanks(const vector<Ranks> ranksystem);

  private:
    vector<PersonToRank> peopleToRank;
};

#endif
