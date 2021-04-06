#pragma once

//============================================================================
// Name        : Exercise 4
// Author      : Benjamin Liden
// Date		   : April 5, 2021
// Professor   : Ivan Temesvari
// Class       : CS240
//============================================================================

/* Please see the new additions at the bottom of the file:
 *
 * Ancestors (x2), GetParentage
 */

#include <string>
#include <sstream>

#include "QueType.h"

enum class OrderType {
	PRE_ORDER, IN_ORDER, POST_ORDER
};

template<class T>
struct TreeNode;

template<class T>
class TreeType {
public:
	TreeType();                     // constructor
	~TreeType();                    // destructor
	TreeType(const TreeType<T> &originalTree);
	void operator=(const TreeType<T> &originalTree);
	// copy constructor
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int GetLength() const;
	T GetItem(T item, bool &found);
	void PutItem(T item);
	void DeleteItem(T item);
	void ResetTree(OrderType order);
	T GetNextItem(OrderType order, bool &finished);
	void Print(std::ostream &out = std::cout) const;
	std::string Ancestors(T item) const;

private:
	TreeNode<T> *root;
	QueType<T> preQue;
	QueType<T> inQue;
	QueType<T> postQue;
};

template<class T>
struct TreeNode {
	T info;
	TreeNode *left;
	TreeNode *right;
};

template<class T>
bool TreeType<T>::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
	TreeNode<T> *location;
	try {
		location = new TreeNode<T>;
		delete location;
		return false;
	} catch (std::bad_alloc &exception) {
		return true;
	}
}

template<class T>
bool TreeType<T>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
	return root == nullptr;
}

template<class T>
int CountNodes(TreeNode<T> *tree)
// Post: returns the number of nodes in the tree.
		{
	if (tree == nullptr)
		return 0;
	else
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template<class T>
int TreeType<T>::GetLength() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
	return CountNodes(root);
}

