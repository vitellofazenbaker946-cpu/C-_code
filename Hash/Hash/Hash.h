#pragma once
#include<vector>
#include<iostream>
using namespace std;


enum State
{
	EXIST,
	EMPTY,
	DELETE
};

template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

//仿函数  和  模板特化string特殊处理
template<class K>
struct HashFanc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

template<>
struct HashFanc<string>
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
			hash *= 131;
		}
		return hash;
	}
};


// 素数表
inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}


//
namespace open_address
{
	//
	template<class K,class V,class Hash = HashFanc<K>>
	class HashTable
	{
	public:
		HashTable()
			:_tables(__stl_next_prime(0))
			, _n(0)
		{}

		bool Insert(const pair<K, V>& kv)
		{
			if (find(kv.first))
			{
				return false;
			}

			// 负载因子 >= 0.7扩容
			if (_n * 10 / _tables.size() >= 7)
			{
				//vector<HashData<K, V>> newtables(_tables.size()*2);
				//for (auto& data : _tables)
				//{
				//	// 旧表的数据映射到新表
				//	if (data._state == EXIST)
				//	{
				//		size_t hash0 = data._kv.first % newtables.size();
				//		// ...
				//	}
				//}

				//_tables.swap(newtables);

				HashTable<K, V, Hash> newht;
				//newht._tables.resize(_tables.size() * 2);
				newht._tables.resize(__stl_next_prime(_tables.size() + 1));

				for (auto& data : _tables)
				{
					if (data._state == EXIST)
					{
						newht.Insert(data._kv);
					}
				}
				_tables.swap(newht._tables);
			}

			Hash hash;
			size_t hash0 = hash(kv.first) % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi]._state == EXIST)
			{
				hashi = (hash0 + i) % _tables.size();
				++i;
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;
			return true;
		}


		bool Erase(const K& key)
		{
			HashData<K, V>* ret = find(key);
			if (ret)
			{
				ret->_state = DELETE;
				return true;
			}
			else
			{
				return false;
			}

		}



		HashData<K,V>* find(const K& key)
		{
			Hash hash;
			size_t hash0 = hash(key) % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi] != EMPTY)
			{
				if (_tables[hashi] == EXIST
					&& _tables[hashi] == key)
				{
					return &_tables[hashi];
				}
				hashi = (hash0 + i) % _tables.size();
				++i;
			}
			return nullptr;
		}
		


	private:
		vector<HashData<K, V>> _tables;
		size_t _n;// 记录数据个数
	};
}
