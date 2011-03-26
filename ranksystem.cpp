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
  string abbreviation;
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
      cout << "No rank.conf found.  Would you like to generate one based on a clan_detailedroster.php (with only limited functionality supported)? [y/n] ";
      cin >> choice;
      choice = to_lowercase(choice);

      if (choice == "yes" || choice == "y") {
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

  tempData.maxKarma = -1; //set to original state
  tempData.minKarma = -1;

  for (unsigned int i = 0; i < rankNames.size(); i++) {
    tempData.rankName = rankNames[i];
    tempData.abbreviation = rankNames[i][0];
    for (unsigned int k = 1; k < rankNames[i].length(); k++) {
      if (rankNames[i][k] == ' ') tempData.abbreviation += rankNames[i][k+1];
    }
    //for each rank name, get the max and min karma held by members of that rank
    for (unsigned int j = 0; j < roster.size(); j++) {
      if (rankNames[i] == roster[j].rank) {
	if (tempData.maxKarma < roster[j].karma
	    || tempData.maxKarma == -1) {
	  //if in original state or needs changed
	  tempData.maxKarma = roster[j].karma + (100 - roster[j].karma % 100);
	  //floor to nearest 100
	}
	if (tempData.minKarma > roster[j].karma
		 || tempData.minKarma == -1) {
	  //same
	  tempData.minKarma = roster[j].karma - (roster[j].karma % 100);
	  //ceiling to nearest 100
	}
      }
    }

    ranksGleaned.push_back(tempData); // add to main gleaned data vector.
    tempData.maxKarma = -1; //set these back to original state.
    tempData.minKarma = -1;
  }

  for (unsigned int i = 0; i < ranksGleaned.size(); i++) {
    //output gleaned data to rank.conf
    tempData = ranksGleaned[i];
    rankConf << "rank=\"" << tempData.rankName 
	     << "\" abbreviation=\"" << tempData.abbreviation 
	     << "\" rank_lower_bound=\"" << tempData.minKarma 
	     << "\" rank_upper_bound=\""  << tempData.maxKarma 
	     << "\" change_if_below=\""<< tempData.minKarma 
	     << "\" change_if_above=\"" << tempData.maxKarma
	     << "\" rankline=\"primary\""
	     << endl;
  }

  cout << endl << "rank.conf created.  Given a sufficiently big clan with a sufficiently simple 100% karma-based and up-to-date clan, the automatically generated rank.conf could be fully functional, but for the majority of cases, significant editing will be necessary for the ranking functionality to work.  Searching will work, except for by rank line. YOU CAN RANK WITH THIS RANK.CONF BUT IT WILL LIKELY BE WILDLY INACCURATE." << endl;
}
