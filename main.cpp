#include "rank.hpp"
#include "ranksystem.hpp"
#include <string>
#include <iostream>
#include <iomanip>

void helpText() {
  cout << "Usage: ranker [OPTION]" << endl
       << "Process Kingdom of Loathing Clan Ranks." << endl << endl
       << "Mandatory arguments are mandatory for both long and short argument forms." << endl
       << "  -i, --input [FILENAME]         process specified file as the clan detailed roster." << endl
       << "  -h, --human-readable           human-readable output format" << endl
       << "  -sc, --search-by-criteria [CRITERIA]" << endl
       << "                                 Possible criteria choices:" << endl
       << "                                   rank" << endl
       << "                                   rank-line" << endl
       << "                                   playername" << endl
       << "                                   karma" << endl
       << "                                   karma-above" << endl
       << "                                   karma-below" << endl
       << "                                   karma-between" << endl;
}

void humanOutput(vector<PersonToRank> rankees)
{
  if (rankees.size() == 0) {
    cout << "Ranks are up-to-date." << endl; //will also print if doRanks() is not called prior to function call.
  }
  else {
    for (unsigned int i = 0; i < rankees.size(); i++) {
      cout << rankees[i].person << " (" << rankees[i].karma 
	   << " karma) Ranked: " << rankees[i].currentRank
	   << " Switch to: " << rankees[i].destRank << endl;
    }
  }
}

void defaultOutput(vector <PersonToRank> rankees)
{
  if (rankees.size() == 0) {
    cout << "Ranks are up-to-date." << endl;
  }
  else {
    for (unsigned int i = 0; i < rankees.size(); i++) {
      cout << rankees[i].person << " " << rankees[i].karma
	   << " " << rankees[i].currentAbbr << "->" 
	   << rankees[i].destAbbr << endl;
    }
  }
}

int main(int argc, char* argv[])
{
  bool options [3] = {false, false, false}; //option flags. {human-readable, search, search by criteria}
  string filename = "", criteria = ""; //search criteria
  RankSystem ranksystem;

  if (!ranksystem.sysCheck()) {
    cout << "Failed to read the rank system from rank.conf.\n";
    return 0;
  }

  //Command line argument processing.
  for (int argument = 1; argument < argc; argument++) {
    if ((string) argv[argument] == "-i" 
	|| (string) argv[argument] == "--input") {
      if ((argument+1)<argc) {
	filename = argv[++argument];
      }
      else {helpText(); return 0;}
    }
    else if ((string) argv[argument] == "-h" 
	     || (string) argv[argument] == "--human-readable") {
      options[0] = true;
    }
    else if ((string) argv[argument] == "-s"
	     || (string) argv[argument] == "search") {
      options[1] = true;
    }
    else if ((string) argv[argument] == "-sc" 
	     || (string) argv[argument] == "--search-by-criteria") {
      if ((argument+1)<argc) {
	criteria = argv[++argument];
	options[2] = true;
      }
      else {helpText(); return 0;}
    }
    else {
      helpText();
      return 0;
    }
  }
  Rank rank(options, filename);

  rank.doRanks(ranksystem.getRankInfo());

  if (options[0] && !options[1] && !options[2]) humanOutput(rank.getRankees());
  if (!options[0] && !options[1] && !options[2]) defaultOutput(rank.getRankees());

  return 0;
}
