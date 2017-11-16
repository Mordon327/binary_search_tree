//Name: Shane Soderstrom
//Class: CS 2420
//Date: 7/21/17
#ifndef BST_H
#define BST_H
/**
* Provide implementations for the methods in this class so that it is complete and correct.
* Many of the algorithms are most easily done recursively, typically using private helper methods.
* Some public methods have code inserted to give an example for how this could be done.
* Some methods have dummy code inserted just to mke the code compile.
* You should feel free to alter or add private helper methods or signatures in order
* to make your coding easier.
* Notice that the data type is integer.  For Bst's and databases, fast keys are typically integers
* or strings, but we will only concern ourselves with integers to keep it simple.
*/

#include <vector>
#include <algorithm>
using std::vector;
using namespace std;


//TODO: Start with the insert function.  Get it working.																Is done? DONE!
//Second: The three traversals.  The reason being is that they are quick to do and only need insert to get started.		Is done? DONE!
//Third: Size and Height functions.  Two important functions that are used in almost all other functions.				Is done? DONE!
//Fourth: Remove.  If the goal is to make a tree and then balance the tree, this function needs to be done.				Is done?
//Fifth: Find.  Fast function that should be easy and helpful later on.													Is done? DONE!
//Sixth: Copy.  This one will be a pain but it will be worth it.														Is done? DONE!
//Seventh: Destructor.  This completes everything other than balancing.													Is done? DONE!
//Eight: isBalanced.																									Is done?
//Ninth: Balanced.  Save the big bad one for last.																		Is done?







class Bst {
	struct Node {
		Node* parent = nullptr;
		Node* left = nullptr;
		int val;
		Node* right = nullptr;
		Node(int v) { val = v; }
	};

	Node* root = nullptr;

	/**
	* This is the helper function for public insert method.
	* @see insert().
	Because a Node is being inserted, we know that there is already a root node.  We will not check for an empty tree.
	*/
	void insert(Node*& node, int val) {
		Node * temp;
		temp = new Node(val);
		//First stopping case.  Because we don't want duplicates, if the value already exists, then do nothing.
		if (node->val == val)
		{
			return;
		}
		else if (val < node->val && node->left == nullptr)
		{
			node->left = temp;
			node->left->parent = node;
		}
		else if (val > node->val && node->right == nullptr)
		{
			node->right = temp;
			node->right->parent = node;
		}
		else if (val < node->val)
		{
			insert(node->left, val);
		}
		else
		{
			insert(node->right, val);
		}
	}
	/**
	* This is the helper function for public inorder traversal method.
	* @see inorder().
	*/
	void inorder(Node* node, vector<int>& values) {
		if (node != nullptr)
		{
			inorder(node->left, values);
			values.push_back(node->val);
			inorder(node->right, values);
		}
		//if (node->left != nullptr)
		//{
		//	node = node->left;
		//	inorder(node, values);
		//}
		//values.push_back(node->val);
		//if (node->right != nullptr)
		//{
		//	node = node->right;
		//	inorder(node, values);
		//}
	}

