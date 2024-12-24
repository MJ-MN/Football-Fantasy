#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "manual.hh"
#include "player.hh"
#include "team.hh"

using namespace std;

Team::Team(const string &_name) : name(_name) {}

Team::~Team() {
  for (auto player : this->players) {
    delete player;
  }
}

Team::Team(const Team &team) {
  this->name = team.name;
  this->goals = team.goals;
  for (auto player : team.players) {
    this->players.push_back(player->clone());
  }
}

Team &Team::operator=(const Team &team) {
  if (this != &team) {
    for (auto player : this->players) {
      delete player;
    }
    this->name = team.name;
    this->goals = team.goals;
    for (auto player : team.players) {
      this->players.push_back(player->clone());
    }
  }
  return *this;
}

void Team::set_goal(int goal) {
  this->goals.back() = goal;
}

string Team::get_name() const {
  return this->name;
}

vector<Player *> Team::get_players_in_role(RoleTitle role) const {
  vector<Player *> players_in_role;
  for (Player *player : this->players) {
    if (player->get_role() == role) {
      players_in_role.push_back(player);
    }
  }
  return players_in_role;
}

Player *Team::find_player_by_name(const string &name) const {
  for (Player *player : this->players) {
    if (player->get_name() == name) {
      return player;
    }
  }
  return NULL;
}

void Team::extract_data(TeamTitle title, const string &content) {
  switch (title) {
    case TeamTitle::kTeamName:
      this->name = content;
      break;
    case TeamTitle::kTeamGoalkeepers:
      this->extract_goalkeepers(content);
      break;
    case TeamTitle::kTeamDefenders:
      this->extract_defenders(content);
      break;
    case TeamTitle::kTeamMidfielders:
      this->extract_midfielders(content);
      break;
    default:
      this->extract_forwards(content);
      break;
  }
}

void Team::add_match() {
  this->goals.push_back(-1);
  for (Player *player : this->players) {
    player->add_match();
  }
}

void Team::extract_goalkeepers(const string &content) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    this->players.push_back(new Goalkeeper(name));
  }
}

void Team::extract_defenders(const string &content) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    this->players.push_back(new Defender(name));
  }
}

void Team::extract_midfielders(const string &content) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    this->players.push_back(new Midfielder(name));
  }
}

void Team::extract_forwards(const string &content) {
  stringstream content_ss(content);
  string name("");
  while (getline(content_ss, name, ';')) {
    this->players.push_back(new Forward(name));
  }
}
