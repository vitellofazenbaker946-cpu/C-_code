#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTNode
{
	K _k;
	BSTNode<K>* _left;
	BSTNode<K>* _right;

	BSTNode(const K& key)
		:_k(key)
		, _left(nullptr)
		,_right(nullptr)
	{}
};

template<class K>
class BSTTree
{
	typedef BSTNode<K> Node;

public:
	bool insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{

			if (cur->_k < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_k > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		if (parent->_k < key)
		{
			parent->_right = cur;
		}
		if (parent->_k > key)
		{
			parent->_left = cur;
		}

		return true;
	}

	bool find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_k > key)
			{
				cur = cur->_left;
			}
			else if (cur->_k < key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	

	bool Erase(const K& key)
	{
		if (_root == nullptr)
		{
			return false;
		}

		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{

			if (cur->_k < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_k > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//删除数据
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
					return true;
					
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
						delete cur;
						return true;
					}
				}
				//有两个孩子的时候
				else
				{
					Node* parent = cur;
					Node* replace = cur->_right;
					while (replace->_left)
					{
						parent = replace;
						replace = replace->_left;
					}
					cur->_k = replace->_k;
					if (parent->_left == replace)
					{
						parent->_left = replace->_right;
					}
					else
					{
						parent->_right = replace->_right;
					}
					delete replace;
					return true;
				}
			}
		}
		return false;
	}

	void InOrder()
	{
		_InOrder(_root);//外面套一层，函数内部可以使用 
		cout << endl;
	}
private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_k << " ";
		_InOrder(root->_right); 
	}

private:
	Node* _root = nullptr;
};