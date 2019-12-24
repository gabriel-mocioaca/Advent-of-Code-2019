#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long ll;


ifstream in("input.txt");
ofstream out("out.txt");

int mp[1000][5][5], nx[1000][5][5];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0 ,-1 };

int count(int lvl, int x, int y) {
	int cnt = 0;
	for (int k = 0; k < 4; ++k) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx < 0 || ny < 0 || nx > 4 || ny > 4)
			continue;
		if (nx == 2 && ny == 2)
			continue;
		cnt += mp[lvl][nx][ny];
	}

	if (x == 0) {
		cnt += (mp[lvl - 1][1][2]);
	}
	if (x == 4) {
		cnt += (mp[lvl - 1][3][2]);
	}
	if (y == 0) {
		cnt += (mp[lvl - 1][2][1]);
	}
	if (y == 4) {
		cnt += (mp[lvl - 1][2][3]);
	}
	if (x == 1 && y == 2) {
		for (int j = 0; j < 5; ++j) {
			cnt += mp[lvl + 1][0][j];
		}
	}
	if (x == 3 && y == 2) {
		for (int j = 0; j < 5; ++j) {
			cnt += mp[lvl + 1][4][j];
		}
	}
	if (y == 1 && x == 2) {
		for (int i = 0; i < 5; i++) {
			cnt += mp[lvl + 1][i][0];
		}
	}
	if (y == 3 && x == 2) {
		for (int i = 0; i < 5; i++) {
			cnt += mp[lvl + 1][i][4];
		}
	}
	return cnt;
}

int main() {
	string s;
	int mid = 500;
	vector<string> ss;
	while (!in.eof()) {
		in >> s;
		ss.push_back(s);
	}

	for (int l = 0; l < 1000; ++l)
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
				mp[l][i][j] = 0;

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			mp[mid][i][j] = (ss[i][j] == '#');
		}
	}

	int l = mid - 1;
	int r = mid + 1;
	

	for (int k = 0; k < 200; ++k) {
		for (int lvl = l; lvl <= r; ++lvl) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j){
					int cnt = count(lvl, i, j);
					if (mp[lvl][i][j]) {
						if (cnt == 1)
							nx[lvl][i][j] = 1;
						else
							nx[lvl][i][j] = 0;
					}
					if (!mp[lvl][i][j]) {
						if (cnt == 1 || cnt == 2)
							nx[lvl][i][j] = 1;
						else
							nx[lvl][i][j] = 0;
					}
				}
			}
			nx[lvl][2][2] = 0;
		}
		for (int lvl = l; lvl <= r; ++lvl) {
			for (int i = 0; i < 5; ++i)
				for (int j = 0; j < 5; ++j)
					mp[lvl][i][j] = nx[lvl][i][j];
		}

		l--;
		r++;
	}

	int bugs = 0;

	for (int lvl = l; lvl <= r; ++lvl) 
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
				bugs += mp[lvl][i][j];
	
	cout << bugs;
}