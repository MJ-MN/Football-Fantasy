#ifndef __FOOTBALL_HH
#define __FOOTBALL_HH

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "player.hh"
#include "team.hh"
#include "user.hh"
#include "week.hh"

const std::string kAdminUsername = "admin";
const std::string kAdminPassword = "123456";

class Football {
 public:
  Football();
  Football(const Football &) = delete;
  Football &operator=(const Football &) = delete;
  ~Football();

  void extract_teams();
  void extract_weeks();
  Team *find_team_by_name(const std::string &name) const;
  Player *find_player_by_name(const std::string &name) const;
  User *find_user_by_name(const std::string &name) const;
  void process_get_method(std::stringstream &ss) const;
  void process_post_method(std::stringstream &ss);
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
  void print_league_standings() const;
  void get_users_ranking() const;
  void get_matches_result_league(std::stringstream &ss) const;
  void print_matches_result_league(int week_num) const;
  void get_squad(std::stringstream &ss) const;
  void post_signup(std::stringstream &ss);
  void signup_user(std::stringstream &ss, const std::string &name);
  void post_login(std::stringstream &ss);
  void post_register_admin(std::stringstream &ss);
  void post_logout();
  void post_sell_player(std::stringstream &ss);
  void post_buy_player(std::stringstream &ss);
  void buy_player(User *user, const std::string &name);
  void post_close_transfer_window();
  void post_open_transfer_window();
  void post_pass_week();
  User *who_is_logged_in() const;
  bool is_player_available(const Player *player) const;
  bool player_has_red_card(const Player *player) const;
  bool player_has_three_yellow_cards(const Player *player) const;
  bool player_is_injured(const Player *player) const;

  User *admin;
  std::vector<Team *> teams;
  std::vector<Week *> weeks;
  std::vector<User *> users;
  int last_week;
  bool transfer_window_is_open;
};

#endif /* __FOOTBALL_HH */
