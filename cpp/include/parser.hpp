#pragma once
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <string>
namespace parser_workshop {
class Parser {
 const std::string& s; std::size_t p=0; unsigned depth=0;
 void ws(){while(p<s.size()&&std::isspace(static_cast<unsigned char>(s[p])))++p;}
 bool eat(char c){ws();if(p<s.size()&&s[p]==c){++p;return true;}return false;}
 double factor(){ws();if(++depth>64)throw std::invalid_argument("expression nesting too deep");
 double v;
 if(eat('+'))v=factor();
 else if(eat('-'))v=-factor();
 else if(eat('(')){v=expr();if(!eat(')'))throw std::invalid_argument("missing )");}
 else {ws();const char* begin=s.c_str()+p;char* end=nullptr;
 v=std::strtod(begin,&end);if(end==begin||!std::isdigit(static_cast<unsigned char>(*begin))&&*begin!='.')throw std::invalid_argument("expected number");
 p=static_cast<std::size_t>(end-s.c_str());}
 --depth;if(!std::isfinite(v))throw std::invalid_argument("nonfinite result");return v;}
 double term(){double v=factor();for(;;){if(eat('*'))v*=factor();else if(eat('/')){double d=factor();if(d==0)throw std::domain_error("division by zero");v/=d;}else break;if(!std::isfinite(v))throw std::invalid_argument("nonfinite result");}return v;}
 double expr(){double v=term();for(;;){if(eat('+'))v+=term();else if(eat('-'))v-=term();else break;if(!std::isfinite(v))throw std::invalid_argument("nonfinite result");}return v;}
 public:explicit Parser(const std::string& text):s(text){if(s.size()>4096)throw std::invalid_argument("expression too long");}
 double evaluate(){double v=expr();ws();if(p!=s.size())throw std::invalid_argument("unexpected token");return v;}
};
inline double evaluate(const std::string& s){return Parser(s).evaluate();}
}
