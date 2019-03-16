#pragma comment(linker, "/STACK:16777216")
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Block;
bool differentRooms(Block, Block);

int m, n;
vector < vector<Block> > castle;
vector <int> rooms;

ifstream fin("in.txt");
ofstream fout("out.txt");

struct Block {
	int i, j, code, room, used;
	vector<Block*> friends;

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
		used = true;
		room = roomNumber;
		rooms[roomNumber]++;
		for (int i = 0; i < friends.size(); i++) {
			if (!friends[i]->used) {
				friends[i]->burn(roomNumber);
			}
		}
	}

	int maxDoubleRoomSquare() {
		int maxSq = 0;
		if (i > 0) {
			if (maxSq < rooms[this->room] + rooms[castle[i - 1][j].room] && differentRooms(*this, castle[i - 1][j])) {
				maxSq = rooms[this->room] + rooms[castle[i - 1][j].room];
			}
		}
		if (j > 0) {
			if (maxSq < rooms[this->room] + rooms[castle[i][j - 1].room] && differentRooms(*this, castle[i][j - 1])) {
				maxSq = rooms[this->room] + rooms[castle[i][j - 1].room];
			}
		}
		if (i < m - 1) {
			if (maxSq < rooms[this->room] + rooms[castle[i + 1][j].room] && differentRooms(*this, castle[i + 1][j])) {
				maxSq = rooms[this->room] + rooms[castle[i + 1][j].room];
			}
		}
		if (j < n - 1) {
			if (maxSq < rooms[this->room] + rooms[castle[i][j + 1].room] && differentRooms(*this, castle[i][j + 1])) {
				maxSq = rooms[this->room] + rooms[castle[i][j + 1].room];
			}
		}
		return maxSq;
	}
};

bool differentRooms(Block b1, Block b2) {
	return b1.room != b2.room;
}

int main()
{
	//reading data
	fin >> m >> n;

	for (int i = 0; i < m; i++) {
		vector<Block> tmpVect;
		for (int j = 0; j < n; j++) {
			Block newBlock(i, j);
			fin >> newBlock.code;
			tmpVect.push_back(newBlock);
		}
		castle.push_back(tmpVect);
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
				castle[i][j].burn(rooms.size() - 1);
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