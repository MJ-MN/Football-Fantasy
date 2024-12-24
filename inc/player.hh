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

enum class InOrderOf {
  kName = 0,
  kScore
};

class Player {
 public:
  Player();
  Player(const std::string &_name);
  Player(const Player &) = default;
  Player &operator=(const Player &) = default;

  void set_score(float score);
  std::string get_name() const;
  RoleTitle get_role() const;
  float get_score(int week_num) const;
  float get_avg_score() const;
  void add_match();
  virtual Player *clone() const = 0;
  virtual void print_name_score(int week_num,
                                Rank rank = Rank::kNoRank) const = 0;
  virtual void print_name_role_score(int rank) const = 0;

 protected:
  std::string name;
  RoleTitle role;
  std::vector<float> scores;
};

class Goalkeeper : public Player {
 public:
  Goalkeeper();
  Goalkeeper(const std::string &_name);
  Goalkeeper(const Goalkeeper &) = default;
  Goalkeeper &operator=(const Goalkeeper &) = default;

  Player *clone() const;
  void print_name_score(int week_num, Rank rank = Rank::kNoRank) const;
  void print_name_role_score(int rank) const;
};

class Defender : public Player {
 public:
  Defender();
  Defender(const std::string &_name);
  Defender(const Defender &) = default;
  Defender &operator=(const Defender &) = default;

  Player *clone() const;
  void print_name_score(int week_num, Rank rank = Rank::kNoRank) const;
  void print_name_role_score(int rank) const;
};

class Midfielder : public Player {
 public:
  Midfielder();
  Midfielder(const std::string &_name);
  Midfielder(const Midfielder &) = default;
  Midfielder &operator=(const Midfielder &) = default;

  Player *clone() const;
  void print_name_score(int week_num, Rank rank = Rank::kNoRank) const;
  void print_name_role_score(int rank) const;
};

class Forward : public Player {
 public:
  Forward();
  Forward(const std::string &_name);
  Forward(const Forward &) = default;
  Forward &operator=(const Forward &) = default;

  Player *clone() const;
  void print_name_score(int week_num, Rank rank = Rank::kNoRank) const;
  void print_name_role_score(int rank) const;
};

#endif /* __PLAYER_HH */
