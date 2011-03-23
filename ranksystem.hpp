#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rank.hpp"

using namespace std;

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
{
 public:
  RankSystem(string filename="rank.conf");
  void makeRank(string filename);
 private:
  vector <Ranks> rankInfo;
  inline string to_lowercase(string input);
};

inline string RankSystem::to_lowercase(string input) {
  for (unsigned int i=0; i<input.length(); i++) {
    input[i] = (char) tolower(input[i]);
  }
  return input;
}
