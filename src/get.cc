#include <iostream>
#include <sstream>
#include <string>

#include "football.hh"
#include "manual.hh"
#include "week.hh"

using namespace std;

void Football::get_team_of_the_week(stringstream &ss) {
  string qm(""), week_num_arg(""), week_num("");
  ss >> qm >> week_num_arg >> week_num;
  if (qm == "?" && week_num_arg != "" && week_num != "") {
    if (week_num_arg == "week_num") {
      this->print_team_of_the_week(stoi(week_num));
    } else {
      cout << BAD_REQUEST << endl;
    }
  } else if (qm == "" && week_num_arg == "" && week_num == "") {
    this->print_team_of_the_week(this->last_week);
  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Football::print_team_of_the_week(int week_num) {
  if (week_num >= 1 && week_num <= this->weeks.size()) {
      cout << "Team of the week:" << endl;
      this->print_best_players_in_role(RoleTitle::kGoalkeeper, week_num - 1);
      this->print_best_players_in_role(RoleTitle::kDefender, week_num - 1);
      this->print_best_players_in_role(RoleTitle::kMidfielder, week_num - 1);
      this->print_best_players_in_role(RoleTitle::kForward, week_num - 1);
  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Football::print_best_players_in_role(RoleTitle role, int week_num) {
  vector<Player *> best_players;
  pair<Player *, Player *> two_best_players;
  for (Team *team : this->teams) {
    two_best_players = find_two_best_players(team->get_players_in_role(role),
                                             week_num);
    best_players.push_back(two_best_players.first);
    best_players.push_back(two_best_players.second);
  }
  two_best_players = find_two_best_players(best_players, week_num);
  this->print_players_score(two_best_players, role, week_num);
}

void Football::print_players_score(const pair<Player *, Player *> &palyers,
                                   RoleTitle role, int week_num) {
  switch (role) {
    case RoleTitle::kGoalkeeper:
      cout << "Goalkeeper: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score(week_num) << endl;
      break;
    case RoleTitle::kDefender:
      cout << "Defender 1: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score(week_num) << endl;
      cout << "Defender 2: " << palyers.second->get_name()
           << " | score: " << palyers.second->get_score(week_num) << endl;
      break;
    case RoleTitle::kMidfielder:
      cout << "Midfielder: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score(week_num) << endl;
      break;
    default:
      cout << "Forward: " << palyers.first->get_name()
           << " | score: " << palyers.first->get_score(week_num) << endl;
      break;
  }
}

void Football::get_players(stringstream &ss) {
  string team_name_arg(""), team_name(""), role_arg(""), ranks_arg("");
  ss >> team_name_arg >> team_name >> role_arg >> ranks_arg;
  if (team_name_arg != "" && team_name != "") {
    if (team_name_arg == "team_name") {

    } else {
      cout << BAD_REQUEST << endl;
    }
  } else if (team_name_arg == "" && team_name == "") {

  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Football::get_league_standings() {

}

void Football::get_users_ranking() {

}

void Football::get_matches_result_league(stringstream &ss) {

} 

void Football::get_squad(stringstream &ss) {
  
}
