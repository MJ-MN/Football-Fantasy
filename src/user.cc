#include <string>

#include "user.hh"

using namespace std;

User::User(const string &_username, const string &_password) 
    : username(_username), password(_password) {}

string User::get_name() const {
  return this->username;
}
