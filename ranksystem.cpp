#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ranksystem.hpp"
#include "rankutils.hpp"

using namespace std;

//data structure for pulling rank.conf info from clan_detailedroster
struct gleanedData {
  string rankName;
  int maxKarma;
  int minKarma;
};

RankSystem::RankSystem(string filename)
  : RankUtils()
{ //default filename is rank.conf
  fstream rankConf;
  rankConf.open(filename.c_str(), fstream::in);

  if (!rankConf.is_open()) {
    //if rank.conf is not found, offer to make one, and call function if user okays it.
    string choice;
    bool acceptable=false; //was a valid yes/no response given?

    while (!acceptable) {
      cout << "No rank.conf found.  Would you like to generate one based on a clan_detailedroster.php (with only limited functionality supported)? [Y/n] ";
      cin >> choice;
      choice = to_lowercase(choice);

      if (choice == "" || choice == "yes" || choice == "y") {
	makeRankConf(filename);
	rankConf.open(filename.c_str(), fstream::in);
	acceptable = true;
      }
      else if (choice == "no" || choice == "n") {
	acceptable = true;
      }

      if (!acceptable) cout << "Invalid input." << endl;
    }
  }
}

void RankSystem::makeRankConf(string filename)
{
  //make a rank.conf if one doesn't exist.
  vector<gleanedData> ranksGleaned; //info that will be written to rank.conf
  vector <string> rankNames; //names of ranks
  gleanedData tempData;
  ofstream rankConf; //output file
  rankConf.open(filename.c_str());

  cout << "The program must process a valid detailed roster source page to construct a rank.conf.  Please enter the name of the file you would like to use." << endl;
  makeRankBook(""); //extract info from HTML.
  if (empty()) return; //failure to process.
  const vector <Data> & roster = getRankBook();

  //process the rank book. Might need re-doing.
  for (unsigned int i = 0; i < roster.size(); i++) {
    rankNames.push_back(roster[i].rank);
  }

  //remove duplicate rankNames... N^2 Might need redoing.
  for (unsigned int i = 0; i < rankNames.size(); i++) {
    for (unsigned int j = i+1; j < rankNames.size();) {
      if (rankNames[i] == rankNames[j]) rankNames.erase(rankNames.begin()+j);
      else j++;
    }
  }
}
