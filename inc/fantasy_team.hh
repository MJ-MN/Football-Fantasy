#ifndef __FANTASY_TEAM
#define __FANTASY_TEAM

#include <string>

#include "player.hh"

class FantasyTeam {
 public:
  FantasyTeam();

  bool is_completed() const;
  bool sell_player(const std::string &name);

 private:
  Goalkeeper *goalkeeper;
  Defender *defender1;
  Defender *defender2;
  Midfielder *midfielder;
  Forward *forward;
};

#endif /* __FANTASY_TEAM */
