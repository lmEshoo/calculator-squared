#include<iostream>
#include<string>
using namespace std;

bool die(const string & msg);

int main(){
	unsigned x,y;
	char calc;
	cout<<" Input 2 values that you want to either add, subtract, divide, multiply or a value to a power with the proper expression in between: " <<endl;
	cin>>x >>calc >>y || die("invalid input");
	
	double solution = 0;
	
	switch(calc){
	case '+':
			solution = x + y;
			break;

	case '-':
			solution = x - y;
			break;

	case '/':
		if(y==0) die("Can't divide by 0, it is illegal in all 50 states");
			solution = x / y;
			break;

	case '*':
			solution = x * y;
			break;

	case'^':
		solution = pow(x,y);
			break;

	default: 
		die("No such operation");
	}

	cout <<" " <<x <<" " <<calc <<" " <<y <<" = " <<solution <<endl;

}

bool die(const string & msg){
	cerr <<"Fatal Error:" <<msg <<endl;
	exit(EXIT_FAILURE);
}