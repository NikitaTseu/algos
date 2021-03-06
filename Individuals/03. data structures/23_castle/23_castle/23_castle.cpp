#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Block;

int m, n;
vector < vector<Block> > castle(1001);
vector <int> rooms;
queue<Block*> q;

ifstream fin("in.txt");
ofstream fout("out.txt");

struct Block {
	int i, j, code, room, used;
	vector<Block*> friends;

	Block() : i(-1), j(-1), used(false), room(-1), code(-1), friends(NULL) {};

	Block(int i, int j) : i(i), j(j), used(false), room(-1), code(-1), friends(NULL) {};

	void parseCode() {
		int a = code;
		vector<bool> v(4, true);
		if (a >= 8) {
			a -= 8;
			v[0] = false;
		}
		if (a >= 4) {
			a -= 4;
			v[1] = false;
		}
		if (a >= 2) {
			a -= 2;
			v[2] = false;
		}
		if (a >= 1) {
			a -= 1;
			v[3] = false;
		}
		
		if (v[0]) { friends.push_back(&castle[i + 1][j]); }
		if (v[1]) { friends.push_back(&castle[i][j + 1]); }
		if (v[2]) { friends.push_back(&castle[i - 1][j]); }
		if (v[3]) { friends.push_back(&castle[i][j - 1]); }
	}

	void burn(int roomNumber) {
		for (int i = 0; i < friends.size(); i++) {
			if (!friends[i]->used) {
				friends[i]->used = true;
				friends[i]->room = roomNumber;
				rooms[roomNumber]++;
				q.push(friends[i]);
			}
		}
		q.pop();
	}

	int maxDoubleRoomSquare() {
		int maxSq = 0;
		if (i > 0) {
			if (maxSq < rooms[this->room] + rooms[castle[i - 1][j].room] && this->room != castle[i - 1][j].room) {
				maxSq = rooms[this->room] + rooms[castle[i - 1][j].room];
			}
		}
		if (j > 0) {
			if (maxSq < rooms[this->room] + rooms[castle[i][j - 1].room] && this->room != castle[i][j - 1].room) {
				maxSq = rooms[this->room] + rooms[castle[i][j - 1].room];
			}
		}
		if (i < m - 1) {
			if (maxSq < rooms[this->room] + rooms[castle[i + 1][j].room] && this->room != castle[i + 1][j].room) {
				maxSq = rooms[this->room] + rooms[castle[i + 1][j].room];
			}
		}
		if (j < n - 1) {
			if (maxSq < rooms[this->room] + rooms[castle[i][j + 1].room] && this->room != castle[i][j + 1].room) {
				maxSq = rooms[this->room] + rooms[castle[i][j + 1].room];
			}
		}
		return maxSq;
	}
};

int main()
{
	//reading data
	fin >> m >> n;

	for (int i = 0; i < m; i++) {
		vector<Block> tmpVect(1001);
		for (int j = 0; j < n; j++) {
			Block newBlock(i, j);
			fin >> newBlock.code;
			tmpVect[j] = newBlock;
		}
		castle[i] = tmpVect;
	}

	//parcing codes (get info about walls)
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			castle[i][j].parseCode();
		}
	}

	//setting fire to the rooms!!!
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!(castle[i][j].used)) {
				rooms.push_back(0);
				q.push(&castle[i][j]);
				castle[i][j].used = true;
				castle[i][j].room = rooms.size() - 1;
				rooms[rooms.size() - 1]++;
				while (!q.empty()) {
					q.front()->burn(rooms.size() - 1);
				}
			}
		}
	}

	int maxSq1 = 0;
	for (int i = 0; i < rooms.size(); i++) {
		if (maxSq1 < rooms[i]) {
			maxSq1 = rooms[i];
		}
	}

	int maxSq2 = maxSq1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (maxSq2 < castle[i][j].maxDoubleRoomSquare()) {
				maxSq2 = castle[i][j].maxDoubleRoomSquare();
			}
		}
	}

	fout << rooms.size() << endl << maxSq1 << endl << maxSq2;
	return 0;
}