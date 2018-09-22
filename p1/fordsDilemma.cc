// given two planet names return the list of planet names and entrance fees of all planets between the two queried names, in lexicographic order
// 
// author: willie yee
// date: 5.25.2018

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;

// TODO: fix the updateInfo method to account for this ^

template <class key_t, class value_t> class AVLTree
{
	public:
	
	class AVLNode
	{
		public:
		key_t key;
		value_t value;
		shared_ptr<AVLNode> left;
		shared_ptr<AVLNode> right;
		int height;
		AVLNode(key_t key, value_t value)
		{
			this->key = key;
			this->value = value;
			this->height = 1;
		}
	};

	shared_ptr<AVLNode> root = NULL;
	
	int getHeight(shared_ptr<AVLNode> node)
	{
		if (node == NULL)
		{
			return 0;
		}
		return node->height;
	}

	void updateInfo(shared_ptr<AVLNode> node)
	{
		node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	}

	shared_ptr<AVLNode> rightRotate(shared_ptr<AVLNode> node)
	{
		shared_ptr<AVLNode> nodel = node->left;
		shared_ptr<AVLNode> nodelr = nodel->right;
		nodel->right = node;
		node->left = nodelr;
		updateInfo(node);
		updateInfo(nodel);
		return nodel;
	}

	shared_ptr<AVLNode> leftRotate(shared_ptr<AVLNode> node)
	{
		shared_ptr<AVLNode> noder = node->right;
		shared_ptr<AVLNode> noderl = noder->left;
		noder->left = node;
		node->right = noderl;
		updateInfo(node);
		updateInfo(noder);
		return noder;
	}

	int getBalance(shared_ptr<AVLNode> node)
	{
		if (node == NULL)
		{
			return 0;
		}
		return getHeight(node->left) - getHeight(node->right);
	}
	
	shared_ptr<AVLNode> doInsert(shared_ptr<AVLNode> node, key_t key, value_t value)
	{
		if (node == NULL)
		{
			return (make_shared<AVLNode>(key, value));
		}
		if (key < node->key)
		{
			node->left = doInsert(node->left, key, value);
		}
		else if (key > node->key)
		{
			node->right = doInsert(node->right, key, value);
		}
		else
		{
			node->value = value;
			return node;
		}
		updateInfo(node);
		int balance = getBalance(node);
		if (balance > 1 && key < node->left->key)
		{
			return rightRotate(node);
		}
		if (balance < -1 && key > node->right->key)
		{
			return leftRotate(node);
		}
		if (balance > 1 && key > node->left->key)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balance < -1 && key < node->right->key)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}

	void insert(key_t key, value_t value)
	{
		root = doInsert(root, key, value);
	}

	value_t find(key_t key)
	{
		return doFind(root, key);
	}

	value_t doFind(shared_ptr<AVLNode> node, key_t key)
	{
		if (node == NULL)
		{
			return -1;
		}
		if (key == node->key)
		{
			return node->value;
		}
		else if (key < node->key)
		{
			return doFind(node->left, key);
		}
		return doFind(node->right, key);
	}

	// this function only works when working on type <string, int>
	vector<string> treeList(shared_ptr<AVLNode> node)
	{
		vector<string> output;
		if (node != NULL) {
			auto left = treeList(node->left);
			auto right = treeList(node->right);
			string current = "[" + node->key + ": " + to_string(node->value) + "]";
			string padding = "";
			for (int i = 0; i < current.size(); i++)
			{
				padding += " ";
			}
			for (auto level : left)
			{
				output.push_back(padding + level);
			}
			output.push_back(current);
			for (auto level : right)
			{
				output.push_back(padding + level);
			}
		}
		return output;
	}
	
	string str()
	{
		auto levels = treeList(root);
		string output = "";
		for (auto level : levels)
		{
			output += level + "\n";
		}
		return output;
	}
	
	// method to print out a tree given a range
	void printTree(shared_ptr<AVLNode> node, string rMin, string rMax)
	{
		if(node == NULL)
		{
			return;
		}
		if(node->key > rMin)
		{
			printTree(node->left, rMin, rMax);	
		}
		if(node->key >= rMin && node->key <= rMax)
		{
			cout << node->key << " " << node->value << "\n";
		}
		if(node->key < rMax)
		{
			printTree(node->right, rMin, rMax);
		}
	}
};

int main()
{
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */   

	// create the tree
	AVLTree<string, int> tree;

	// get size of the database
	int dSize;
	cin >> dSize;

	// get next dSize lines of user input and insert them into the tree
	for(int counter = 0; counter < dSize; counter++)
	{		
		// get planet name
		string key;		
		cin >> key;
			
		// get price
		int value;
		cin >> value;
		
		// insert into tree
		tree.insert(key, value);
	}

	// get number of queries
	int qCount;
	cin >> qCount;
	
	// get next qCount lines of user input and store them
	for(int counter = 0; counter < qCount; counter++)
	{
		// get range min
		string rMin;
		cin >> rMin;

		// get range max
		string rMax;
		cin >> rMax;
		
		tree.printTree(tree.root, min(rMin,rMax), max(rMin,rMax));
	}
	return 0;
}