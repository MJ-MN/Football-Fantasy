#include <algorithm>
#include <iostream>
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
  for (auto goal : this->goals) {
    delete goal;
  }
  for (auto player : this->players) {
    delete player;
  }
}

Team::Team(const Team &team) {
  this->name = team.name;
  for (auto goal : team.goals) {
    this->goals.push_back(new Goal(*goal));
  }
  for (auto player : team.players) {
    this->players.push_back(player->clone());
  }
}

Team &Team::operator=(const Team &team) {
  if (this != &team) {
    for (auto goal : this->goals) {
      delete goal;
    }
    for (auto player : this->players) {
      delete player;
    }
    this->name = team.name;
    for (auto goal : team.goals) {
      this->goals.push_back(new Goal(*goal));
    }
    for (auto player : team.players) {
      this->players.push_back(player->clone());
    }
  }
  return *this;
}

void Team::set_goal(const Goal &goal) {
  this->goals.back()->goals_for = goal.goals_for;
  this->goals.back()->goals_against = goal.goals_against;
}

string Team::get_name() const {
  return this->name;
}

int Team::get_score() const {
  int score = 0;
  for (Goal *goal : this->goals) {
    score += (goal->goals_for > goal->goals_against) ? 3 :
             (goal->goals_for < goal->goals_against) ? 0 : 1;
  }
  return score;
}

int Team::get_goals_diff() const {
  int goal_diff = 0;
  for (Goal *goal : this->goals) {
    goal_diff += goal->goals_for - goal->goals_against;
  }
  return goal_diff;
}

int Team::get_goal_for(int week_num) const {
  return this->goals[week_num]->goals_for;
}

int Team::get_goals_for() const {
  int goal_for = 0;
  for (Goal *goal : this->goals) {
    goal_for += goal->goals_for;
  }
  return goal_for;
}

int Team::get_goals_against() const {
  int goal_against = 0;
  for (Goal *goal : this->goals) {
    goal_against += goal->goals_against;
  }
  return goal_against;
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
  this->goals.push_back(new Goal{-1, -1});
  for (Player *player : this->players) {
    player->add_match();
  }
}

void Team::print_players(stringstream &ss) const {
  string role_or_ranks_arg("");
  ss >> role_or_ranks_arg;
  if (role_or_ranks_arg != "") {
    if (role_or_ranks_arg == "gk" || role_or_ranks_arg == "df" ||
        role_or_ranks_arg == "md" || role_or_ranks_arg == "fw") {
      this->print_players_in_role(ss, role_or_ranks_arg);
    } else if (role_or_ranks_arg == "ranks") {
      this->print_players_in_order_of(this->players, InOrderOf::kScore);
    } else {
      cout << BAD_REQUEST << endl;
    }
  } else {
    this->print_players_in_order_of(this->players, InOrderOf::kName);
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

void Team::print_players_in_role(stringstream &ss, const string &role) const {
  string ranks("");
  ss >> ranks;
  vector<Player *> _players =
      this->get_players_in_role(kRoleMap.find(role)->second);
  if (ranks == "ranks") {
    this->print_players_in_order_of(_players, InOrderOf::kScore);
  } else if (ranks == "") {
    this->print_players_in_order_of(_players, InOrderOf::kName);
  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Team::print_players_in_order_of(vector<Player *> _players, InOrderOf order) const {
  cout << "list of players:" << endl;
  if (order == InOrderOf::kName) {
    sort(_players.begin(), _players.end(), [](Player *player1,
                                              Player *player2) {
      return player1->get_name() < player2->get_name();
    });
  } else {
    sort(_players.begin(), _players.end(), [](Player *player1,
                                              Player *player2) {
      return player1->get_avg_score() > player2->get_avg_score();
    });
  }
  for (int i = 0; i < _players.size(); ++i) {
    _players[i]->print_name_role_score(i + 1);
  }
}

void Team::print_score(int rank) const {
  cout << rank << ". " << this->name;
  cout << ": score: " << this->get_score();
  cout << " | GF: " << this->get_goals_for();
  cout << " | GA: " << this->get_goals_against() << endl;
}
