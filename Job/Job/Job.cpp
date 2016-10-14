// Job.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"funcForTest.h" //Class, Predicate and funcs that we want to test/use
using namespace std;
//func tests by CppUnit; FuncTest is friend class for StrWor
class FuncTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FuncTest);
	CPPUNIT_TEST(sortingWithoutRegisterTest);
	CPPUNIT_TEST(splitTest);
	CPPUNIT_TEST(removeWordTest);
	CPPUNIT_TEST(toStringTest);
	CPPUNIT_TEST(DeleteWordTest);
	CPPUNIT_TEST_SUITE_END();
	string s1;
	string s2;
	StrWor c1;
	StrWor c2;
public:
	void setUp() {
		const string mas[10] = { "hgfd", "gfd", "gf", "gy", "FgFd", "ytr", "iuytr", "a", "GFDS", "HJK    dss" };
		vector<string> v1(mas, mas + 4);
		vector<string> v2 (mas + 4, mas + 6);
		c1.str = v1;
		c2.str = v2;
		s1 = mas[8];
		s2 = mas[9];
	}
	void tearDown()    {
	}
	void sortingWithoutRegisterTest()    {
		CPPUNIT_ASSERT(true== sortingWithoutRegister(c1, c2));
	}
	void splitTest()    {
		vector<string> s;
		s.push_back("HJK");
		s.push_back("dss");
		CPPUNIT_ASSERT(s == split(s2));
	}
	void removeWordTest(){
		c1.removeWord("gfd");
		c1.removeWord("gf");
		c1.removeWord("hgfd");
		vector<string>v;
		v.push_back("gy");
		StrWor check(v);
		CPPUNIT_ASSERT(c1 == check);
	}
	void toStringTest(){
		string result = c2.toString();
		string answer = "FgFd ytr ";
		CPPUNIT_ASSERT(result == answer);
	}
	void DeleteWordTest(){
		vector<StrWor>c;
		c.push_back(c1);
		c.push_back(c2);
		vector<string> s;
		s.push_back("gf");
		s.push_back("ytr");
		int i = 0;
		for_each(c.begin(), c.end(), DeleteWord(s, i));
		StrWor ck2;
		ck2.str.push_back("FgFd");
		StrWor ck1;
		ck1.str.push_back("hgfd");
		ck1.str.push_back("gfd");
		ck1.str.push_back("gy");
		CPPUNIT_ASSERT(ck2 == c[1] && ck1 == c[0]);
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(FuncTest);
int main()
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();
	system("pause");
	vector <StrWor> sw;
	string v(
		(istreambuf_iterator<char>(
		*(auto_ptr<ifstream>(
		new ifstream("inputWords.txt")
		)).get()
		)),
		istreambuf_iterator<char>()
		); // input string of all wordsToDelete with iterators and string constructor
	vector<string>delWord = split(v); //vector of our wordToDel
	ifstream inStrings("inputStrings.txt");
	string str;
	vector<string> time;
	while (getline(inStrings, str, '\n')) {
		time.push_back(str);
	} //vector<string> of lines
	for_each(time.begin(), time.end(), [&sw](string s){vector<string>time = split(s); 
	sw.push_back(time); }); //fill our contener with for_each from <algorithm> and lambda-func
	int i = 0;
	ofstream fout("output.txt");
	try{
		if (sw.size() > delWord.size()) //check if we have all words that want delete
			throw 1;
		for_each(sw.begin(), sw.end(), DeleteWord(delWord, i)); //delete with predicate; first word from first line and etc;
	}
	catch(int i){
		fout << "Error number " << i << endl;
		return(EXIT_FAILURE);  //finish program with error in output
	}
	sort(sw.begin(), sw.end(), sortingWithoutRegister); //sort without register
	copy(sw.begin(), sw.end(), ostream_iterator <StrWor>(fout)); //to output with iterator
	return (EXIT_SUCCESS);
}

