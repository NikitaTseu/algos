#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue> 

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

template <typename T> class Node {
public:
	T key;
	Node* left;
	Node* right;
	Node* parent;
	int height; //высота
	int rank; //количество потомков

	Node(T val) {
		key = val;
		left = NULL;
		right = NULL;
		parent = NULL;
		rank = 0;
		height = 0;
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

const bool operator < (const Node<int> &n1, const Node<int> &n2)
{
	return n1.key < n2.key;
}

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

	int reverseHeight(Node<T>* start) {
		if (start != NULL) {
			//start->height = max(reverseHeight(start->left), reverseHeight(start->right)) + 1;
			//return start->height;
			return max(reverseHeight(start->left), reverseHeight(start->right)) + 1;
		}
		else {
			return -1;
		}
	}

	int directDepth(Node<T>* start) {
		int h = 0;
		while (start != root) {
			start = start->parent;
			h++;
		}
		return h;
	}

	int reverseRank(Node<T>* start) {
		if (start != NULL) {
			start->rank = reverseRank(start->left) + reverseRank(start->right) + 2;
			return start->rank;
		}
		else {
			return -1;
		}
	}
};

int main()
{
	BinTree<int> tree;

	int a;
	while (fin >> a) {
		tree.add(a);
	}

	int h = tree.reverseHeight(tree.root);
	int mid = h / 2;
	tree.reverseRank(tree.root);

	queue<Node<int>*> BFSQueue;
	vector<Node<int>*> goodNodes;
	BFSQueue.push(tree.root);
	while (!BFSQueue.empty()) {
		if (h - tree.directDepth(BFSQueue.front()) != mid) {
			if (BFSQueue.front()->left != NULL) {
				BFSQueue.push(BFSQueue.front()->left);
			}
			if (BFSQueue.front()->right != NULL) {
				BFSQueue.push(BFSQueue.front()->right);
			}
		}
		else {
			if (BFSQueue.front()->left != NULL) {
				BFSQueue.push(BFSQueue.front()->left);
			}
			if (BFSQueue.front()->right != NULL) {
				BFSQueue.push(BFSQueue.front()->right);
			}
			if ((BFSQueue.front()->left != NULL) && ((BFSQueue.front()->right == NULL) || BFSQueue.front()->left->rank > BFSQueue.front()->right->rank)) {
				goodNodes.push_back(BFSQueue.front());
			}
		}
		BFSQueue.pop();
	}

	if (goodNodes.size() % 2 != 0) {
		//sort(goodNodes.begin(), goodNodes.end());
		tree.deleteRight(goodNodes[goodNodes.size() / 2]->key, tree.root);
	}
	
	tree.directLeft(tree.root);
	return 0;
}

