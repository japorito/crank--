#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "rankutils.hpp"

using namespace std;

RankUtils::RankUtils(string filename)
{
  //options bool array contains option flags. {human-readable, search}
  fstream roster;
  string is;
  string raw;
  int line=0;

  if (filename == "") {
    //if constructor is called without an argument, get the filename.
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
  string tempKarma;
  int rawLength = raw.find("clan_members.php"); // to avoid function call in loop
  watchFor watchingFor = PERSON;

  for (int i = raw.find("showplayer.php?who="); i < rawLength; i++) {
    if (raw[i] == '>') {
      watching = true;
      i++;
    }
    if (raw[i] == '<' || raw[i] == '&') {
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
	watchingFor = PERSON;
	tempData.karma = to_int(tempKarma);
	rankBook.push_back(tempData);
	tempData.person.clear();
	tempData.playerClass.clear();
	tempData.rank.clear();
	tempKarma.clear();
      }
    }
    if (watching) {
      if (watchingFor == PERSON) tempData.person += raw[i];
      if (watchingFor == CLASS) tempData.playerClass += raw[i];
      if (watchingFor == RANK && raw[i] != ',') tempData.rank += raw[i];
      if (watchingFor == KARMA) tempKarma += raw[i];
    }
  }
}

inline bool RankUtils::is_int(string input) const
{
  for (unsigned int i = 0; i < input.length(); i++) {
    if (!isdigit(input[i])) return false;
  }
  return true;
}

inline int RankUtils::to_int(string input) {
  int answer = 0, tempNum = 0;
  for (unsigned int i = 0; i < input.length(); i++) {
    if (input[i] == '0') tempNum = 0;
    else if (input[i] == '1') tempNum = 1;
    else if (input[i] == '2') tempNum = 2;
    else if (input[i] == '3') tempNum = 3;
    else if (input[i] == '4') tempNum = 4;
    else if (input[i] == '5') tempNum = 5;
    else if (input[i] == '6') tempNum = 6;
    else if (input[i] == '7') tempNum = 7;
    else if (input[i] == '8') tempNum = 8;
    else if (input[i] == '9') tempNum = 9;
    answer += (pow(10, (input.length()-1-i))*tempNum);
  }
  return answer;
}

bool RankUtils::empty() const
{
  return (rankBook.size() == 0);
}

const vector<Data> & RankUtils::getRankBook() const
{
  return rankBook;
}
