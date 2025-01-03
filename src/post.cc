#include <iostream>
#include <sstream>

#include "football.hh"
#include "manual.hh"

using namespace std;

void Football::post_signup(std::stringstream &ss) {
  string qm(""), team_name_arg(""), team_name("");
  ss >> qm >> team_name_arg >> team_name;
  if (qm == "?" && team_name_arg != "" && team_name != "") {
    if (team_name_arg == "team_name") {
      if (this->find_user_by_name(team_name) == NULL) {
        this->signup_user(ss, team_name);
      } else {
        cout << kBadRequest << endl;
      }
    } else {
      cout << kBadRequest << endl;
    }
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::signup_user(stringstream &ss, const string &username) {
  string password_arg(""), password("");
  ss >> password_arg >> password;
  if (password_arg == "password" && password != "") {
    this->users.push_back(new User(username, password));
    cout << kOk << endl;
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::post_login(std::stringstream &ss) {
  string qm(""), team_name_arg(""), team_name("");
  ss >> qm >> team_name_arg >> team_name;
  if (qm == "?" && team_name_arg != "" && team_name != "" &&
      this->who_is_logged_in() == NULL) {
    if (team_name_arg == "team_name") {
      User *user = this->find_user_by_name(team_name);
      if (user != NULL) {
        user->login(ss);
      } else {
        cout << kNotFound << endl;
      }
    } else {
      cout << kBadRequest << endl;
    }
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::post_register_admin(std::stringstream &ss) {
  string qm(""), username_arg(""), username("");
  ss >> qm >> username_arg >> username;
  if (qm == "?" && username_arg != "" && username != "" &&
      this->who_is_logged_in() == NULL) {
    if (username_arg == "username") {
      if (username == this->admin->get_name()) {
        this->admin->login(ss);
      } else {
        cout << kBadRequest << endl;
      }
    } else {
      cout << kBadRequest << endl;
    }
  } else {
    cout << kBadRequest << endl;
  }
}

void Football::post_logout() {
  User *user = this->who_is_logged_in();
  if (user != NULL) {
    user->logout();
  }
  cout << kOk << endl;
}

void Football::post_sell_player(std::stringstream &ss) {

}

void Football::post_buy_player(std::stringstream &ss) {

}

void Football::post_close_transfer_window() {

}

void Football::post_open_transfer_window() {

}

void Football::post_pass_week() {

}
