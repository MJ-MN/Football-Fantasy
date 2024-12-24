#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "football.hh"
#include "manual.hh"
#include "match.hh"
#include "player.hh"
#include "week.hh"

using namespace std;

Week::Week(vector<Match*> _matches) : matches(_matches) {}

Week::Week(const Week &week) {
  for (Match* match : week.matches) {
    this->matches.push_back(new Match(*match));
  }
}

Week& Week::operator=(const Week &week) {
  if (this != &week) {
    for (Match *match : this->matches) {
      delete match;
    }
    for (Match *match : week.matches) {
      this->matches.push_back(new Match(*match));
    }
  }
  return *this;
}

Week::~Week() {
  for (auto match : this->matches) {
    delete match;
  }
}

vector<MatchTitle> Week::extract_matches_title(ifstream &ifs) const {
  string line("");
  getline(ifs, line);
  line.pop_back();
  stringstream line_ss(line);
  int i = 0;
  vector<MatchTitle> titles_pos(kMatchColumns);
  string word("");
  while (getline(line_ss, word, ',')) {
    if (word == "match") {
      titles_pos[i] = MatchTitle::kMatchTeams;
    } else if (word == "result") {
      titles_pos[i] = MatchTitle::kMatchResult;
    } else if (word == "injured") {
      titles_pos[i] = MatchTitle::kMatchInjured;
    } else if (word == "yellow-card") {
      titles_pos[i] = MatchTitle::kMatchYellowCards;
    } else if (word == "red-card") {
      titles_pos[i] = MatchTitle::kMatchRedCards;
    } else if (word == "scores") {
      titles_pos[i] = MatchTitle::kMatchScores;
    }
    ++i;
  }
  return titles_pos;
}

void Week::extract_matches_data(ifstream &ifs, 
                                const vector<MatchTitle> &matches_title_pos,
                                Football &football) {
  string line("");
  while (getline(ifs, line)) {
    line.pop_back();
    int i = 0;
    Match *match = new Match;
    stringstream line_ss(line);
    string content("");
    while (getline(line_ss, content, ',')) {
      match->extract_data(matches_title_pos[i], content, football);
      ++i;
    }
    this->matches.push_back(match);
  }
}
