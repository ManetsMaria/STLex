#include "stdafx.h"
#include "funcForTest.h"
using namespace std;
void StrWor::removeWord(string word)
{
	str.erase(remove(str.begin(), str.end(), word), str.end());
}
string StrWor::toString()
{
	string a;
	for_each(str.begin(), str.end(), [&a](string b) {a = a + b + " "; });
	return a;
}
ostream& operator << (ostream& os, StrWor dt)
{
	os << dt.toString() << endl;
	return os;
}
vector<string> split(string &s)
{
	stringstream ss(s);
	vector <string> VecStr;
	while (ss >> s)
		VecStr.push_back(s);
	return VecStr;
}
void DeleteWord::operator () (StrWor & s)
{
	s.removeWord(word[i]);
	i++;
}
bool sortingWithoutRegister(StrWor s1, StrWor s2)
{
	string a = s1.toString(),
		b = s2.toString();
	transform(a.begin(), a.end(), a.begin(), toupper);
	transform(b.begin(), b.end(), b.begin(), toupper);
	return a > b;
}
bool StrWor::operator==(StrWor& s)
{
	return (this->toString() == s.toString());
}


