#include <string>
#include <vector>
#include <iostream>
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
    void doRanks(const vector<Ranks> ranksystem); //process ranks to find people who need changed.  Stored in peopleToRank.
    const vector <PersonToRank> & getRankees() const; //get reference to peopleToRank.
    bool checkRankees() const {return (peopleToRank.size() != 0);}

  private:
    vector<PersonToRank> peopleToRank;
};

#endif
