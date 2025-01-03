#ifndef __MANUAL_HH
#define __MANUAL_HH

#include <string>
#include <utility>
#include <vector>

#include "player.hh"
#include "team.hh"

const std::string kOk = "OK";
const std::string kBadRequest = "Bad Request";
const std::string kPermissionDenied = "Permission Denied";
const std::string kNotFound = "Not Found";
const std::string kEmpty = "Empty";

std::pair<Player *, Player *> find_two_best_players(
    const std::vector<Player *> &players, int week_num);
std::string replace_underscore(std::string str);
bool standings_comparator(Team *team1, Team *team2);

#endif /* __MANUAL_HH */
