#define _CRT_SECURE_NO_WARNINGS
#include"BinarySearch.h"
int main()
{
	BSTTree<int> t;
	int a[] = { 8,3,1,10,1,6,4,7,14,13 };
	for (auto e : a)
	{
		t.insert(e);
	}

	t.InOrder();
	t.Erase(14);
	t.InOrder();
	return 0;
}