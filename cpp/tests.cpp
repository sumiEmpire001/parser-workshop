#include "core.hpp"
#include <cassert>
int main(){
 double v;using lord_sumi::Expression;
 assert(Expression::evaluate("2 + 3 * (4 - 1)",v)&&v==11);
 assert(Expression::evaluate("-(2+3)/2",v)&&v==-2.5);
 assert(Expression::evaluate("--3",v)&&v==3);
 assert(!Expression::evaluate("1/0",v));
 assert(!Expression::evaluate("(1+2",v));
 assert(!Expression::evaluate("1+",v));
 assert(!Expression::evaluate("2foo",v));
 assert(!Expression::evaluate("1e999",v));
 assert(!Expression::evaluate(nullptr,v));
 assert(!Expression::evaluate("",v));
}