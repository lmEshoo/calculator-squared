//Lini Mestar
//Calculator_0
//Using the switch statment

#include <iostream>
#include <sstream>
using namespace std;

string getLine();

void error(){
    cout <<"Pretend I'm handling this error" <<endl;
    exit( EXIT_FAILURE );
}   //  error

int main(){
    for(;;){    
        double x0, x1;
        double answer = 0;
        char op;
        istringstream sin( getLine() );
        if( !(sin >>x0 >>op >>x1) )  error();
        switch( op ){
          case '+': answer = x0 + x1; break;
          case '-': answer = x0 - x1; break;
          default: cout <<"get serious" <<endl; break;
        }
        cout <<answer <<endl;
    }
}   //  main

string getLine(){
    cout <<">";
    string result;
    for(  char c;  (c = static_cast<char>(getchar())) != '\n';  )
        result += c;
    return result;
}   //  getLine

    