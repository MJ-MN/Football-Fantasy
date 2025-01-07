#include <iostream>
#include <string>

#include "fantasy_team.hh"
#include "manual.hh"

using namespace std;

FantasyTeam::FantasyTeam()
    : goalkeeper(NULL), defender1(NULL), defender2(NULL),
      midfielder(NULL), forward(NULL), completed(false) {}

void FantasyTeam::set_completed() {
  this->completed = true;
}

bool FantasyTeam::is_completed() const {
  return this->completed;
}

bool FantasyTeam::is_filled() const {
  if (this->goalkeeper != NULL && this->defender1 != NULL &&
      this->defender2 != NULL && this->midfielder != NULL &&
      this->forward != NULL) {
    return true;
  }
  return false;
}

bool FantasyTeam::sell_player(const string &name) {
  if (this->goalkeeper->get_name() == name) {
    this->goalkeeper = NULL;
  } else if (this->defender1->get_name() == name) {
    this->defender1 = NULL;
  } else if (this->defender2->get_name() == name) {
    this->defender2 = NULL;
  } else if (this->midfielder->get_name() == name) {
    this->midfielder = NULL;
  } else if (this->forward->get_name() == name) {
    this->forward = NULL;
  } else {
    return false;
  }
  return true;
}

bool FantasyTeam::buy_player(Player *player) {
  bool ret_flag = false;
  switch (player->get_role()) {
    case RoleTitle::kGoalkeeper:
      if (this->goalkeeper == NULL) {
        this->goalkeeper = player;
        ret_flag = true;
      }
      break;
    case RoleTitle::kDefender:
      if (this->defender1 == NULL && this->defender2 != player) {
        this->defender1 = player;
        ret_flag = true;
      } else if (this->defender2 == NULL && this->defender1 != player) {
        this->defender2 = player;
        ret_flag = true;
      }
      break;
    case RoleTitle::kMidfielder:
      if (this->midfielder == NULL) {
        this->midfielder = player;
        ret_flag = true;
      }
      break;
    case RoleTitle::kForward:
      if (this->forward == NULL) {
        this->forward = player;
        ret_flag = true;
      }
      break;
    default:
      break;
  }
  return ret_flag;
}
