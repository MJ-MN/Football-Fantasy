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
  Match(const Match &);
  Match& operator=(const Match &);
  ~Match();

  void extract_data(MatchTitle title, std::string content,
                    Football &football);
  std::pair<Player *, Player *> find_best_players_in_role(RoleTitle role);

 private:
  void extract_teams(std::string content, Football &football);
  void extract_result(std::string content);
  void extract_players_in_field(std::string content,
                               std::vector<Player *> &field);
  void extract_players_score(std::string content);

  Team *firstTeam;
  Team *secondTeam;
  std::vector<Player *> injured;
  std::vector<Player *> yellow_cards;
  std::vector<Player *> red_cards;
};

#endif /* __MATCH_HH */
