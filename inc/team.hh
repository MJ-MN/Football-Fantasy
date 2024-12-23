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
  Team(std::string _name);
  Team(const Team &);
  Team &operator=(const Team &);
  ~Team();

  void set_goal(int goal);
  std::string get_name();
  std::vector<Player *> get_players_in_role(RoleTitle role);
  Player *find_player_by_name(std::string name);
  void extract_data(TeamTitle index, std::string content);
  void add_match();

 private:
  void extract_goalkeepers(std::string content);
  void extract_defenders(std::string content);
  void extract_midfielders(std::string content);
  void extract_forwards(std::string content);

  std::string name;
  std::vector<int> goals;
  std::vector<Player *> players;
};

#endif /* __TEAM_HH */
