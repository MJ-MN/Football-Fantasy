#include <iostream>
#include <string>

#include "player.hh"

using namespace std;

Player::Player() : role(RoleTitle::kNoRole) {}

Player::Player(const string &_name) : name(_name), role(RoleTitle::kNoRole) {}

void Player::set_score(float score) {
  this->scores.back() = score;
}

string Player::get_name() const {
  return this->name;
}

RoleTitle Player::get_role() const {
  return this->role;
}

float Player::get_score(int week_num) const {
  return scores[week_num];
}

void Player::add_match() {
  this->scores.push_back(-1.0f);
}

Goalkeeper::Goalkeeper() : Player() {
  this->role = RoleTitle::kGoalkeeper;
}

Goalkeeper::Goalkeeper(const string &_name) : Player(_name) {
  this->role = RoleTitle::kGoalkeeper;
}

Player *Goalkeeper::clone() const {
  return new Goalkeeper(*this);
}

void Goalkeeper::print_name_score(int week_num, Rank rank) const {
  if (rank == Rank::kNoRank) {
    cout << "Goalkeeper: " << this->name;
  } else if (rank == Rank::kFirstRank) {
    cout << "Goalkeeper 1: " << this->name;
  } else {
    cout << "Goalkeeper 2: " << this->name;
  }
  cout << " | score: " << this->scores[week_num] << endl;
}

void Goalkeeper::print_name_role_score(int rank, int week_num) const {
  cout << rank << ". name: " << this->name;
  cout << " | role: gk";
  cout << " | score: " << this->scores[week_num] << endl;
}

Player *Defender::clone() const {
  return new Defender(*this);
}

Defender::Defender() : Player() {
  this->role = RoleTitle::kDefender;
}

Defender::Defender(const string &_name) : Player(_name) {
  this->role = RoleTitle::kDefender;
}

void Defender::print_name_score(int week_num, Rank rank) const {
  if (rank == Rank::kNoRank) {
    cout << "Defender: " << this->name;
  } else if (rank == Rank::kFirstRank) {
    cout << "Defender 1: " << this->name;
  } else {
    cout << "Defender 2: " << this->name;
  }
  cout << " | score: " << this->scores[week_num] << endl;
}

void Defender::print_name_role_score(int rank, int week_num) const {
  cout << rank << ". name: " << this->name;
  cout << " | role: df";
  cout << " | score: " << this->scores[week_num] << endl;
}

Player *Midfielder::clone() const {
  return new Midfielder(*this);
}

Midfielder::Midfielder() : Player() {
  this->role = RoleTitle::kMidfielder;
}

Midfielder::Midfielder(const string &_name) : Player(_name) {
  this->role = RoleTitle::kMidfielder;
}

void Midfielder::print_name_score(int week_num, Rank rank) const {
  if (rank == Rank::kNoRank) {
    cout << "Midfielder: " << this->name;
  } else if (rank == Rank::kFirstRank) {
    cout << "Midfielder 1: " << this->name;
  } else {
    cout << "Midfielder 2: " << this->name;
  }
  cout << " | score: " << this->scores[week_num] << endl;
}

void Midfielder::print_name_role_score(int rank, int week_num) const {
  cout << rank << ". name: " << this->name;
  cout << " | role: md";
  cout << " | score: " << this->scores[week_num] << endl;
}

Player *Forward::clone() const {
  return new Forward(*this);
}

Forward::Forward() : Player() {
  this->role = RoleTitle::kForward;
}

Forward::Forward(const string &_name) : Player(_name) {
  this->role = RoleTitle::kForward;
}

void Forward::print_name_score(int week_num, Rank rank) const {
  if (rank == Rank::kNoRank) {
    cout << "Forward: " << this->name;
  } else if (rank == Rank::kFirstRank) {
    cout << "Forward 1: " << this->name;
  } else {
    cout << "Forward 2: " << this->name;
  }
  cout << " | score: " << this->scores[week_num] << endl;
}

void Forward::print_name_role_score(int rank, int week_num) const {
  cout << rank << ". name: " << this->name;
  cout << " | role: fw";
  cout << " | score: " << this->scores[week_num] << endl;
}
