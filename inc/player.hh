#ifndef __PLAYER_HH
#define __PLAYER_HH

#include <string>
#include <vector>

enum class RoleTitle {
  kGoalkeeper = 1,
  kDefender,
  kMidfielder,
  kForward
};

class Player {
 public:
  Player() = default;
  Player(std::string _name);
  Player(const Player &) = default;
  Player &operator=(const Player &) = default;

  void set_score(float score);
  std::string get_name();
  float get_score(int week_num);
  void add_match();

 private:
  std::string name;
  std::vector<float> scores;
};

#endif /* __PLAYER_HH */