	/**
	* This is the helper function for public preorder traversal method.
	* @see inorder().
	*/
	void preorder(Node* node, vector<int>& values) {
		if (node != nullptr)
		{
			values.push_back(node->val);
			preorder(node->left, values);
			preorder(node->right, values);
		}
	}
	/**
	* This is the helper function for public postorder traversal method.
	* @see inorder().
	*/
	void postorder(Node* node, vector<int>& values) {
		//if (node->left != nullptr)
		//{
		//	node = node->left;
		//	inorder(node, values);
		//}
		//if (node->right != nullptr)
		//{
		//	node = node->right;
		//	inorder(node, values);
		//}
		//values.push_back(node->val);

		if (node != nullptr)
		{
			postorder(node->left, values);
			postorder(node-> right, values);
			values.push_back(node->val);
		}
	}
	/**
	* This is the helper function for the destructor method.
	* @see ~Bst().
	*/
	void destroy(Node* node) {
		if (node != nullptr)
		{
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}

	/**
	* This is the helper function for the copy constructor.
	* @see Bst(Bst& other).
	*/
	Node* copy_tree(Node* node) {
		Node * temp;
		if (node != nullptr)
		{		
			temp = new Node(node->val);
			temp->left = (node->left);
			temp->right = copy_tree(node->right);
		}
		return temp;
	}

	/**
	* This is the helper function for the public find method.
	* @see find().
	*/
	Node* find(Node* node, int val) {
		if (node != nullptr)
		{
			if (node->val == val)
			{
				return node;
			}
			else if (node->val > val)
			{
				find(node->right, val);
			}
			else
			{
				find(node->left, val);
			}
		}
	}

	/**
	* This is the helper function for the public remove method.
	* @see remove().
	*/
	void remove(Node*& p, int n) {
		if (p == nullptr || find(n) == false)
			return;
		else
		{
			if (p->val == n)
			{
				if (p->left == nullptr && p->right == nullptr)
				{
					delete p;
				}
				else
				{
					Node * temp = p;
					if (temp->left != nullptr)
					{
						temp = temp->left;

						//go until there are no more rights to go to.
						while (temp->right != nullptr)
						{
							temp = temp->right;
						}

						//if there are more left nodes.
						if (temp->left != nullptr)
						{
							//while there are more left nodes go left.
							while (temp->left != nullptr)
							{
								temp = temp->left;
								//check for more right nodes.
								if (temp->right != nullptr)
								{
									//if more right nodes then go right again.
									while (temp->right != nullptr)
									{
										temp = temp->right;
									}
								}
							}
						}

						p->val = temp->val;
						temp = temp->parent;
						if (temp->right->val == p->val)
						{
							temp->right = nullptr;
						}
						if (temp->left->val == p->val)
						{
							temp->left = nullptr;
						}
						temp = NULL;
						
					}
					else
					{
						if (temp->right != nullptr)
						{
							temp = temp->right;

							//go until there are no more lefts to go to.
							while (temp->left != nullptr)
							{
								temp = temp->left;
							}

							//if there are more rights nodes.
							if (temp->right != nullptr)
							{
								//while there are more rights nodes go right.
								while (temp->right != nullptr)
								{
									temp = temp->right;
									//check for more left nodes.
									if (temp->left != nullptr)
									{
										//if more left nodes then go left again.
										while (temp->left != nullptr)
										{
											temp = temp->left;
										}
									}
								}
							}
							p->val = temp->val;
							temp->val = NULL;
						}
					}
				}
			}
			else
			{
				if (p->left != nullptr)
					remove(p->left, n);
				if (p->right != nullptr)
					remove(p->right, n);
			}
		}
	}

	/**
	* This is the helper function for the public size method.
	* @see size().
	*/
	size_t size(Node* node)
	{
		vector<int> temp;
		preorder(node, temp);
		size_t size = temp.size();
		return size;
	}

	/**
	* This is the helper for the public balance method
	* @see balanced.
	*/
	void balance(Node* node) {
		int two = 2;
		vector<int> temp;
		inorder(node, temp);
		int length = temp.size();
		delete node;
		Node * newNode;
		int mid = length / two;
		if (length % two == 0)
		{
			mid--;
		}
		newNode = new Node(temp[mid]);
		node = newNode;

		int newmid = mid / two;
		if (mid % two == 0)
		{
			newmid--;
		}
		newNode = new Node(temp[newmid]);
		node->left = newNode;
		node->left->parent = node;

		int lastmid = newmid + mid;
		if (length % two != 0)
		{
			lastmid++;
		}
		newNode = new Node(temp[lastmid]);
		node->right = newNode;
		node->right->parent = node;

		for (int i = 0; i < length; i++)
		{
			insert(node, i);
		}

	}

	/**
	* This is the helper for the public isBalanced method
	* @see isBalanced.
	*/
	bool isBalanced(Node* tree) {
		if (tree == nullptr)
		{
			return true;
		}
		int two = 2;
		int negtwo = -2;
		int left = 0;
		int right = 0;

		left = height(tree->left);
		right = height(tree->right);
		int sum = left - right;
		if ((sum <= two || sum >= negtwo) && isBalanced(tree->right) && isBalanced(tree->left))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t height(Node* tree) {
		//if (tree == nullptr)
		//	return -1;

		//return 1 + max(height(tree->left), height(tree->right));
		if (tree != nullptr) 
		{
			int left = 1;
			int right = 1;
			left += height(tree->left);
			right += height(tree->right);

			if (left < right) {
				return right;
			}
			else if (left > right) {
				return left;
			}
			else {
				return right;
			}
		}
		else {
			return 0;
		}
	}

public:
	/**
	* Default constructor.
	*/
	Bst()
	{

	}

	/**
	* Copy constructor.
	*/
	Bst(Bst& other)
	{
		root = copy_tree(other.root);
	}
	/**
	* Destructor.
	*/
	~Bst() {
		destroy(root);
	}

	/**
	* Insert the value into the tree at the proper position.
	* Duplicates are not allowed. Values less than a node should go in the left subtree,
	* values greater should go in the right subtree, just like the text.  If there is a tie,
	* do nothing to the tree.
	* @param the value to be inserted in the tree.
	*/
	void insert(int val) {
		//insert a node with the value at the next available location based on the parents value.

		if (root == nullptr)
		{			
			Node * temp;
			temp = new Node(val);
			temp->left = nullptr;
			temp->right = nullptr;
			root = temp;
		}
		//if there is no root node, then this first node is the root node.
		else
		{
			insert(root, val);
		}

		//else, use recursion to continually test for where the next node should be placed.
	}

	vector<int> inorder() {
		//put the items into a vector as an inorder traversal and return it. Left, parent, right
		vector<int> temp;
		inorder(root, temp);
		return temp;

		//if (root == nullptr)
		//{
		//	return temp;
		//}
		//else if (root->left == nullptr && root->right == nullptr)
		//{
		//	temp.push_back(root->val);
		//	return temp;
		//}
		//else
		//{
		//	inorder(root, temp);
		//	return temp;
		//}
	}

	vector<int> preorder() {
		//put the items into an vector as an preorder traversal and return it. Parent, left, right
		vector<int> temp;
		preorder(root, temp);
		return temp;
	}

	vector<int> postorder() {
		//put the items into an vector as an postorder traversal and return it. left, right, parent
		vector<int> temp;
		postorder(root, temp);
		return temp;
	}

	//probably nothing at find, remove, size.
	bool find(int val) {
		return find(root, val) != nullptr;
	}

	void remove(int val) {
		remove(root, val);
	}

	size_t size() {
		return size(root);
	}
	//end of nothing.

	void balance() {
		balance(root);
	}

	bool isBalanced() {
		return isBalanced(root);
	}

	size_t height() {
		return height(root);
	}
};
#endif