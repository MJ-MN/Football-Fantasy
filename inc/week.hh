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

  std::vector<MatchTitle> extract_matches_title(std::ifstream &ifs) const;
  void extract_matches_data(std::ifstream &ifs,
                            const std::vector<MatchTitle> &teams_title_pos,
                            Football &football);
  void print_matches_result(int week_num) const;
  bool player_has_red_card(const Player *player) const;
  bool player_has_yellow_card(const Player *player) const;
  bool player_is_injured(const Player *player) const;

 private:
  std::vector<Match*> matches;
};

#endif /* __WEEK_HH */
