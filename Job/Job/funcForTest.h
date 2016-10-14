#include "stdafx.h"
using namespace std;
class StrWor
{
	vector <string> str;
public:
	friend class FuncTest; //for using private str in tests
	StrWor(){}
	StrWor(vector <string> v) : str(v){}
	void removeWord(string ); // for DeleteWord Predicate; remove element and trash erase trash
	bool operator == (StrWor &); //for testing
	string toString(); //transform vector<string> to string
	friend ostream& operator<<(ostream&, StrWor); //for outputing
	~StrWor(){
		str.clear();
	}
};
vector<string> split(string &); //for transform string to vector<string>
class DeleteWord //for deleting words from lines;
{
	int &i;
	vector<string>word;
public:
	DeleteWord(vector<string>& s, int &i) : word(s), i(i) {}
	void operator () (StrWor &);
};
bool sortingWithoutRegister(StrWor, StrWor); //for sorting line

