#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "football.hh"
#include "manual.hh"
#include "match.hh"
#include "player.hh"
#include "team.hh"

using namespace std;

void Match::extract_data(MatchTitle title, const string &content,
                         Football &football) {
  switch (title) {
    case MatchTitle::kMatchTeams:
      this->extract_teams(content, football);
      break;
    case MatchTitle::kMatchResult:
      this->extract_result(content);
      break;
    case MatchTitle::kMatchInjured:
      this->extract_players_in_field(content, this->injured);
      break;
    case MatchTitle::kMatchYellowCards:
      this->extract_players_in_field(content, this->yellow_cards);
      break;
    case MatchTitle::kMatchRedCards:
      this->extract_players_in_field(content, this->red_cards);
      break;
    case MatchTitle::kMatchScores:
      this->extract_players_score(content);
      break;
    default:
      break;
  }
}

void Match::extract_teams(const string &content, Football &football) {
  stringstream content_ss(content);
  string name("");
  getline(content_ss, name, ':');
  this->firstTeam = football.find_team_by_name(name);
  this->firstTeam->add_match();
  getline(content_ss, name);
  this->secondTeam = football.find_team_by_name(name);
  this->secondTeam->add_match();
}

void Match::extract_result(const string &content) {
  stringstream content_ss(content);
  string num1(""), num2("");
  getline(content_ss, num1, ':');
  getline(content_ss, num2);
  this->firstTeam->set_goal(Goal{stoi(num1), stoi(num2)});
  this->secondTeam->set_goal(Goal{stoi(num2), stoi(num1)});
}

void Match::extract_players_in_field(const string &content,
                                     vector<Player *> &field) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    Player *player = this->firstTeam->find_player_by_name(name);
    if (player == NULL) {
      player = this->secondTeam->find_player_by_name(name);
    }
    field.push_back(player);
  }
}

void Match::extract_players_score(const string &content) {
  stringstream content_ss(content);
  string player_s("");
  while (getline(content_ss, player_s, ';')) {
    stringstream player_ss(player_s);
    string name("");
    getline(player_ss, name, ':');
    string score("");
    getline(player_ss, score);
    Player *player = this->firstTeam->find_player_by_name(name);
    if (player == NULL) {
      player = this->secondTeam->find_player_by_name(name);
    }
    player->set_score(stof(score));
  }
}

void Match::print_result(int week_num) const {
  cout << this->firstTeam->get_name();
  cout << " " << this->firstTeam->get_goal_for(week_num);
  cout << " | " << this->secondTeam->get_name();
  cout << " " << this->secondTeam->get_goal_for(week_num) << endl;
}

bool Match::player_has_red_card(const Player *player) const {
  for (Player *_player : this->red_cards) {
    if (_player == player) {
      return true;
    }
  }
  return false;
}

bool Match::player_has_yellow_card(const Player *player) const {
  for (Player *_player : this->yellow_cards) {
    if (_player == player) {
      return true;
    }
  }
  return false;
}

bool Match::player_is_injured(const Player *player) const {
  for (Player *_player : this->injured) {
    if (_player == player) {
      return true;
    }
  }
  return false;
}
