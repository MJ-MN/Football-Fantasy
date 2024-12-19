#include <set>
#include <utility>
#include <vector>

#include "player.hh"

using namespace std;

pair<Player *, Player *> find_two_best_players(
    const vector<Player *> &players) {
  set<Player *> players_set(players.begin(), players.end());
  auto first_player_it = players_set.begin();
  auto second_player_it = (players_set.size() > 1) ? ++players_set.begin() :
                                                     first_player_it;
  auto temp_player_it = ++players_set.begin();
  while (temp_player_it != players_set.end()) {
    if ((*temp_player_it)->get_score() >= (*first_player_it)->get_score()) {
      second_player_it = first_player_it;
      first_player_it = temp_player_it;
    }
    ++temp_player_it;
  }
  return pair<Player *, Player *>(*first_player_it, *second_player_it);
}
