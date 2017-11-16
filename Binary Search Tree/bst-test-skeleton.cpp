#include <vector>

#include "test.h"
#include "bst2-skeleton.h"

using std::cout;
using std::endl;
using std::vector;

/**
* Helper function prints a vector on one line with space as the separator between elements.
* @param values the vector to print
*/
void printTraversal(vector<int>& values) {
	for (int value : values)
	{
		cout << value << " ";
	}
	cout << endl;
}

/**
* @TODO: Add code in this method to complete the construction of
* the tree on page 524 of text, except the leaf 53 is replaced by 50.
* Helper method that builds a tree of nodes.
* Precondition: the tree is empty.
* Postcondition: A correct BST is created based on the order values are inserted.
* @param tree a pointer to a BST.
*/
void build_tree(Bst* tree) {

	tree->insert(45);
	tree->insert(9);
	tree->insert(53);
	tree->insert(50);
	tree->insert(54);
	tree->insert(3);
	tree->insert(17);


}

/**
* @TODO: add code to insert 55,56,57,58,59,60 in order.
* Helper method that adds a linear sequence of nodes to the tree
* Precondition: the tree is a valid BST
* Postcondition: Tree height is increased by length of the linear branch.
* @param tree a pointer to a BST.
*/
void add_linear_branch(Bst* tree) {


	tree->insert(55);
	tree->insert(56);
	tree->insert(57);
	tree->insert(58);
	tree->insert(59);
	tree->insert(60);

}
/**
* This helper function tests individual elements because a tree may be partially correct.
* @param expectedValues  a vector of expected values
* @param size the length of expected values--not strictly necessary, since we can get the size of a vector.
* @param actualValues the set of actaul values from a traversal
*/
void check_traversal(vector<int>& expectedValues, size_t size, vector<int>& actualValues)
{
	assert_equal(size, actualValues.size());
	for (size_t i = 0; i < actualValues.size() && i < size; i++) {
		assert_equal(expectedValues[i], actualValues[i]);
	}
}

/**
!!!!!!!!!DONE!!!!!!
* @TODO: insert code at the indicated lines to construct the tree
* 9 <- 45 -> 53
Test method
*/
void test_empty()
{
	Bst tree;
	tree.insert(45);
	assert_equal((size_t)1, tree.size());
	assert_equal(tree.find(45), true);
	tree.insert(9);
	tree.insert(53);
	assert_equal((size_t)3, tree.size());
	vector<int> values = tree.inorder();
	printTraversal(values);
	vector<int> expectedValues = {9,45,53}; //insert expected values in this array
	check_traversal(expectedValues, 3, values);
}

/**
* @TODO: Insert code in the places indicated
Test method
*/
void test_remove_root()
{
	Bst* tree = new Bst();
	build_tree(tree);
	assert_equal((size_t)7, tree->size());
	tree->remove(45);
	assert_equal((size_t)6, tree->size());


	vector<int> values = tree->inorder();  //modify this line to store an inorder traversal in values
	printTraversal(values);
	vector<int> expectedValues = { 3,9,17,50,53,54}; //modify this line to store expected values here
	check_traversal(expectedValues, 6, values);
	tree->remove(53);
	expectedValues.erase(expectedValues.begin() + 3);
	values = tree->inorder();  //modify this line to store an inorder traversal in values
	check_traversal(expectedValues, 5, values);
	delete tree;//add a line here to delete the tree nodes you allocated above
}
/**
@TODO add lines at the indicated places
Test method
*/
void test_traversals()
{
	Bst* tree = new Bst();
	//add a line of code to construct the tree from page 524 here.
	tree->insert(45);
	tree->insert(9);
	tree->insert(53);
	tree->insert(3);
	tree->insert(50);
	tree->insert(54);
	tree->insert(17);
	//In this method add lines to print the preorder, inorder and postorder traversals to
	//the console on a single line. Prefix the line with "preorder: ", "inorder: " and "postorder:
	//respectively
	cout << "Inorder traversal: ";
	vector<int> traversal = tree->inorder();
	printTraversal(traversal);
	vector<int> expectedValues = { 3,9,17,45,50,53,54 }; //store expected values here
	bool same = (expectedValues == traversal);
	test_(same);

	cout << "Preorder traversal: ";
	traversal = tree->preorder();
	printTraversal(traversal);
	expectedValues = { 45,9,3,17,53,50,54 }; //store expected values here
	same = (expectedValues == traversal);
	test_(same);

	cout << "Postorder traversal: ";
	traversal = tree->postorder();
	printTraversal(traversal);
	expectedValues = { 3,17,9,50,54,53,45 }; //store expected values here
	same = (expectedValues == traversal);
	test_(same);
}

/**
Test method
*/
void test_balance()
{
	Bst* tree = new Bst();
	build_tree(tree);
	assert_equal(true, tree->isBalanced());
	add_linear_branch(tree);
	assert_equal(false, tree->isBalanced());
	assert_equal((size_t)9, tree->height());
	tree->balance();
	assert_equal(true, tree->isBalanced());
	assert_equal((size_t)4, tree->height());
	delete tree;//add a line here to delete the tree you constructed above
}


/**
* Run tests in the indicated methods and print a result to
* the console.
*/
int main()
{
	test_empty();
	test_traversals();
	test_remove_root();
	test_balance();
	report_();

	std::cin.ignore();
	return 0;
}