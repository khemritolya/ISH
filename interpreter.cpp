#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <unordered_map>
using namespace std;

struct ISHInt
{
public:
	string str_format;
	int int_format;
	ISHInt() {};
	ISHInt(string input)
	{
		int v = 0;
		for (string::iterator it = input.begin(); it != input.end(); ++it)
		{
			v = v*12 + toDec[*it];
		}
		str_format = input;
		int_format = v;
	}
	ISHInt(int input)
	{
		string v = "";
		int x = input;
		while (x != 0)
		{
			v = toDoz[x % 12] + v;
			x = (int)(x - x % 12) / 12;
		}
		str_format = input == 0 ? "0" : v;
		int_format = input;
	}
	void operator=(ISHInt other)
	{
		this->int_format = other.int_format;
		this->str_format = other.str_format;
	}
private:
	unordered_map<char, int> toDec = {
		{ '0', 0 },
		{ '1', 1 },
		{ '2', 2 },
		{ '3', 3 },
		{ '4', 4 },
		{ '5', 5 },
		{ '6', 6 },
		{ '7', 7 },
		{ '8', 8 },
		{ '9', 9 },
		{ 'a', 10 },
		{ 'b', 11 }
	};
	unordered_map<int, string> toDoz = {
		{ 0, "0" },
		{ 1, "1" },
		{ 2, "2" },
		{ 3, "3" },
		{ 4, "4" },
		{ 5, "5" },
		{ 6, "6" },
		{ 7, "7" },
		{ 8, "8" },
		{ 9, "9" },
		{ 10, "a" },
		{ 11, "b" }
	};
};

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
