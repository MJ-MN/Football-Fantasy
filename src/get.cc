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
    this->weeks[week_num - 1]->print_team_of_the_week();
  } else {
    cout << BAD_REQUEST << endl;
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
