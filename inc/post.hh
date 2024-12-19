#ifndef __POST_HH
#define __POST_HH

#include <sstream>

void post_signup(std::stringstream &ss);
void post_login(std::stringstream &ss);
void post_register_admin(std::stringstream &ss);
void post_logout();
void post_sell_player(std::stringstream &ss);
void post_buy_player(std::stringstream &ss);
void post_close_transfer_window();
void post_open_transfer_window();
void post_pass_week();

#endif /* __POST_HH */
