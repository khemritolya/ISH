#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() 
{
	string line;
	string program;
	
	ifstream myfile ("test.txt");
	while (getline(myfile,line)) 
	{
		program += line;
	}
	
	cout << program << endl;
	myfile.close();
}
