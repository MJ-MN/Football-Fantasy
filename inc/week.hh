#ifndef __WEEK_HH
#define __WEEK_HH

#include <fstream>
#include <vector>

#include "match.hh"
#include "player.hh"

class Football;

class Week {
 public:
  Week() = default;
  Week(std::vector<Match*> _matches);
  Week(const Week &);
  Week& operator=(const Week &);
  ~Week();

  std::vector<MatchTitle> extract_matches_title(std::ifstream &ifs);
  void extract_matches_data(std::ifstream &ifs,
                            const std::vector<MatchTitle> &teams_title_pos,
                            Football &football);
  void print_team_of_the_week();

 private:
  void print_best_player_in_role(RoleTitle role);
  void print_player_score(const std::pair<Player *, Player *> &palyers,
                          RoleTitle role);

  std::vector<Match*> matches;
};

#endif /* __WEEK_HH */
