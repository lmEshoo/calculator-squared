#include<iostream>
#include<string>
using namespace std;

bool die(const string & msg);

int main() {
	double x;
	double function;
	double e = 2.718281828;

	cout<<"Input a value for x in this functions f(x) = (e)^x : ";
	cin>>x;

	function = pow(e, x);


	cout<<"The output for f(x) is: " <<function <<endl;
	system("pause");

}

bool die(const string & msg){
	cerr <<"Fatal Error" <<msg <<endl;
	exit(EXIT_FAILURE);

}