#include<iostream>
#include<string>
#include<cassert>
using namespace std;

const double DELTA = 1e-6;
bool die(const string & msg);

int main(){
	double a,b,c,d;
	cout<<"Input 4 sides of a quadrallatel: " <<endl;
	cin>>a >>b >>c >>d;
	
	if(!cin) die("input is invalid");
	if(a< DELTA || b<DELTA || c<DELTA || d<DELTA || a>=b+c+d-DELTA || b>=a+c+d-DELTA || c>=b+a+d-DELTA || d>=b+c+a-DELTA
	){
	cout<<"We got no truck with such quadrilaterals here" <<endl;
	return 0;
	}
	
	cout<<"Good, we got a quad" <<endl;

	if(abs(a-b) < DELTA && abs(a-c)<DELTA && abs(a-d)<DELTA)
		cout<<"It's a rhombus" <<endl;
	else
		cout<<"Not a rhombus" <<endl;

	if(a==b && a==c && a==d && c==d && b==d && b==c)
		cout<<"It's a square" <<endl;
	else
		cout<<"Not a square" <<endl;

	system("pause");
}



bool die(const string & msg){
	cerr <<endl <<"Fatal Error:" <<msg <<endl;
	exit(EXIT_FAILURE);
}