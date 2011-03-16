#include "rank.h"
#include "ranksystem.h"
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

int main(int argc, char* argv[])
{
  bool options [3] = {false, false, false}; //option flags. {human-readable, search, search by criteria}
  string filename = "", criteria = ""; //search criteria

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

  return 0;
}
