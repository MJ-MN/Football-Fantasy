#ifndef __USER_HH
#define __USER_HH

#include <sstream>
#include <string>

class User {
 public:
  User();
  User(const std::string &_username, const std::string &_password);
  User(const User &user) = default;
  User &operator=(const User &user) = default;
  ~User() = default;

  std::string get_name() const;
  std::string get_password() const;
  bool is_logged_in() const;
  void login(std::stringstream &ss);
  void logout();

 private:
  bool logged_in;
  std::string username;
  std::string password; 
};

#endif /* __USER_HH */
