#include <iostream>
#include <string>

#include "player.hh"

using namespace std;

Player::Player(string _name) : name(_name) {}

void Player::set_score(float score) {
  this->scores.back() = score;
}

string Player::get_name() {
  return this->name;
}

float Player::get_score(int week_num) {
  return scores[week_num];
}

void Player::add_match() {
  this->scores.push_back(-1.0f);
}
