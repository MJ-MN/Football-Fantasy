#include <set>
#include <utility>
#include <vector>

#include "player.hh"

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
