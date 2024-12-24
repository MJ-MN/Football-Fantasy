#ifndef __MANUAL_HH
#define __MANUAL_HH

#include <string>
#include <utility>
#include <vector>

#include "player.hh"

const std::string OK = "OK";
const std::string BAD_REQUEST = "Bad Request";
const std::string PERMISSION_DENIED = "Permission Denied";
const std::string NOT_FOUND = "Not Found";
const std::string EMPTY = "Empty";

std::pair<Player *, Player *> find_two_best_players(
    const std::vector<Player *> &players, int week_num);
std::string replace_underscore(std::string str);

#endif /* __MANUAL_HH */
