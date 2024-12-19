#ifndef __PLAYER_HH
#define __PLAYER_HH

#include <string>

enum class RoleTitle {
  kGoalkeeper = 1,
  kDefender,
  kMidfielder,
  kForward
};

class Player {
 public:
  Player();
  Player(std::string _name, float _score = -1);
  Player(const Player &) = default;
  Player &operator=(const Player &) = default;

  void set_score(float score);
  std::string get_name();
  float get_score();

 private:
  std::string name;
  float score;
};

#endif /* __PLAYER_HH */
