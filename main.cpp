#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

const vector<string>& split(string filename)
{
	/*
	takes filename to open
	returns a vector of commands, ignoring white space and grouping based on {}
	*/
	ifstream myfile(filename);
	vector<string>* commands = new vector<string>();
	string current_command = "";
	int brace_balance;
	typedef std::istream_iterator<char> CharIter;

	for (CharIter it(myfile); it != CharIter(); ++it)
	{
		switch (*it)
		{
		case ' ': case '\t': case '\n': break;
		case '{':
			brace_balance = 1;
			++it;
			while (brace_balance > 0 && it != CharIter())
			{
				if (*it == '{') ++brace_balance;
				if (*it == '}') --brace_balance;
				if (brace_balance > 0)
				{
					current_command = current_command + *it;
					++it;
				}
			}
		case ';':
			commands->push_back(current_command);
			current_command = "";
			break;
		default:
			current_command = current_command + *it;
			break;
		}
	}
	myfile.close();
	return *commands;
}

int main()
{
	vector<string> commands = split("file");
	cout << "Commands read as follows: (in order of execution)\n";
	for (vector<string>::const_iterator i = commands.begin(); i != commands.end(); ++i) cout << "  - " << *i << endl;
}
