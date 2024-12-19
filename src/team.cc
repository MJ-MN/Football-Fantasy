#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "manual.hh"
#include "player.hh"
#include "team.hh"

using namespace std;

Team::Team() : goals(-1) {}

Team::Team(string _name) : name(_name), goals(-1) {}

Team::~Team() {
  for (auto player : this->goalkeepers) { delete player; }
  for (auto player : this->defenders) { delete player; }
  for (auto player : this->midfielders) { delete player; }
  for (auto player : this->forwards) { delete player; }
}

Team::Team(const Team &team) {
  this->name = team.name;
  for (auto player : team.goalkeepers) {
    this->goalkeepers.push_back(new Player(*player));
  }
  for (auto player : team.defenders) {
    this->defenders.push_back(new Player(*player));
  }
  for (auto player : team.midfielders) {
    this->midfielders.push_back(new Player(*player));
  }
  for (auto player : team.forwards) {
    this->forwards.push_back(new Player(*player));
  }
}

Team &Team::operator=(const Team &team) {
  if (this != &team) {
    for (auto player : this->goalkeepers) { delete player; }
    for (auto player : this->defenders) { delete player; }
    for (auto player : this->midfielders) { delete player; }
    for (auto player : this->forwards) { delete player; }
    this->name = team.name;
    for (auto player : team.goalkeepers) {
      this->goalkeepers.push_back(new Player(*player));
    }
    for (auto player : team.defenders) {
      this->defenders.push_back(new Player(*player));
    }
    for (auto player : team.midfielders) {
      this->midfielders.push_back(new Player(*player));
    }
    for (auto player : team.forwards) {
      this->forwards.push_back(new Player(*player));
    }
  }
  return *this;
}

void Team::set_goals(int _goals) {
  this->goals = _goals;
}

string Team::get_name() {
  return this->name;
}

vector<Player *> &Team::get_players_in_role(RoleTitle role) {
  switch (role) {
    case RoleTitle::kGoalkeeper:
      return this->goalkeepers;
    case RoleTitle::kDefender:
      return this->defenders;
    case RoleTitle::kMidfielder:
      return this->midfielders;
    default:
      return this->forwards;
  }
}

Player *Team::find_player_by_name(string name) {
  for (Player *player : this->goalkeepers) {
    if (player->get_name() == name) { return player; }
  }
  for (Player *player : this->defenders) {
    if (player->get_name() == name) { return player; }
  }
  for (Player *player : this->midfielders) {
    if (player->get_name() == name) { return player; }
  }
  for (Player *player : this->forwards) {
    if (player->get_name() == name) { return player; }
  }
  return NULL;
}

void Team::extract_data(TeamTitle title, string content) {
  switch (title) {
    case TeamTitle::kTeamName:
      this->name = content;
      break;
    case TeamTitle::kTeamGoalkeepers:
      this->extract_players_in_role(content, this->goalkeepers);
      break;
    case TeamTitle::kTeamDefenders:
      this->extract_players_in_role(content, this->defenders);
      break;
    case TeamTitle::kTeamMidfielders:
      this->extract_players_in_role(content, this->midfielders);
      break;
    case TeamTitle::kTeamForwards:
      this->extract_players_in_role(content, this->forwards);
      break;
    default:
      break;
  }
}

void Team::extract_players_in_role(string content, vector<Player *> &role) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    role.push_back(new Player(name));
  }
}
