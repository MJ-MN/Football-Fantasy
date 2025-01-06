#include <iostream>
#include <string>

#include "fantasy_team.hh"
#include "manual.hh"

using namespace std;

FantasyTeam::FantasyTeam()
    : goalkeeper(NULL), defender1(NULL), defender2(NULL),
      midfielder(NULL), forward(NULL) {}

bool FantasyTeam::is_completed() const {
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
