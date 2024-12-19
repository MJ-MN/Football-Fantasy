#ifndef __FOOTBALL_HPP
#define __FOOTBALL_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
  Team *find_team_by_name(std::string name);
  void process_get_method(std::stringstream &ss);
  void get_team_of_the_week(std::stringstream &ss);
  void print_team_of_the_week(int week_num);
  void get_players(std::stringstream &ss);
  void get_league_standings();
  void get_users_ranking();
  void get_matches_result_league(std::stringstream &ss);
  void get_squad(std::stringstream &ss);
  void process_post_method(std::stringstream &ss);
  void process_put_method(std::stringstream &ss);
  void process_delete_method(std::stringstream &ss);

 private:
  std::vector<TeamTitle> extract_teams_title(std::ifstream &ifs);
  void extract_teams_data(std::ifstream &ifs,
                          const std::vector<TeamTitle> &teams_title_pos);

  std::vector<Team *> teams;
  std::vector<Week *> weeks;
  int last_week;
};

#endif /* __FOOTBALL_HPP */
