#include <iostream>
#include <string>

#include "player.hh"

using namespace std;

Player::Player() : score(-1) {}

Player::Player(string _name, float _score)
    : name(_name), score(_score) {}

void Player::set_score(float score) {
  this->score = score;
}

string Player::get_name() {
  return this->name;
}

float Player::get_score() {
  return this->score;
}
