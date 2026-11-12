#include "parser.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <string>
int main(){
 using parser_workshop::evaluate;
 assert(std::fabs(evaluate("2 + 3*(4-1)")-11)<1e-12);
 assert(evaluate("-(2+3)") == -5);
 assert(evaluate(".5*8")==4);
 for(const std::string s: {"","1/0","1+","(2+3","1 2","1e999","2**3",std::string(5000,'1'),std::string(100,'(')+"1"+std::string(100,')')}) {
  bool rejected=false;try{(void)evaluate(s);}catch(const std::exception&){rejected=true;}assert(rejected);
 }
}
