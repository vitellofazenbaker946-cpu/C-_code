#define _CRT_SECURE_NO_WARNINGS 1

#include"Hash.h"
#include<set>
#include<unordered_set>

void test_set1()
{
	unordered_set<int> s = { 3,1,6,7,8,2,1,1,5,6,7,6 };
	unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


int main()
{
	test_set1();
	return 0;
}