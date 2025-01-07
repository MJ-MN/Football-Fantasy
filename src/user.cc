#include <iostream>
#include <sstream>
#include <string>

#include "manual.hh"
#include "user.hh"

using namespace std;

User::User() : logged_in(false), players_sold(0) {}

User::User(const string &_username, const string &_password) 
    : logged_in(false), username(_username), password(_password),
      players_sold(0) {}

string User::get_name() const {
  return this->username;
}

string User::get_password() const {
  return this->password;
}

bool User::is_logged_in() const {
  return this->logged_in;
}

void User::login(stringstream &ss) {
  string password_arg(""), password("");
  ss >> password_arg >> password;
  if (password_arg == "password") {
    if (password == this->get_password()) {
      this->logged_in = true;
      cout << kOk << endl;
    } else {
      cout << kPermissionDenied << endl;
    }
  } else {
    cout << kBadRequest << endl;
  }
}

void User::logout() {
  this->logged_in = false;
}

void User::sell_player(const string &name) {
  if (this->players_sold < 2) {
    if (this->team.sell_player(name)) {
      if (this->team.is_completed()) {
        ++players_sold;
      }
      cout << kOk << endl;
    } else {
      cout << kNotFound << endl;
    }
  } else {
    cout << kPermissionDenied << endl;
  }
}

void User::buy_player(Player *player) {
  if (this->team.buy_player(player)) {
    if (!this->team.is_completed() && this->team.is_filled()) {
      this->team.set_completed();
    }
    cout << kOk << endl;
  } else {
    cout << kBadRequest << endl;
  }
}
