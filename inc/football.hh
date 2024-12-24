#ifndef __FOOTBALL_HH
#define __FOOTBALL_HH

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "player.hh"
#include "team.hh"
#include "week.hh"

class Football {
 public:
  Football();
  Football(const Football &) = delete;
  Football &operator=(const Football &) = delete;
  ~Football();

  void extract_teams();
  void extract_weeks();
  Team *find_team_by_name(const std::string &name) const;
  void process_get_method(std::stringstream &ss) const;
  void process_post_method(std::stringstream &ss) const;
  void process_put_method(std::stringstream &ss) const;
  void process_delete_method(std::stringstream &ss) const;

 private:
  std::vector<TeamTitle> extract_teams_title(std::ifstream &ifs) const;
  void extract_teams_data(std::ifstream &ifs,
                          const std::vector<TeamTitle> &teams_title_pos);
  void get_team_of_the_week(std::stringstream &ss) const;
  void print_team_of_the_week(int week_num) const;
  void print_best_players_in_role(RoleTitle role, int week_num) const;
  void get_players(std::stringstream &ss) const;
  void get_league_standings() const;
  void get_users_ranking() const;
  void get_matches_result_league(std::stringstream &ss) const;
  void get_squad(std::stringstream &ss) const;

  std::vector<Team *> teams;
  std::vector<Week *> weeks;
  int last_week;
};

#endif /* __FOOTBALL_HH */
