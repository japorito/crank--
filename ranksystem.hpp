#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rankutils.hpp"

#ifndef RANK_HPP
#define RANK_HPP

using namespace std;

//struct for holding the information about the ranksystem
struct Ranks {
  string rank;
  string abbreviation;
  int minKarma;
  int maxKarma;
  int minToReturn;
  int maxToReturn;
  string rankLine;
};

class RankSystem
  : public RankUtils
{
 public:
  RankSystem(string filename="rank.conf");
  void makeRankConf(string filename); //make a limited-functionality rank.conf
 private:
  vector <Ranks> rankInfo; //holds the important rank.conf info
};

#endif
