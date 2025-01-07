#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "football.hh"
#include "manual.hh"
#include "week.hh"

using namespace std;

void Football::get_team_of_the_week(stringstream &ss) const {
  string qm(""), week_num_arg(""), week_num("");
  ss >> qm >> week_num_arg >> week_num;
  if (qm == "?" && week_num_arg != "" && week_num != "") {
    if (week_num_arg == "week_num") {
      this->print_team_of_the_week(stoi(week_num) - 1);
    } else {
      cout << kBadRequest << endl;
    }
  } else if (qm == "" && week_num_arg == "" && week_num == "") {
    this->print_team_of_the_week(this->last_week);
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::print_team_of_the_week(int week_num) const {
  if (week_num >= 0 && week_num < this->weeks.size()) {
      cout << "Team of the week:" << endl;
      this->print_best_players_in_role(RoleTitle::kGoalkeeper, week_num);
      this->print_best_players_in_role(RoleTitle::kDefender, week_num);
      this->print_best_players_in_role(RoleTitle::kMidfielder, week_num);
      this->print_best_players_in_role(RoleTitle::kForward, week_num);
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::print_best_players_in_role(RoleTitle role, int week_num) const {
  vector<Player *> best_players;
  pair<Player *, Player *> two_best_players;
  for (Team *team : this->teams) {
    two_best_players = find_two_best_players(team->get_players_in_role(role),
                                             week_num);
    best_players.push_back(two_best_players.first);
    best_players.push_back(two_best_players.second);
  }
  two_best_players = find_two_best_players(best_players, week_num);
  if (role != RoleTitle::kDefender) {
    two_best_players.first->print_name_score(week_num);
  } else {
    two_best_players.first->print_name_score(week_num, Rank::kFirstRank);
    two_best_players.second->print_name_score(week_num, Rank::kSecondRank);
  }
}

void Football::get_players(stringstream &ss) const {
  string qm(""), team_name_arg(""), team_name("");
  ss >> qm >> team_name_arg >> team_name;
  if (qm == "?" && team_name_arg == "team_name" && team_name != "") {
    Team *team = this->find_team_by_name(replace_underscore(team_name));
    if (team != NULL) {
      team->print_players(ss);
    } else {
      cout << kNotFound << endl;
    }
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::get_league_standings() const {
  cout << "league standings:" << endl;
  this->print_league_standings();
}

void Football::print_league_standings() const {
  vector<Team *> _teams = this->teams;
  sort(_teams.begin(), _teams.end(), standings_comparator);
  for (int i = 0; i < _teams.size(); ++i) {
    _teams[i]->print_score(i + 1);
  }
}

void Football::get_users_ranking() const {
  vector<User *> _users = this->users;
  sort(_users.begin(), _users.end(), [=](User *user1, User *user2) {
    if (user1->get_score(this->last_week) ==
        user2->get_score(this->last_week)) {
      return user1->get_name() < user2->get_name();
    } else {
      return user1->get_score(this->last_week) >
             user2->get_score(this->last_week);
    }
  });
  for (int i = 0; i < _users.size(); ++i) {
    cout << i + 1 << ". team_name: ";
    cout << _users[i]->get_name() << " | ";
    cout << _users[i]->get_score(this->last_week) << endl;
  }
}

void Football::get_matches_result_league(stringstream &ss) const {
  string qm(""), week_num_arg(""), week_num("");
  ss >> qm >> week_num_arg >> week_num;
  if (qm == "?" && week_num_arg != "" && week_num != "") {
    if (week_num_arg == "week_num") {
      this->print_matches_result_league(stoi(week_num) - 1);
    } else {
      cout << kBadRequest << endl;
    }
  } else if (qm == "" && week_num_arg == "" && week_num == "") {
    this->print_matches_result_league(this->last_week);
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::print_matches_result_league(int week_num) const {
  if (week_num >= 0 && week_num < this->weeks.size()) {
    this->weeks[week_num]->print_matches_result(week_num);
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::get_squad(stringstream &ss) const {
  string qm(""), fantasy_team_arg(""), fantasy_team("");
  ss >> qm >> fantasy_team_arg >> fantasy_team;
  if (qm == "?" && fantasy_team_arg != "" && fantasy_team != "") {
    if (fantasy_team_arg == "fantasy_team") {
      this->print_squad(fantasy_team);
    } else {
      cout << kBadRequest << endl;
    }
  } else if (qm == "" && fantasy_team_arg == "" && fantasy_team == "") {
    this->print_squad();
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::print_squad(const string &fantasy_team) const {
  if (fantasy_team != "") {
    User *user = this->find_user_by_name(fantasy_team);
    if (user != NULL) {
      user->print_squad(this->last_week);
    } else {
      cout << kNotFound << endl;
    }
  } else {
    User *user = this->who_is_logged_in();
    if (user != NULL) {
      user->print_squad(this->last_week);
    } else {
      cout << kPermissionDenied << endl;
    }
  }
}
