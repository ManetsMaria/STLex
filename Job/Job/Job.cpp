// Job.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
ofstream fout("output.txt");
class StrWor{
	vector <string> str;
public:
	StrWor(vector <string> v) : str(v){}
	void removeWord(string word)
	{
		str.erase(remove(str.begin(), str.end(), word), str.end());
	}
		string toString()
	{
		string a;
		for_each(str.begin(), str.end(), [&a](string b) {a=a+b+" "; });
		return a;
	}
	friend ostream& operator<<(ostream& os,  StrWor dt)
	{
		os << dt.toString()<<endl;
		return os;
	}
};
vector<string> split(string &s)
{
	stringstream ss(s); 
	vector <string> VecStr;
	while (ss >> s)
		VecStr.push_back(s);
	return VecStr;
}
class DeleteWord
{
	int &i;
	vector<string>word;
public:
	DeleteWord(vector<string>& s, int &i) : word(s), i(i) {}
	void operator () (StrWor & s)
	{
		s.removeWord(word[i]);
		i++;
	}
};
bool sortingWithoutRegister(StrWor s1, StrWor s2)
{
	string a=s1.toString(),
		b=s2.toString();
	transform(a.begin(), a.end(), a.begin(), toupper);
	transform(b.begin(), b.end(), b.begin(), toupper);
	return a > b;
}
int main()
{
	vector <StrWor> sw;
	string v(
		(istreambuf_iterator<char>(
		*(auto_ptr<ifstream>(
		new ifstream("inputWords.txt")
		)).get()
		)),
		istreambuf_iterator<char>()
		);
	vector<string>delWord = split(v);
	ifstream inStrings("inputStrings.txt");
	string str;
	vector<string> time;
	while (getline(inStrings, str, '\n')) {
		time.push_back(str);
	}
	for_each(time.begin(), time.end(), [&sw](string s){vector<string>time = split(s);
	sw.push_back(time); });
	int i = 0;
	try{
		if (sw.size() > delWord.size())
			throw 1;
		for_each(sw.begin(), sw.end(), DeleteWord(delWord, i));
	}
	catch(int i){
		fout << "Error number " << i << endl;;
	}
	sort(sw.begin(), sw.end(), sortingWithoutRegister);
	copy(sw.begin(), sw.end(), ostream_iterator <StrWor>(fout));
	return 0;
}

