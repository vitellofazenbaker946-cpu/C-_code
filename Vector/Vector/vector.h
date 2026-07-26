#pragma once
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

namespace Jianyi
{

	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T*  const_iterator;
		vector()
		{ }

		vector(const vector<T>& v)
		{
			for (auto e : v)
			{
				pushback(e);
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				pushback(*first);
				++first;
			}
		}

		vector(size_t n, const T& val = T())
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				pushback(val);
			}

		}

		~vector()
		{
			if (_start != nullptr)
			{
				delete[]_start;
				_start = _finish = _end_of_storage = nullptr;

			}
		}
		void clear()
		{
			_finish = _start;
		}
		/*vector<T>& operator=(const vector<T>& v)
		{
			if (*this != v)
			{
				clear();
				reserve(v.size());
				for (auto e : v)
				{
					pushback(e);
				}
			}
			return *this;
		}*/
		// 注释掉的版本
/*
vector<T>& operator=(const vector<T>& v)
{
	if (*this != v)   // ← 这里错了
	{
		clear();
		reserve(v.size());
		for (auto e : v)
			pushback(e);
	}
	return *this;
}
*/

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		vector<T>& operator=(const vector<T> v)//这个不可是引用，要是一个深拷贝
		{
			swap(v);
			return *this;
		}

		T& operator[](size_t n)
		{
			assert(n < size());
			return *(_start + n);
		}
		const T& operator[](size_t n)const
		{
			assert(n < size());
			return *(_start + n);
		}

		iterator begin()
		{
			return _start;
		}
		const_iterator begin()const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}
		const_iterator end()const
		{
			return _finish;
		}

		void reserve(size_t n)
		{
			size_t old_size = size();
			if (n > capacity())
			{
				T* tmp = new T[n];
				//memcpy(tmp, _start, size()*sizeof(T));
				for (size_t i = 0; i < old_size; ++i)
				{
					tmp[i] = _start[i];
				}
				 
				delete[] _start;
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + n;
			}
		}

		size_t capacity()
		{
			return _end_of_storage - _start;
		}
		const size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		size_t size()
		{
			return _finish - _start;
		}
		const size_t size()const
		{
			return _finish - _start;
		}

		void pushback(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//如果不够就扩容
			}
			*_finish = x;
			++_finish;
		}
		bool Empty()
		{
			return _start == _finish;
		}
		void popback()
		{
			assert(Empty());
			--_finish;
		}
		

		//void insert(iterator pos, const T& x)
		//{
		//	if (_finish == _end_of_storage)
		//	{
		//		reserve(capacity() == 0 ? 4 : capacity() * 2);
		//		//如果不够就扩容
		//	}
		//	for (iterator end = end(); end >= pos; --end)
		//	{
		//		_start[end + 1] = _start[end];
		//	}
		//	*pos = x;
		//	++_finish;
		//}

		void insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//如果不够就扩容
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
		}

		void erase(size_t pos)
		{
			assert(pos < size());
			for (size_t i = pos; i < size();++i)
			{
				_start[i] = _start[i + 1];
			}
			--_finish;

		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos <_finish);
			iterator it = pos + 1;
			while (it != end())
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			return pos;
		}

		void resize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

	
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;

	};
	template<class T>
	void Print_Vector(const vector<T>& v)
	{
		vector<T>::const_iterator it = v.begin();
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << *(it + i) << " ";
		}
		cout << endl;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}


	
	void text01();
	void text02();
	void text03();
	void text04();
	void text05();
}
