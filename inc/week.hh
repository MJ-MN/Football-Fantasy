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

 private:
  std::vector<Match*> matches;
};

#endif /* __WEEK_HH */
