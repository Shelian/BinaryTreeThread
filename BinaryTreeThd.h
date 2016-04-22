#ifndef __BINARYTREETHD_H__
#define __BINARYTREETHD_H__
#include <iostream>
using namespace std;
#include <stack>

enum PointerTag{ THREAD, LINK };

template<class T>
struct BinaryTreeThdNode
{
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;
	T _data;

	BinaryTreeThdNode(const T& x)
		:_left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
		, _data(x)
	{}
};



template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd(int* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTreeThd(a, size, invalid,index);
	}

	BinaryTreeThd(const BinaryTreeThd& b)
	{}

	BinaryTreeThd& operator=(const BinaryTreeThd& b)
	{}

	~BinaryTreeThd()
	{}

	/*用栈线索化二叉树*/
	void InOrderThreading()
	{
		stack<Node*> s;
		Node* prev = NULL;
		Node* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			s.pop();
			if (cur->_left == NULL)
			{
				cur->_left = prev;
				cur->_leftTag = THREAD;
			}
			prev = cur;
			if (cur->_right == NULL && !s.empty())
			{
				cur->_right = s.top();
				cur->_rightTag = THREAD;
				cur = NULL;
			}

			else
			{
				cur = cur->_right;
			}
		}
	}

	//用递归实现线索化二叉树
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
	}

	/*void InOrder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur)
		{
			while (cur->_left)
			{
				cur = cur->_left;
			}
			cut << cur->_data << " ";
			if (cur->_rightTag == THREAD)
			{
				cout << cur->_right->_data << " ";
				cur = cur->_right;
			}
			else if (cur->_right == LINK)
			{
				
			}
		}
	}*/

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	//线索化的优势在哪？
	void InOrder_NonR()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				if (cur->_leftTag == THREAD)
					break;
				cur = cur->_left;
			}
			cur = s.top();
			cout << cur->_data << " ";
			s.pop();

			if (cur->_rightTag == LINK)
			{
				cur = cur->_right;
			}
			else if (cur->_rightTag == THREAD)
			{
				cur = NULL;
			}
		}
		cout << endl;
	}

protected:
	//递归实现线索化二叉树
	void _InOrderThreading(Node* root,Node* prev)
	{
		if (root == NULL)
			return;

		if (root->_leftTag == LINK)
		_InOrderThreading(root->_left, prev);

		if (root->_left == NULL)
		{
			root->_left = prev;
			root->_leftTag = THREAD;
		}
		if (root->_right == NULL)
		{
			root->_rightTag = THREAD;
		}
		if (prev != NULL && prev->_rightTag == THREAD)
		{
			prev->_right = root;
		}

		prev = root;

		if (root->_rightTag == LINK)
		_InOrderThreading(root->_right, prev);
	}

	//递归打印线索化二叉树
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		if (root->_leftTag == LINK)
			_InOrder(root->_left);

		cout << root->_data << " ";
		if (root->_rightTag == LINK)
		{
			_InOrder(root->_right);
		}
	
	}

	Node* _CreateTreeThd(int* a, size_t size, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTreeThd(a, size, invalid, ++index);
			root->_right = _CreateTreeThd(a, size, invalid, ++index);
		}

		return root;
	}

protected:
	BinaryTreeThdNode<T>* _root;
};




void test()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd<int> t1(a, 10, '#');
	t1.InOrderThreading();
	t1.InOrder();
	t1.InOrder_NonR();
}


#endif //__BINARYTREETHD_H__