#include <iostream>
#include <sstream>
#include <string>

#include "manual.hh"
#include "user.hh"

using namespace std;

User::User() : logged_in(false) {}

User::User(const string &_username, const string &_password) 
    : logged_in(false), username(_username), password(_password) {}

string User::get_name() const {
  return this->username;
}

string User::get_password() const {
  return this->password;
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
