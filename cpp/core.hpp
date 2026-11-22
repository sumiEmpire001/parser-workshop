#pragma once
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cerrno>
namespace lord_sumi {
class Expression {
public:
 static bool evaluate(const char* text,double& out){
  out=0;if(!text)return false;const std::size_t len=std::strlen(text);if(!len||len>128)return false;
  Expression p(text);double value=0;if(!p.expr(value,0))return false;
  p.space();if(*p.s_!='\0'||!std::isfinite(value))return false;out=value;return true;
 }
private:
 explicit Expression(const char* s):s_(s){}
 void space(){while(*s_==' '||*s_=='\t')++s_;}
 bool expr(double& out,int depth){
  if(!term(out,depth))return false;
  for(;;){space();char op=*s_;if(op!='+'&&op!='-')return true;++s_;double rhs;
   if(!term(rhs,depth))return false;out=op=='+'?out+rhs:out-rhs;if(!std::isfinite(out))return false;}
 }
 bool term(double& out,int depth){
  if(!factor(out,depth))return false;
  for(;;){space();char op=*s_;if(op!='*'&&op!='/')return true;++s_;double rhs;
   if(!factor(rhs,depth)||(op=='/'&&rhs==0))return false;
   out=op=='*'?out*rhs:out/rhs;if(!std::isfinite(out))return false;}
 }
 bool factor(double& out,int depth){
  space();if(depth>24)return false;
  if(*s_=='+'||*s_=='-'){char op=*s_++;if(!factor(out,depth+1))return false;if(op=='-')out=-out;return true;}
  if(*s_=='('){++s_;if(!expr(out,depth+1))return false;space();if(*s_!=')')return false;++s_;return true;}
  if(!((*s_>='0'&&*s_<='9')||*s_=='.'))return false;
  errno=0;char* end=nullptr;out=std::strtod(s_,&end);
  if(end==s_||errno==ERANGE||!std::isfinite(out))return false;
  s_=end;return true;
 }
 const char* s_;
};
}