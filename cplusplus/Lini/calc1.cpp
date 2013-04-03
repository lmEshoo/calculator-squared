//Lini Mestar
//Calculator_0
//Using the pointer to function

#include <iostream>
#include <sstream>
using namespace std;

string getLine();

void error(){
    cout <<"Pretend I'm handling this error" <<endl;
    exit( EXIT_FAILURE );
}   //  error

double add     ( double x, double y ) {return x+y;}
double subtract( double x, double y ) {return x-y;}
double logBase ( double base, double value ) {return log(value) / log(base);}

#define OPTYPE string

struct Operation{
    OPTYPE name;
    double (*func)( double x, double y );
};  //  struct Operation

const Operation TABLE[] = {
    {"+"  , add     },  //  precedence, associativity, arity (binary unary)
                        //  documentation, acceptable operand range, illegal result
    {"&"  , add     },
    {"-"  , subtract},
    {"log", logBase }
};  //  TABLE

unsigned find( const OPTYPE & op ){
    for(  unsigned i = 0;  i < sizeof(TABLE)/sizeof(TABLE[0]);  i++  )
        if( TABLE[i].name == op )  return i;
    return UINT_MAX;
}   //  find

int main(){
    for(;;){
        double x0, x1;
        //double answer = 0;
        OPTYPE op;
        istringstream sin( getLine() );
        if( !(sin >>x0 >>op >>x1) )  error();
        unsigned opPos = find( op );
        if( opPos == UINT_MAX ){
            cout <<"crud" <<endl;
        }else{
            cout <<TABLE[opPos].func( x0, x1 ) <<endl;
        }
    }
}   //  main

string getLine(){
    cout <<">";
    string result;
    for(  char c;  (c = static_cast<char>(getchar())) != '\n';  )
        result += c;
    return result;
}   //  getLine

    