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
        cout << BAD_REQUEST << endl;
      }
    } else {
      cout << BAD_REQUEST << endl;
    }
  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Football::signup_user(stringstream &ss, const string &username) {
  string password_arg(""), password("");
  ss >> password_arg >> password;
  if (password_arg == "password" && password != "") {
    this->users.push_back(new User(username, password));
    cout << OK << endl;
  } else {
    cout << BAD_REQUEST << endl;
  }
}

void Football::post_login(std::stringstream &ss) {

}

void Football::post_register_admin(std::stringstream &ss) {

}

void Football::post_logout() {

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
