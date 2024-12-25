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

struct Goal {
  int goals_for;
  int goals_against;
};

class Team {
 public:
  Team() = default;
  Team(const std::string &_name);
  Team(const Team &);
  Team &operator=(const Team &);
  ~Team();

  void set_goal(const Goal &goal);
  std::string get_name() const;
  int get_score() const;
  int get_goals_diff() const;
  int get_goal_for(int week_num) const;
  int get_goals_for() const;
  int get_goals_against() const;
  std::vector<Player *> get_players_in_role(RoleTitle role) const;
  Player *find_player_by_name(const std::string &name) const;
  void extract_data(TeamTitle index, const std::string &content);
  void add_match();
  void print_players(std::stringstream &ss) const;
  void print_score(int rank) const;

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
  std::vector<Goal *> goals;
  std::vector<Player *> players;
};

#endif /* __TEAM_HH */
