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
typedef unsigned long long ull;
#define LEN 26

ifstream in("test.txt");
ofstream out("out.txt");

vector<string> m;
map<char, pair<int, int>> keys;
map<char, pair<int, int>> doors;
int sx, sy;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

bool in_bounds(int x, int y) {
	return x >= 0 && x < m.size() && y >= 0 && y < m[0].size();
}

typedef tuple<int, int, ull> node;



int bfs(node start) {
	queue<pair<node, int>> q;
	set<node> vis;
	q.push({ start, 0 });

	while (!q.empty()) {
		node cur = q.front().first;
		int dist = q.front().second;
		q.pop();
		int x = get<0>(cur);
		int y = get<1>(cur);
		ull bm = get<2>(cur);
		bitset<LEN> bs(bm);
		//cout << x << ' ' << y << ' ' << bm << endl;

		

		if (bs.all()) {
			return dist;
		}
		
		for (int k = 0; k < 4; ++k) {
			if (!in_bounds(x + dx[k], y + dy[k]))
				continue;
			if (vis.find({ x + dx[k], y + dy[k], bm }) != vis.end())
				continue;
			if (m[x + dx[k]][y + dy[k]] == '#')
				continue;
			if ((m[x + dx[k]][ y + dy[k]] >= 'A' && m[x + dx[k]][y + dy[k]] <= 'Z') && !bs[m[x + dx[k] ][y + dy[k]] - 'A'])
				continue;

			//cout << x + dx[k] << ' ' << y + dy[k] << ' ' << bs << ' ' <<  dist << endl;

			bitset<LEN> newbs = bs;

			if (m[x + dx[k]][y + dy[k]] >= 'a' && m[x + dx[k]][y + dy[k]] <= 'z' && !bs[m[x + dx[k]][y + dy[k]] - 'a']) {
				newbs [m[x + dx[k]][y + dy[k]] - 'a'] = 1;
			}
			vis.insert({ x + dx[k], y + dy[k], newbs.to_ullong() });
			q.push({ {x + dx[k], y + dy[k], newbs.to_ullong()}, dist + 1 });
				
		}
	}
	return -1;
}



int main() {
	string s;
	vector<string> org;
	while (!in.eof()) {
		in >> s;
		org.push_back(s);
	}

	m = org;

	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[0].size(); ++j) {
			if (m[i][j] == '@') {
				sx = i;
				sy = j;
				m[i][j] = '.';
			}
			if (m[i][j] >= 'a' && m[i][j] <= 'z') {
				keys[m[i][j]] = { i,j };
			}
			if (m[i][j] >= 'A' && m[i][j] <= 'Z') {
				doors[m[i][j]] = { i,j };
			}
		}
	}
	
	cout << bfs({ sx, sy, 0ll });

}