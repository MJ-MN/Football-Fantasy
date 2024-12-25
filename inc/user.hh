#ifndef __USER_HH
#define __USER_HH

#include <string>

class User {
 public:
  User() = default;
  User(const std::string &_username, const std::string &_password);
  User(const User &user) = default;
  User &operator=(const User &user) = default;
  ~User() = default;

  std::string get_name() const;

 private:
  std::string username;
  std::string password; 
};

#endif /* __USER_HH */
