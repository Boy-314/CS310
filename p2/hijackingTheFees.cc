// For each query that starts with 3 print the entrance fee of the planet in a new line.
// If the planet is not in the database, print a "-1", without the quotes.
// 
// author: willie yee
// date: 5.29.2018

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

// TODO: add pushdown method

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
		value_t carry;
		key_t minimum;
		key_t maximum;
		AVLNode(key_t key, value_t value)
		{
			this->key = key;
			this->value = value;
			this->height = 1;
			this->carry = 0;
			this->minimum = key;
			this->maximum = key;
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

	// added method to update min and max values of a node
	void updateMinMax(shared_ptr<AVLNode> node)
	{
		if(node == NULL)
		{
			return;
		}
		updateMinMax(node->left);
		if(node->left == NULL)
		{
			node->minimum = node->key;
		}
		else if(node->left->minimum < node->minimum)
		{
			node->minimum = node->left->minimum;
		}
		updateMinMax(node->right);
		if(node->right == NULL)
		{
			node->maximum = node->key;
		}
		else if(node->right->maximum > node->maximum)
		{
			node->maximum = node->right->maximum;
		}
	}
	
	shared_ptr<AVLNode> rightRotate(shared_ptr<AVLNode> node)
	{
		shared_ptr<AVLNode> nodel = node->left;
		shared_ptr<AVLNode> nodelr = nodel->right;
		nodel->right = node;
		node->left = nodelr;
		updateInfo(node);
		updateInfo(nodel);
		updateMinMax(node);
		updateMinMax(nodel);
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
		updateMinMax(node);
		updateMinMax(noder);
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
	
	// added pushdown node method
	void pushDown(shared_ptr<AVLNode> node)
	{
		if(node->left == NULL && node->right == NULL)
		{
			node->value += node->carry;
			node->carry = 0;
			return;
		}
		if(node->left != NULL)
		{
			node->left->carry += node->carry;
		}
		if(node->right != NULL)
		{
			node->right->carry += node->carry;
		}
		node->value += node->carry;
		node->carry = 0;
	}
	
	shared_ptr<AVLNode> doInsert(shared_ptr<AVLNode> node, key_t key, value_t value)
	{
		if (node == NULL)
		{
			return (make_shared<AVLNode>(key, value));
		}
		if(node->carry > 0)
		{
			pushDown(node);
		}
		if (key < node->key)
		{
			// update the mininmum of each node if necessary
			if(node->minimum > key)
			{
				node->minimum = key;
			}
			node->left = doInsert(node->left, key, value);
			updateMinMax(node);
		}
		else if (key > node->key)
		{
			// update the maximum of each node if necessary
			if(node->maximum < key)
			{
				node->maximum = key;
			}
			node->right = doInsert(node->right, key, value);
			updateMinMax(node);
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
			updateMinMax(root);
			return rightRotate(node);
		}
		if (balance < -1 && key < node->right->key)
		{
			node->right = rightRotate(node->right);
			updateMinMax(root);
			return leftRotate(node);
		}
		return node;
	}

	void insert(key_t key, value_t value)
	{
		root = doInsert(root, key, value);
		updateMinMax(root);
	}

	value_t find(key_t key)
	{
		return doFind(root, key, root->carry);
	}

	// edited to account for the carry value
	value_t doFind(shared_ptr<AVLNode> node, key_t key, value_t c)
	{
		if (node == NULL)
		{
			// cout << "null\n";
			return -1;
		}
		if (key == node->key)
		{
			// cout << "found key\n";
			return node->value + c;
		}
		else if (key < node->key && node->left != NULL)
		{
			// cout << "going left\n";
			return doFind(node->left, key, node->left->carry + c);
		}
		else if (key > node->key && node->right != NULL)
		{
			// cout << "going right\n";
			// cout << "c: " << c << "\n" << "node->right->carry + c: " << node->right->carry + c << "\n"; 
			return doFind(node->right, key, node->right->carry + c);
		}
		else
		{
			// cout << "none of the above\n";
			return -1;
		}
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
	
	// update method
	void update(shared_ptr<AVLNode> node, key_t a, key_t b, value_t v)
	{
		if(node == NULL)
		{
			return;
		}
		else if(node->minimum >= a && node->maximum <= b)
		{
			node->carry += v;
		}
		else if((node->minimum < a && node->maximum < a) || (node->minimum > b && node->maximum > b))
		{
		}
		else
		{
			update(node->left, a, b, v);
			update(node->right, a, b, v);
			if(node->key >= a && node->key <= b)
			{
				node->value += v;
			}
		}
	}
};

int main()
{
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */   

	// create the tree
	AVLTree<string, int> tree;
	
	// get number of queries
	int dSize;
	cin >> dSize;
	
	// get next dSize lines of user input
	for(int counter = 0; counter < dSize; counter++)
	{	
		// first input: 1, 2, or 3
		// 1 a k: insert a planet with name a and entrance fee k
		// 2 a b k: increase the entrance fee for all planets between a and b by k
		// 3 a: print out the entrance fee for planet a
		int inType;
		cin >> inType;
		
		// insert a planet with name a and entrance fee k
		if(inType == 1)
		{
			// get the planet name
			string name;
			cin >> name;
			
			// get the planet fee
			int fee;
			cin >> fee;
			
			// insert into the tree
			tree.insert(name, fee);	
			
			// test output
			// cout << tree.str();
		}
		
		// increase the entrance fee for all planets between a and b by k
		if(inType == 2)
		{
			// get the range
			string rMin;
			cin >> rMin;
			
			string rMax;
			cin >> rMax;
			
			// get the amount to increase by
			int v;
			cin >> v;
			
			// increment the nodes in the range
			tree.update(tree.root, min(rMin,rMax), max(rMin,rMax), v);
			
			// test output
			// cout << tree.str() << "finished type2\n";
			// cout << "@main if block 2 --- tree.root->carry: " << tree.root->carry << "\n";
		}
		
		// print out the entrance fee for planet a
		if(inType == 3)
		{
			// get planet name
			string name;		
			cin >> name;
			
			cout << tree.find(name) << "\n";
		}
	}
	
	// cout << "root: " << tree.root->key << ", " << tree.root->value << ", " << tree.root-> carry << ", " << tree.root->minimum << ", " << tree.root->maximum << "\n";
	// cout << "root->left: " << tree.root->left->key << ", " << tree.root->left->value << ", " << tree.root->left-> carry << ", " << tree.root->left->minimum << ", " << tree.root->left->maximum << "\n";
	// cout << "root->right: " << tree.root->right->key << ", " << tree.root->right->value << ", " << tree.root->right-> carry << ", " << tree.root->right->minimum << ", " << tree.root->right->maximum << "\n";

	return 0;
}