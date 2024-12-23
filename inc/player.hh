#ifndef __PLAYER_HH
#define __PLAYER_HH

#include <string>
#include <vector>

enum class RoleTitle {
  kNoRole = 0,
  kGoalkeeper,
  kDefender,
  kMidfielder,
  kForward
};

enum class Rank {
  kNoRank = 0,
  kFirstRank,
  kSecondRank
};

class Player {
 public:
  Player();
  Player(std::string _name);
  Player(const Player &) = default;
  Player &operator=(const Player &) = default;

  void set_score(float score);
  std::string get_name();
  RoleTitle get_role();
  float get_score(int week_num);
  void add_match();
  virtual Player *clone() = 0;
  virtual void print_name_score(int week_num, Rank rank = Rank::kNoRank) = 0;
  virtual void print_name_role_score(int rank, int week_num) = 0;

 protected:
  std::string name;
  RoleTitle role;
  std::vector<float> scores;
};

class Goalkeeper : public Player {
 public:
  Goalkeeper();
  Goalkeeper(std::string _name);
  Goalkeeper(const Goalkeeper &) = default;
  Goalkeeper &operator=(const Goalkeeper &) = default;

  Player *clone();
  void print_name_score(int week_num, Rank rank = Rank::kNoRank);
  void print_name_role_score(int rank, int week_num);
};

class Defender : public Player {
 public:
  Defender();
  Defender(std::string _name);
  Defender(const Defender &) = default;
  Defender &operator=(const Defender &) = default;

  Player *clone();
  void print_name_score(int week_num, Rank rank = Rank::kNoRank);
  void print_name_role_score(int rank, int week_num);
};

class Midfielder : public Player {
 public:
  Midfielder();
  Midfielder(std::string _name);
  Midfielder(const Midfielder &) = default;
  Midfielder &operator=(const Midfielder &) = default;

  Player *clone();
  void print_name_score(int week_num, Rank rank = Rank::kNoRank);
  void print_name_role_score(int rank, int week_num);
};

class Forward : public Player {
 public:
  Forward();
  Forward(std::string _name);
  Forward(const Forward &) = default;
  Forward &operator=(const Forward &) = default;

  Player *clone();
  void print_name_score(int week_num, Rank rank = Rank::kNoRank);
  void print_name_role_score(int rank, int week_num);
};

#endif /* __PLAYER_HH */
