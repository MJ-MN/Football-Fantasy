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

Match::Match(const Match &match) {
  this->firstTeam = new Team(*match.firstTeam);
  this->secondTeam = new Team(*match.secondTeam);
  this->injured = match.injured;
  this->yellow_cards = match.yellow_cards;
  this->red_cards = match.red_cards;
}

Match& Match::operator=(const Match &match) {
  if (this != &match) {
    delete this->firstTeam;
    this->firstTeam = new Team(*match.firstTeam);
    delete this->secondTeam;
    this->secondTeam = new Team(*match.secondTeam);
    this->injured = match.injured;
    this->yellow_cards = match.yellow_cards;
    this->red_cards = match.red_cards;
  }
  return *this;
}

Match::~Match() {
  delete this->firstTeam;
  delete this->secondTeam;
}

void Match::extract_data(MatchTitle title, string content,
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

pair<Player *, Player *> Match::find_best_players_in_role(RoleTitle role) {
  pair<Player *, Player *> best_players1 =
      find_two_best_players(this->firstTeam->get_players_in_role(role));
  pair<Player *, Player *> best_players2 =
      find_two_best_players(this->secondTeam->get_players_in_role(role));
  vector<Player *> best_players = {best_players1.first, best_players2.first,
                                   best_players1.second, best_players2.second};
  return find_two_best_players(best_players);
}

void Match::extract_teams(std::string content, Football &football) {
  stringstream content_ss(content);
  string name("");
  getline(content_ss, name, ':');
  this->firstTeam = new Team(*(football.find_team_by_name(name)));
  getline(content_ss, name);
  this->secondTeam = new Team(*(football.find_team_by_name(name)));
}

void Match::extract_result(std::string content) {
  stringstream content_ss(content);
  string num("");
  getline(content_ss, num, ':');
  this->firstTeam->set_goals(stoi(num));
  getline(content_ss, num);
  this->secondTeam->set_goals(stoi(num));
}

void Match::extract_players_in_field(string content, vector<Player *> &field) {
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

void Match::extract_players_score(string content) {
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

