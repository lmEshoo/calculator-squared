//separate the on value into four parts

#include<iostream>
#include<string>
using namespace std;

bool die(const string & msg);

int main() {
	unsigned x;

	cout<<"Input a 4 digit number: ";
	cin>>x;

	if(!cin) die("input is invalid");
	if(x<0 || x>9999) die("input exceeds the boundaries");


	int answer1 =	static_cast<int>(x/1000);
	int answer2 = static_cast<int>(x/100);
	int answer2a = answer2 - (static_cast<int>(answer2/10)*10);
	int answer3 = static_cast<int>(x/10);
	int answer3a = answer3 - (static_cast<int>(answer3/10)*10);
	int answer4 = x - (static_cast<int>(x/10)*10);

	cout <<"The values seperated for " <<x <<" are " <<endl <<answer1 <<endl <<answer2a <<endl <<answer3a <<endl <<answer4 <<endl;
	system("pause");
}

bool die(const string & msg) {
	cerr <<"Fatal error: " <<msg <<endl;
	exit(EXIT_FAILURE);

}


