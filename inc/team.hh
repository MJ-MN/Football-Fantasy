#ifndef __TEAM_HH
#define __TEAM_HH

#include <map>
#include <string>
#include <vector>

#include "player.hh"

const int kTeamColumns = 5;

const std::map<std::string, RoleTitle> kRoleMap = {
  {"gk", RoleTitle::kGoalkeeper},
  {"df", RoleTitle::kDefender},
  {"md", RoleTitle::kMidfielder},
  {"fw", RoleTitle::kForward}
};

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
  void print_players(std::stringstream &ss) const;

 private:
  void extract_goalkeepers(const std::string &content);
  void extract_defenders(const std::string &content);
  void extract_midfielders(const std::string &content);
  void extract_forwards(const std::string &content);
  void print_players_in_role(std::stringstream &ss,
                             const std::string &role) const;
  void print_players_in_order_of(std::vector<Player *> players,
                                 InOrderOf order) const;

  std::string name;
  std::vector<int> goals;
  std::vector<Player *> players;
};

#endif /* __TEAM_HH */
