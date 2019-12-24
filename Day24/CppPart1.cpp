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


vector<string> mp;
set<unsigned long long> vis;

char nx[5][5];

int count(int x, int y) {
	int cnt = 0;
	if (x > 0) {
		cnt += (mp[x - 1][y] == '#');
	}
	if (x < 4) {
		cnt += (mp[x + 1][y] == '#');
	}
	if (y > 0) {
		cnt += (mp[x][y - 1] == '#');
	}
	if (y < 4) {
		cnt += (mp[x][y + 1] == '#');
	}
	return cnt;
}

int main() {
	string s;
	while (!in.eof()) {
		in >> s;
		mp.push_back(s);
	}



	while (1) {
		
		bitset<25> cur;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (mp[i][j] == '#') {
					cur[i * 5 + j] = true;
				}
			}
		}
		if (vis.find(cur.to_ullong()) != vis.end()) {
			cout << cur.to_ullong();
			return 0;
		}
		else {
			vis.insert(cur.to_ullong());
		}

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				int cnt = count(i, j);
				if (mp[i][j] == '#') {
					if (cnt != 1) {
						nx[i][j] = '.';
					}
					else {
						nx[i][j] = '#';
					}
				}

				if (mp[i][j] == '.') {
					if (cnt == 1 || cnt == 2) {
						nx[i][j] = '#';
					}
					else {
						nx[i][j] = '.';
					}
				}
				
			}
		}
		
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
				mp[i][j] = nx[i][j];
	}

}