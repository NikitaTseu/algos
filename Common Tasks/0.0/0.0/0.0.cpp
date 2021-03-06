#include "stdafx.h"
#include <fstream>
#include <set>

using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	set<long long int> mySet;

	long long int sum = 0;
	long long int a;

	while (fin >> a) {
		mySet.insert(a);
	}

	for (auto it = mySet.begin(); it != mySet.end(); it++) {
		sum += *it;
	}

	fout << sum;
    return 0;
}

