#include"vector.h"
namespace Jianyi
{
	void text01()
	{
		vector<int> v;
		v.pushback(1);
		v.pushback(2);
		v.pushback(3);
		v.pushback(4);
		v.pushback(5);
		/*for (operator i = v.begin(); i < v.end(); ++i)
		{
			cout << *(_start + i) << " ";
		}
		cout << endl;*/

		for (size_t n = 0; n < v.size(); ++n)
		{
			cout << v[n] << " ";
		}
		cout << endl;

		Print_Vector(v);

		v.insert(v.begin() + 2, 30);
		Print_Vector(v);

	}

	void text02()
	{
		vector<int> v;
		v.pushback(1);
		v.pushback(2);
		v.pushback(3);
		v.pushback(4);
		v.Print_Vector(v);
		int x;
		cin >> x;
		auto pos = find(v.begin(), v.end(), x);
		if (pos != v.end())//如果找不到就都是默认返回end，因为不可能在end是找得到的值，他都是最后一个空位置
		{
			v.insert(pos, 40);
		}
		Print_Vector(v);

		v.erase(2);
		Print_Vector(v);
	}

	void text03()
	{

		vector<int> v;
		v.pushback(1);
		v.pushback(2);
		v.pushback(3);
		v.pushback(4);
		v.pushback(5);
		v.pushback(6);
		Print_Vector(v);


		//删除所有的偶数
		//这是错误的，在删除操作之后iterator失效，不许再用了
		/*auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				v.erase(it);
			}
			++it;
		}*/



		//这是正确的，不要跳过
		auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
			{
				++it;
			}
		}
	}


	void text04()
	{
		int i = int();
		int j = int(1);
		int k(2);

	}

	void text05()
	{
		vector<string> v;
		v.pushback("11111111");
		v.pushback("11111111");
		v.pushback("11111111");
		v.pushback("11111111");
		v.pushback("11111111");
		v.pushback("11111111");
		Print_Vector(v);

	}






}

