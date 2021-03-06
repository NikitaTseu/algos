#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, k, snowBegin, snowEnd;
vector<int> street;

ifstream fin("in.txt");
ofstream fout("out.txt");

//рассчет минимального времени на зачистку линейного куска (конечная точка не важна)
int findMinTime(int start, int end) {
	if (start == end) {
		return 0;
	}
	if (start < end) {
		int t1 = 0;
		int t2 = (end - start) * 2;
		int tmin = t2;
		for (int i = 0; i < end - start; i++) {
			t2 -= 2;
			if (street[start + i] == 3) {
				t1 += 3;
			}
			else {
				t1 += 1;
			} 
			tmin = min(tmin, t1 + t2);
		}
		return tmin;
	}
	if (start > end) {
		int t1 = 0;
		int t2 = (start - end) * 2;
		int tmin = t2;
		for (int i = 0; i < start - end; i++) {
			t2 -= 2;
			if (street[start - i - 1] == 3) {
				t1 += 3;
			}
			else {
				t1 += 1;
			}
			tmin = min(tmin, t1 + t2);
		}
		return tmin;
	}
}

int main()
{
	//считываем данные
	fin >> n >> k;

	for (int i = 0; i < n; i++) {
		int a, b;
		fin >> a >> b;
		if (a == 1 && b == 1) {
			street.push_back(3);
		}
		else {
			street.push_back(a + b);
		}
	}

	//определяем границы снега
	snowBegin = -1;
	snowEnd = -1;

	for (int i = 0; i < n; i++) {
		if (street[i] != 0) {
			if (snowBegin == -1) {
				snowBegin = i;
			}
			snowEnd = i + 1;
		}
	}

	//ищем минимальное время
	int mintime = -1;
	if (k <= snowBegin) {
		mintime = findMinTime(k, snowEnd);
	}
	if (k >= snowEnd) {
		mintime = findMinTime(k, snowBegin);
	}
	if (k > snowBegin && k < snowEnd) 
	{
		int t1 = 2 * (k - snowBegin) + findMinTime(k, snowEnd);
		int t2 = 2 * (snowEnd - k) + findMinTime(k, snowBegin);
		mintime = min(t1, t2);
	}

	fout << mintime;
    return 0;
}

