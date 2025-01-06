#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "player.hh"
#include "team.hh"

using namespace std;

pair<Player *, Player *> find_two_best_players(
    const vector<Player *> &players, int week_num) {
  auto first_player_it = players.begin();
  auto second_player_it = (players.size() > 1) ? ++players.begin() :
                                                 first_player_it;
  auto temp_player_it = ++players.begin();
  while (temp_player_it != players.end()) {
    if ((*temp_player_it)->get_score(week_num) >=
        (*first_player_it)->get_score(week_num)) {
      second_player_it = first_player_it;
      first_player_it = temp_player_it;
    }
    ++temp_player_it;
  }
  return pair<Player *, Player *>(*first_player_it, *second_player_it);
}

string replace_underscore(string str) {
  size_t pos = str.find('_');
  if (pos != string::npos) {
    str[pos] = ' ';
  }
  return str;
}

string get_name(stringstream &ss) {
  string name("");
  getline(ss, name, '\0');
  name.erase(name.begin());
  return name;
}

bool standings_comparator(Team *team1, Team *team2) {
  if (team1->get_score() == team2->get_score()) {
    if (team1->get_goals_diff() == team2->get_goals_diff()) {
      if (team1->get_goals_for() == team2->get_goals_for()) {
        return team1->get_name() < team2->get_name();
      } else {
        return team1->get_goals_for() > team2->get_goals_for();
      }
    } else {
      return team1->get_goals_diff() > team2->get_goals_diff();
    }
  } else {
    return team1->get_score() > team2->get_score();
  }
}