template<class T>
void Retrieve(TreeNode<T> *tree, T &item, bool &found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
		{
	if (tree == nullptr)
		found = false;                     // item is not found.
	else if (item < tree->info)
		Retrieve(tree->left, item, found); // Search left subtree.
	else if (item > tree->info)
		Retrieve(tree->right, item, found); // Search right subtree.
	else {
		item = tree->info;                 // item is found.
		found = true;
	}
}

template<class T>
T TreeType<T>::GetItem(T item, bool &found)
// Calls recursive function Retrieve to search the tree for item.
		{
	Retrieve(root, item, found);
	return item;
}

template<class T>
void Insert(TreeNode<T> *&tree, T item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
		{
	if (tree == nullptr) {                 // Insertion place found.
		tree = new TreeNode<T>;
		tree->right = nullptr;
		tree->left = nullptr;
		tree->info = item;
	} else if (item < tree->info)
		Insert(tree->left, item);    // Insert in left subtree.
	else
		Insert(tree->right, item);   // Insert in right subtree.
}

template<class T>
void TreeType<T>::PutItem(T item)
// Calls recursive function Insert to insert item into tree.
		{
	Insert(root, item);
}

template<class T>
void DeleteNode(TreeNode<T> *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-nullptr child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
		{
	T data;
	TreeNode<T> *tempPtr;

	tempPtr = tree;
	if (tree->left == nullptr) {
		tree = tree->right;
		delete tempPtr;
	} else if (tree->right == nullptr) {
		tree = tree->left;
		delete tempPtr;
	} else {
		GetPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);  // Delete predecessor node.
	}
}

template<class T>
void Delete(TreeNode<T> *&tree, T item)
// Deletes item from tree.
// Post:  item is not in tree.
		{
	if (item < tree->info)
		Delete(tree->left, item);   // Look in left subtree.
	else if (item > tree->info)
		Delete(tree->right, item);  // Look in right subtree.
	else
		DeleteNode(tree);           // Node found; call DeleteNode.
}

template<class T>
void TreeType<T>::DeleteItem(T item)
// Calls recursive function Delete to delete item from tree.
		{
	Delete(root, item);
}

template<class T>
void GetPredecessor(TreeNode<T> *tree, T &data)
// Sets data to the info member of the right-most node in tree.
		{
	while (tree->right != nullptr)
		tree = tree->right;
	data = tree->info;
}

template<class T>
void PrintTree(TreeNode<T> *tree, std::ostream &out)
// Prints info member of items in tree in sorted order on outFile.
		{
	if (tree != nullptr) {
		PrintTree(tree->left, out);   // Print left subtree.
		out << tree->info;
		PrintTree(tree->right, out);  // Print right subtree.
	}
}

template<class T>
void TreeType<T>::Print(std::ostream &out) const
// Calls recursive function Print to print items in the tree.
		{
	PrintTree(root, out);
}

template<class T>
TreeType<T>::TreeType() {
	root = nullptr;
}

template<class T>
void Destroy(TreeNode<T> *&tree)
// Post: tree is empty; nodes have been deallocated.
		{
	if (tree != nullptr) {
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

template<class T>
TreeType<T>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

template<class T>
void TreeType<T>::MakeEmpty() {
	Destroy(root);
	root = nullptr;
}

template<class T>
void CopyTree(TreeNode<T> *&copy, const TreeNode<T> *originalTree)
// Post: copy is the root of a tree that is a duplicate
//       of originalTree.
		{
	if (originalTree == nullptr)
		copy = nullptr;
	else {
		copy = new TreeNode<T>;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}
}

template<class T>
TreeType<T>::TreeType(const TreeType<T> &originalTree)
// Calls recursive function CopyTree to copy originalTree
//  into root.
		{
	CopyTree(root, originalTree.root);
}

template<class T>
void TreeType<T>::operator=(const TreeType &originalTree)
// Calls recursive function CopyTree to copy originalTree
// into root.
		{
	{
		if (&originalTree == this)
			return;             // Ignore assigning self to self
		Destroy(root);      // Deallocate existing tree nodes
		CopyTree(root, originalTree.root);
	}

}

// Function prototypes for auxiliary functions.
template<class T>
void PreOrder(TreeNode<T> *tree, QueType<T> &preQue)
// Post: preQue contains the tree items in preorder.
		{
	if (tree != nullptr) {
		preQue.Enqueue(tree->info);
		PreOrder(tree->left, preQue);
		PreOrder(tree->right, preQue);
	}
}

template<class T>
void InOrder(TreeNode<T> *tree, QueType<T> &inQue)
// Post: inQue contains the tree items in inorder.
		{
	if (tree != nullptr) {
		InOrder(tree->left, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->right, inQue);
	}
}

template<class T>
void PostOrder(TreeNode<T> *tree, QueType<T> &postQue)
// Post: postQue contains the tree items in postorder.
		{
	if (tree != nullptr) {
		PostOrder(tree->left, postQue);
		PostOrder(tree->right, postQue);
		postQue.Enqueue(tree->info);
	}
}

template<class T>
void TreeType<T>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in
// the desired order.
		{
	switch (order) {
	case OrderType::PRE_ORDER:
		PreOrder(root, preQue);
		break;
	case OrderType::IN_ORDER:
		InOrder(root, inQue);
		break;
	case OrderType::POST_ORDER:
		PostOrder(root, postQue);
		break;
	}
}

template<class T>
T TreeType<T>::GetNextItem(OrderType order, bool &finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true;
//       otherwise finished is false.
		{
	finished = false;
	T item;
	switch (order) {
	case OrderType::PRE_ORDER:
		preQue.Dequeue(item);
		if (preQue.IsEmpty())
			finished = true;
		break;
	case OrderType::IN_ORDER:
		inQue.Dequeue(item);
		if (inQue.IsEmpty())
			finished = true;
		break;
	case OrderType::POST_ORDER:
		postQue.Dequeue(item);
		if (postQue.IsEmpty())
			finished = true;
		break;
	}
	return item;
}

/*
 * Written by Benjamin Liden
 * 4/5/21
 */

/**
 * Get the string representation of a tree item's parentage.
 *
 * Prints nicely if your type has a << override!
 */
template<class T>
std::string GetParentage(TreeNode<T> *tree, T &item, bool &found) {
	std::string parentage { };

	// if nullptr, return nothing
	if (tree == nullptr) {
		found = false;
		return "";
	}

	// if we are at the item, mark found=true and return this item
	if (tree->info == item) {
		/*
		 * I would prefer to use the actual item in the string,
		 *  but for compatability with the tests, I will not.
		 */
		found = true;
		return "";
//		return tree->info;
	}

	// search left
	parentage = GetParentage<T>(tree->left, item, found);
	if (found == true) {
		std::string separator = parentage.empty() ? "" : " ";
		std::stringstream ss;
		ss << tree->info << separator << parentage;
		return ss.str();
	}

	// search right
	parentage = GetParentage<T>(tree->right, item, found);
	if (found == true) {
		std::string separator = parentage.empty() ? "" : " ";
		std::stringstream ss;
		ss << tree->info << separator << parentage;
		return ss.str();
	}

	// otherwise, give up?
	found = false;
	return "";
}

/**
 * Return the heritage of a given item.
 */
template<class T>
std::string TreeType<T>::Ancestors(T item) const {
	bool found = false;
	std::string s = GetParentage<T>(root, item, found);

	if (found == false) {
		return "no ancestors were found";
	}

	return s;
}
