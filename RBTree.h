#pragma once
#include<iostream>
#include <utility>

using namespace std;
enum Colour
{
	RED,
	BLACK
};

//key value为结构实现
template<class K,class V>
struct RBTreeNode
{
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;

	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		//, _col(RED);
	{ }
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;

public:

	bool Insert(const pair<K, V>& kv)
	{
		//一个if就可以，不用在一个else
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;;
			return true;
		}

		//向下寻找插入的位置
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)//当cur为nullptr退出，但是有parent，依旧可以知道插入到哪里
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		//定好cur的位置并且链接好
		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		//都在while里面便于循环到底 
		while(parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//关键看uncle
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					//uncle为红色时候
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//当uncle不存在或者为黑色时候
					if (cur = parent->_left)
					{
						//右旋
						RightRotate(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						LeftRotate(parent);
						RightRotate(grandfather);
						cur->_col = BLACK;
					    grandfather->_col = RED;
					}

					break;
				}
	
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//当uncle不存在或者为黑色时候
					if (cur = parent->_right)
					{
						//左旋
						LeftRotate(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						RightRotate(parent);
						LeftRotate(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return true;
	}

	Node* Find(const K& key)
	{

		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}

	void LeftRotate(Node* x)
	{
		Node* y = x->_right;          // y成为新的根

		x->_right = y->_left;          // y的左子树挂到x的右边
		if (y->_left)
			y->_left->_parent = x;

		y->_parent = x->_parent;       // y接替x的位置

		if (x->_parent == nullptr)
			_root = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;

		y->_left = x;
		x->_parent = y;
	}

	void RightRotate(Node* y)
	{
		Node* x = y->_left;          // x成为新的根

		y->_left = x->_right;         // x的右子树挂到y左边
		if (x->_right)
			x->_right->_parent = y;

		x->_parent = y->_parent;      // x接替y的位置

		if (y->_parent == nullptr)
			_root = x;
		else if (y == y->_parent->_left)
			y->_parent->_left = x;
		else
			y->_parent->_right = x;

		x->_right = y;
		y->_parent = x;
	}

	bool Check(Node* root, int BlackNum, const int refnum)
	{
		if (root == nullptr)
		{
			if (BlackNum != refnum)
			{
				cout << "存在黑色节点不相等的路径" << endl;
				return false;
			}
			return true;
		}
		if (root->_parent == RED && root->_col == RED)
		{
			cout << root->_kv.first << "constant RED" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			BlackNum++;
		}
		return Check(root->_left, BlackNum, refnum)
			&& Check(root->_left, BlackNum, refnum);
	}

	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			return false;
		}
		int refnum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				refnum++;			
			}
			cur = cur->_left;
		}
		return Check(_root, 0, refnum);
	}

private:
	Node* _root = nullptr;
};


