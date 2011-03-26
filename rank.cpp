#include "rank.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "rankutils.hpp"

using namespace std;

Rank::Rank(bool options[], string filename, string criteria)
  : RankUtils(filename)
{
  //options bool array contains option flags. {human-readable, search, search-by-criteria}

  //temporary output
  /*  const vector<Data> & theRanks = getRankBook();
  for (unsigned int i=0; i < theRanks.size(); i++) {
    cout << "Person: " << theRanks[i].person << " Class: " << theRanks[i].playerClass << " Rank: " << theRanks[i].rank << " Karma: " << theRanks[i].karma << endl;
    }*/
}
