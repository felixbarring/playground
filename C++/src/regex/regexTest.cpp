   
#include <iostream>
#include <regex>

using namespace std;

int main() {
 string log(R"(
        Speed:	366
        Mass:	35
        Speed:	378
        Mass:	32
        Speed:	400
	    Mass:	30)");

//  std::regex r(R"(Speed:\t\d*)");
  std::regex r("\\S+");
  std::smatch sm;
  while(regex_search(log, sm, r)) {
    std::cout << sm.str() << '\n';
    log = sm.suffix();
  }

}
