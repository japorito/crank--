#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rankutils.hpp"

#ifndef RANKSYSTEM_HPP
#define RANKSYSTEM_HPP

using namespace std;

class RankSystem
  : public RankUtils
{
 public:
  RankSystem(string filename="rank.conf");
  void makeRankConf(string filename); //make a limited-functionality rank.conf
  bool sysCheck() const;
  const Ranks & operator[](int index) const;
  int numOfRanks() const;
  const vector<Ranks> & getRankInfo() const;

 private:
  vector <Ranks> rankInfo; //holds the important rank.conf info
};

#endif
