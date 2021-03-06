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
		root->parent = NULL;
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

	Node<T>* find(T key, Node<T>* start) {
		if (start == NULL || start->key == key) {
			return start;
		}
		else {
			if (start->key < key) {
				return find(key, start->right);
			}
			else {
				return find(key, start->left);
			}
		}
	}

	Node<T>* findMin(Node<T>* start) {
		if (start == NULL || start->left == NULL) {
			return start;
		}
		else {
			return findMin(start->left);
		}
	}

	Node<T>* findMax(Node<T>* start) {
		if (start == NULL || start->right == NULL) {
			return start;
		}
		else {
			return findMax(start->right);
		}
	}

	void deleteRight(T key, Node<T>* start) {
		Node<T>* delNode = find(key, start);
		if (delNode == NULL) {
			return;
		}
		else {
			if (delNode->range() == 0) {
				if (delNode->parent->left == delNode) {
					delNode->parent->left = NULL;
				}
				if (delNode->parent->right == delNode) {
					delNode->parent->right = NULL;
				}
				return;
			}
			else {
				if (delNode->left == NULL) {
					if (delNode == root) {
						root = delNode->right;
					}
					else {
						if (delNode->parent->left == delNode) {
							delNode->parent->left = delNode->right;
						}
						if (delNode->parent->right == delNode) {
							delNode->parent->right = delNode->right;
						}
					}
					
					return;
				}
				if (delNode->right == NULL) {
					if (delNode == root) {
						root = delNode->left;
					}
					else {
						if (delNode->parent->left == delNode) {
							delNode->parent->left = delNode->left;
						}
						if (delNode->parent->right == delNode) {
							delNode->parent->right = delNode->left;
						}
					}
					return;
				}

				//если у удаляемой вершины есть оба ребенка
				Node<T>* minNode = findMin(delNode->right);
				if (minNode == delNode->right) {
					delNode->key = minNode->key;
					minNode->parent->right = minNode->right;
				}
				else {
					delNode->key = minNode->key;
					minNode->parent->left = minNode->right;
				}
			}
		}
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
	BinTree<int> tree;

	int a;
	int key;
	
	fin >> key;

	while (fin >> a) {
		tree.add(a);
	}

	tree.deleteRight(key, tree.root);
	tree.directLeft(tree.root);
	return 0;
}

