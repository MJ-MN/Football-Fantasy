#ifndef __MATCH_HH
#define __MATCH_HH

#include <string>
#include <vector>

#include "player.hh"
#include "team.hh"

const int kMatchColumns = 6;

enum class MatchTitle {
  kMatchTeams = 0,
  kMatchResult,
  kMatchInjured,
  kMatchYellowCards,
  kMatchRedCards,
  kMatchScores
};

class Football;

class Match {
 public:
  Match() = default;
  Match(const Match &) = default;
  Match& operator=(const Match &) = default;
  ~Match() = default;

  void extract_data(MatchTitle title, const std::string &content,
                    Football &football);
  void print_result(int week_num) const;

 private:
  void extract_teams(const std::string &content, Football &football);
  void extract_result(const std::string &content);
  void extract_players_in_field(const std::string &content,
                                std::vector<Player *> &field);
  void extract_players_score(const std::string &content);

  Team *firstTeam;
  Team *secondTeam;
  std::vector<Player *> injured;
  std::vector<Player *> yellow_cards;
  std::vector<Player *> red_cards;
};

#endif /* __MATCH_HH */
