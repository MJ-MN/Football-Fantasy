#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "delete.hh"
#include "football.hh"
#include "manual.hh"
#include "post.hh"
#include "put.hh"
#include "team.hh"
#include "week.hh"

using namespace std;

Football::Football()
    : last_week(1) {}

Football::~Football() {
  for (auto team : this->teams) {
    delete team;
  }
  for (auto week : this->weeks) {
    delete week;
  }
}

vector<TeamTitle> Football::extract_teams_title(ifstream &ifs) const {
  string line("");
  getline(ifs, line);
  line.pop_back();
  stringstream line_ss(line);
  int i = 0;
  string word("");
  vector<TeamTitle> titles_pos(kTeamColumns);
  while (getline(line_ss, word, ',')) {
    if (word == "Team") {
      titles_pos[i] = TeamTitle::kTeamName;
    } else if (word == "Goalkeepers") {
      titles_pos[i] = TeamTitle::kTeamGoalkeepers;
    } else if (word == "Defenders") {
      titles_pos[i] = TeamTitle::kTeamDefenders;
    } else if (word == "Midfielders") {
      titles_pos[i] = TeamTitle::kTeamMidfielders;
    } else if (word == "Forwards") {
      titles_pos[i] = TeamTitle::kTeamForwards;
    }
    ++i;
  }
  return titles_pos;
}

void Football::extract_teams_data(ifstream &ifs,
                                  const vector<TeamTitle> &teams_title_pos) {
  string line("");
  while (getline(ifs, line)) {
    line.pop_back();
    int i = 0;
    Team *team = new Team;
    stringstream line_ss(line);
    string content("");
    while (getline(line_ss, content, ',')) {
      team->extract_data(teams_title_pos[i], content);
      ++i;
    }
    this->teams.push_back(team);
  }
}

Team *Football::find_team_by_name(const string &name) const {
  for (Team *team : this->teams) {
    if (team->get_name() == name) {
      return team;
    }
  }
  return NULL;
}

void Football::extract_teams() {
  ifstream primier_league("data/premier_league.csv");
  vector<TeamTitle> teams_title_pos = this->extract_teams_title(primier_league);
  this->extract_teams_data(primier_league, teams_title_pos);
  primier_league.close();
}

void Football::extract_weeks() {
  int i = 1;
  while (true) {
    ifstream week_stat("data/weeks_stats/week_" + to_string(i) + ".csv");
    if (!week_stat.is_open()) {
      break;
    }
    Week *week = new Week;
    vector<MatchTitle> matches_title_pos = week->extract_matches_title(week_stat);
    week->extract_matches_data(week_stat, matches_title_pos, *this);
    week_stat.close();
    this->weeks.push_back(week);
    ++i;
  }
}

void Football::process_get_method(stringstream &ss) const {
  string command("");
  ss >> command;
  if (command == "team_of_the_week") {
    this->get_team_of_the_week(ss);
  } else if (command == "players") {
    this->get_players(ss);
  } else if (command == "league_standings") {
    this->get_league_standings();
  } else if (command == "users_ranking") {
    this->get_users_ranking();
  } else if (command == "matches_result_league") {
    this->get_matches_result_league(ss);
  } else if (command == "squad") {
    this->get_squad(ss);
  } else if (command == "") {
    cout << BAD_REQUEST << endl;
  } else {
    cout << NOT_FOUND << endl;
  }
}

void Football::process_post_method(stringstream &ss) const {
  string command("");
  ss >> command;
  if (command == "signup") {
    post_signup(ss);
  } else if (command == "login") {
    post_login(ss);
  } else if (command == "register_admin") {
    post_register_admin(ss);
  } else if (command == "logout") {
    post_logout();
  } else if (command == "sell_player") {
    post_sell_player(ss);
  } else if (command == "buy_player") {
    post_buy_player(ss);
  } else if (command == "close_transfer_window") {
    post_close_transfer_window();
  } else if (command == "open_transfer_window") {
    post_open_transfer_window();
  } else if (command == "pass_week") {
    post_pass_week();
  } else if (command == "") {
    cout << BAD_REQUEST << endl;
  } else {
    cout << NOT_FOUND << endl;
  }
}

void Football::process_put_method(stringstream &ss) const {
  string command("");
  ss >> command;
  if (command == "") {
    cout << BAD_REQUEST << endl;
  } else {
    cout << NOT_FOUND << endl;
  }
}

void Football::process_delete_method(stringstream &ss) const {
  string command("");
  ss >> command;
  if (command == "") {
    cout << BAD_REQUEST << endl;
  } else {
    cout << NOT_FOUND << endl;
  }
}
