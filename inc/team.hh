#ifndef __TEAM_HH
#define __TEAM_HH

#include <string>
#include <vector>

#include "player.hh"

const int kTeamColumns = 5;

enum class TeamTitle {
  kTeamName = 0,
  kTeamGoalkeepers,
  kTeamDefenders,
  kTeamMidfielders,
  kTeamForwards
};

class Team {
 public:
  Team() = default;
  Team(const std::string &_name);
  Team(const Team &);
  Team &operator=(const Team &);
  ~Team();

  void set_goal(int goal);
  std::string get_name() const;
  std::vector<Player *> get_players_in_role(RoleTitle role) const;
  Player *find_player_by_name(const std::string &name) const;
  void extract_data(TeamTitle index, const std::string &content);
  void add_match();

 private:
  void extract_goalkeepers(const std::string &content);
  void extract_defenders(const std::string &content);
  void extract_midfielders(const std::string &content);
  void extract_forwards(const std::string &content);

  std::string name;
  std::vector<int> goals;
  std::vector<Player *> players;
};

#endif /* __TEAM_HH */
