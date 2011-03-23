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

class Rank
  : public RankUtils
{
  public:
    Rank(bool options[], string filename, string criteria = "");
};

#endif
