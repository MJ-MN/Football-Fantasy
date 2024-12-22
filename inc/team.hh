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
  std::vector<Player *> &get_players_in_role(RoleTitle role);
  Player *find_player_by_name(std::string name);
  void extract_data(TeamTitle index, std::string content);
  void add_match();

 private:
  void extract_players_in_role(std::string content,
                               std::vector<Player *> &role);

  std::string name;
  std::vector<int> goals;
  std::vector<Player *> goalkeepers;
  std::vector<Player *> defenders;
  std::vector<Player *> midfielders;
  std::vector<Player *> forwards;
};

#endif /* __TEAM_HH */
