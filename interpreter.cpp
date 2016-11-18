#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

vector<string> split(string filename)
{
	ifstream myfile(filename);
	vector<string>* commands = new vector<string>();
	string current_command = "";
	int brace_balance = 0;
	typedef std::istreambuf_iterator<char> CharIter;

	for (CharIter it(myfile); it != CharIter(); ++it)
	{
		switch (*it)
		{
		case '\t': case '\n': case ' ':
			// silly whitespace
			break;
		case '{':
			++brace_balance;
			if (brace_balance != 1) // if it's not the opening {
			{
				current_command += *it;
			}
			break;
		case '}':
			--brace_balance;
			if (brace_balance != 0) // if it's not the closing }
			{
				current_command += *it;
			}
			break;
		case ';':
			if (brace_balance == 0)
			{
				commands->push_back(current_command);
				current_command = "";
			}
			else
			{
				current_command += ';';
			}
			break;
		default:
			current_command += *it;
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
