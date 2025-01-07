#ifndef __FANTASY_TEAM
#define __FANTASY_TEAM

#include <string>

#include "player.hh"

class FantasyTeam {
 public:
  FantasyTeam();
  FantasyTeam(const FantasyTeam &) = default;
  FantasyTeam &operator=(const FantasyTeam &team) = default;
  ~FantasyTeam() = default;

  void set_completed();
  bool is_completed() const;
  bool is_filled() const;
  bool sell_player(const std::string &name);
  bool buy_player(Player *player);
  void print_players() const;
  void print_score(int week_num) const;

 private:
  Player *goalkeeper;
  Player *defender1;
  Player *defender2;
  Player *midfielder;
  Player *forward;
  bool completed;
};

#endif /* __FANTASY_TEAM */
