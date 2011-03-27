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

void Rank::doRanks(const vector<Ranks> ranksystem)
{
  PersonToRank tempPerson;
  const vector <Data> clanMembers = getRankBook();
  unsigned int size = clanMembers.size();
  unsigned int rankNum = ranksystem.size();

  for (unsigned int i = 0; i < size; i++) {
    for (unsigned int j = 0; j < rankNum; j++) {
      if (ranksystem[j].rank == clanMembers[i].rank &&
	  (ranksystem[j].minToReturn > clanMembers[i].karma
	   || ranksystem[j].maxToReturn < clanMembers[i].karma)) {
	if (ranksystem[j].maxToReturn == -1) continue;
	tempPerson.person = clanMembers[i].person;
	tempPerson.currentRank = clanMembers[i].rank;
	tempPerson.currentAbbr = ranksystem[j].abbreviation;
	tempPerson.rankLine = ranksystem[j].rankLine;
	tempPerson.karma = clanMembers[i].karma;
	peopleToRank.push_back(tempPerson);
      }
    }
  }

  for (unsigned int i = 0; i < peopleToRank.size(); i++) {
    for (unsigned int j = 0; j < ranksystem.size(); j++) {
      if (peopleToRank[i].rankLine == ranksystem[j].rankLine) {
	if (peopleToRank[i].karma > ranksystem[j].minKarma 
	    && peopleToRank[i].karma < ranksystem[j].maxKarma
	    && ranksystem[j].maxKarma != -1) {
	  peopleToRank[i].destRank = ranksystem[j].rank;
	  peopleToRank[i].destAbbr = ranksystem[j].abbreviation;
	}
	else if (peopleToRank[i].karma > ranksystem[j].minKarma
		 && ranksystem[j].maxKarma == -1) {
	  peopleToRank[i].destRank = ranksystem[j].rank;
	  peopleToRank[i].destAbbr = ranksystem[j].abbreviation;	  
	}
      }
    }
  }
  
  /*for (unsigned int i = 0; i < peopleToRank.size(); i++) {
    cout << peopleToRank[i].person << " needed ranked to " << peopleToRank[i].destRank << " " << peopleToRank[i].destAbbr << ". In rankline: " << peopleToRank[i].rankLine << " and rank: " << peopleToRank[i].currentRank << " " << peopleToRank[i].currentAbbr << endl << "(S)he has " << peopleToRank[i].karma << endl;
    }*/
}
