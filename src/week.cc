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

vector<MatchTitle> Week::extract_matches_title(ifstream &ifs) {
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

void Week::print_team_of_the_week() {
  cout << "Team of the week:" << endl;
  this->print_best_player_in_role(RoleTitle::kGoalkeeper);
  this->print_best_player_in_role(RoleTitle::kDefender);
  this->print_best_player_in_role(RoleTitle::kMidfielder);
  this->print_best_player_in_role(RoleTitle::kForward);
}

void Week::print_best_player_in_role(RoleTitle role) {
  vector<Player *> best_players;
  pair<Player *, Player *> two_best_players;
  for (Match *match : this->matches) {
    two_best_players = match->find_best_players_in_role(role);
    best_players.push_back(two_best_players.first);
    best_players.push_back(two_best_players.second);
  }
  two_best_players = find_two_best_players(best_players);
  print_player_score(two_best_players, role);
}

void Week::print_player_score(const pair<Player *, Player *> &palyers,
                              RoleTitle role) {
  switch (role) {
    case RoleTitle::kGoalkeeper:
      cout << "Goalkeeper: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score() << endl;
      break;
    case RoleTitle::kDefender:
      cout << "Defender 1: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score() << endl;
      cout << "Defender 2: " << palyers.second->get_name()
           << " | score: " << palyers.second->get_score() << endl;
      break;
    case RoleTitle::kMidfielder:
      cout << "Midfielder: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score() << endl;
      break;
    default:
      cout << "Forward: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score() << endl;
      break;
  }
}
