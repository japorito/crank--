#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "rankutils.hpp"

using namespace std;

RankUtils::RankUtils() {}

RankUtils::RankUtils(string filename)
{
  makeRankBook(filename);
}

void RankUtils::makeRankBook(string filename)
{
  fstream roster;
  string is;
  string raw;
  int line=0;

  if (filename == "") {
    //if constructor is called with empty string as argument, get the filename.
    cout << "Input filename: ";
    cin >> filename;
  }
  roster.open(filename.c_str(), fstream::in);

  while (roster.is_open() == false) {
    //if getting the filename failed, try, try again.
    cout << "Invalid filename \"" << filename << "\"." << " Try again: ";
    cin >> filename;
    roster.open(filename.c_str(), fstream::in);
  }
  
  while (roster.peek() != EOF) {
    //Pulls line which holds pertinent info.  Line 10 has the info.
    getline(roster, is);
    line++;
    //if (++line == 10) {
    if (is.find("showplayer.php?who=") != (size_t) (-1)) {
      raw = is;
    }
  }

  /* Processes HTML to pull out name, karma, rank, and uses it to make
   * the main Data vector of the Rank class. 
   */
  bool watching = false; //flag turning on and off assigning to variables
  Data tempData;
  string tempKarma; //read in as string at first, until it is converted to an int
  int rawLength = raw.find("clan_members.php"); // to avoid function call in loop
  watchFor watchingFor = PERSON; //next data member to pull from HTML

  for (int i = raw.find("showplayer.php?who="); i < rawLength; i++) {
    if (raw[i] == '>') { //start looking for data to pull (out of HTML)
      watching = true;
      i++;
    }
    if (raw[i] == '<' || raw[i] == '&') { //stop looking for data. & stops recording if, for instance, it hits an &nbsp;

      //toggles watching to off and shifts what it is watching for to the next thing.
      watching = false;

      if (watchingFor == PERSON && !tempData.person.empty()) watchingFor = CLASS;
      if (watchingFor == CLASS && !tempData.playerClass.empty()) watchingFor = RANK;
      if (watchingFor == RANK && !is_int(tempData.rank) && !tempData.rank.empty()) {
	//Only shifts what is being watched for if the rank isn't an int.
	watchingFor = KARMA;
      }
      if (watchingFor == RANK && is_int(tempData.rank)) tempData.rank.clear();
      //if it is an int, throw it away.

      if (watchingFor == KARMA && !tempKarma.empty()) {
	//By now, a person's info is pulled.  This stores it.
	watchingFor = PERSON;
	tempData.karma = to_int(tempKarma);
	rankBook.push_back(tempData);
	tempData.person.clear();
	tempData.playerClass.clear();
	tempData.rank.clear();
	tempKarma.clear();
      }
    }

    if (watching) { //actual pulling of data
      if (watchingFor == PERSON) tempData.person += raw[i];
      if (watchingFor == CLASS) tempData.playerClass += raw[i];
      if (watchingFor == RANK && raw[i] != ',') tempData.rank += raw[i];
      if (watchingFor == KARMA) tempKarma += raw[i];
    }
  }  
}

bool RankUtils::empty() const
{
  return (rankBook.size() == 0);
}

const vector<Data> & RankUtils::getRankBook() const
{
  return rankBook;
}
