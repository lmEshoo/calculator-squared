#include<iostream>
#include<string>
using namespace std;

bool die(const string & msg);

int main() {
	double x;
	double y;
	double z;
	double t;
	double p;
	double r;
	double w;
	double q;
	double average;

	cout<<"Input any 8 quiz scores: ";
	cin>>x >>y >>z >>t >>p >>r >>w >>q;

	if(!cin) die("input is invalid");

	if(x<0 || x>1e9) die("Input exceeds the limitations");

	average = (x + y + z + t + p + r + w + q)/8 ; 

	cout<<"The average test score is " <<average <<endl;




}

bool die(const string & msg){
	cerr <<"Fatal Error" <<msg <<endl;
	exit(EXIT_FAILURE);
}
