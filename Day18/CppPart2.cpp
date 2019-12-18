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
typedef tuple<int, int, ull> node;
#define LEN 26

ifstream in("input2.txt");
ofstream out("out.txt");

vector<string> m;
int sx, sy;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

bool in_bounds(int x, int y) {
	return x >= 0 && x < m.size() && y >= 0 && y < m[0].size();
}

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
			if ((m[x + dx[k]][y + dy[k]] >= 'A' && m[x + dx[k]][y + dy[k]] <= 'Z') && !bs[m[x + dx[k]][y + dy[k]] - 'A'])
				continue;


			bitset<LEN> newbs = bs;

			if (m[x + dx[k]][y + dy[k]] >= 'a' && m[x + dx[k]][y + dy[k]] <= 'z' && !bs[m[x + dx[k]][y + dy[k]] - 'a']) {
				newbs[m[x + dx[k]][y + dy[k]] - 'a'] = 1;
			}
			vis.insert({ x + dx[k], y + dy[k], newbs.to_ullong() });
			q.push({ {x + dx[k], y + dy[k], newbs.to_ullong()}, dist + 1 });

		}
	}
	return -1;
}

int main() {
	string s;
	while (!in.eof()) {
		in >> s;
		m.push_back(s);
	}

	sx = sy = m.size() / 2;

	set<char> key[4];
	set<char> door[4];
	m[sx - 1][sy - 1] = m[sx - 1][sy + 1] = m[sx + 1][sy - 1] = m[sx + 1][sy + 1] = '.';
	m[sx][sy] = m[sx][sy + 1] = m[sx + 1][sy] = m[sx][sy - 1] = m[sx][sy] =  '#';

	cout << sx + 1 << ' ' << sy - 1 << endl;

	for (auto it : m)
		cout << it << endl;


	int x[] = { sx - 1, sx - 1, sx + 1, sx + 1 };
	int y[] = { sy - 1, sy + 1, sy - 1, sy + 1 };

	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[0].size(); ++j) {
			if (m[i][j] >= 'a' && m[i][j] <= 'z') {
				if (i < x[0] && j < y[0])
					key[0].insert(m[i][j]);
				if (i < x[0] && j > y[0])
					key[1].insert(m[i][j]);
				if (i > x[0] && j < y[0])
					key[2].insert(m[i][j]);
				if (i > x[0] && j > y[0])
					key[3].insert(m[i][j]);
			}
		}
	}
	int dist = 0;

	for (int k = 0; k < 4; ++k) {
		bitset<LEN> doors;
		doors.set();
		
		for (auto it : key[k])
			doors[it - 'a'] = 0;
		
		dist += bfs({ x[k], y[k] , doors.to_ullong() });
	}

	cout << dist;
}