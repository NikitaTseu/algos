#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

template <typename T> class Node {
public:
	T key;
	Node* left;
	Node* right;
	Node* parent;

	Node(T val) {
		key = val;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	int range() {
		int range = 0;
		if (this->right != NULL) {
			range++;
		}
		if (this->left != NULL) {
			range++;
		}
		return range;
	}

	bool isLeaf() {
		if (this->range() == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool isRoot() {
		if (this->parent == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void add(Node* node) {
		node->left = NULL;
		node->right = NULL;

		if (node->key < key) {
			if (left == NULL) {
				left = node;
				node->parent = this;
			}
			else {
				left->add(node);
			}
		}
		
		if (node->key > key) {
			if (right == NULL) {
				right = node;
				node->parent = this;
			}
			else {
				right->add(node);
			}
		}
	}
};

template <typename T> class BinTree {
public:
	Node<T>* root;

	BinTree() {
		root = NULL;
	}

	BinTree(Node<T>* node) {
		this->root = node;
		root->left = NULL;
		root->right = NULL;
	}

	void add(Node<T>* node) {
		if (root != NULL) {
			root->add(node);
		}
		else {
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			root = node;
		}
	}

	void add(T val) {
		this->add(new Node<T>(val));
	}

	void directLeft(Node<T>* start) {
		if (start != NULL) {
			fout << start->key << endl;
			directLeft(start->left);
			directLeft(start->right);
		}
	}
};

int main()
{
	int a;
	BinTree<int> tree;

	while (fin >> a) {
		tree.add(a);
		cout << a << endl;
	}

	tree.directLeft(tree.root);
	return 0;
}

