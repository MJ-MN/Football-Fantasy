#include <fstream>
#include <iostream>
#include <sstream>

#include "football.hh"
#include "main.hh"
#include "manual.hh"

using namespace std;

int main() {
  Football football;
  football.extract_teams();
  football.extract_weeks();

  string line("");
  while (getline(cin, line)) {
    stringstream line_ss(line);
    string method("");
    line_ss >> method;
    if (method == "GET") {
      football.process_get_method(line_ss);
    } else if (method == "POST") {
      football.process_post_method(line_ss);
    } else if (method == "PUT") {

    } else if (method == "DELETE") {

    } else {
      cout << kBadRequest << endl;
    }
  }
  return 0;
}
