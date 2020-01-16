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
typedef pair<int, int> pii;


ifstream in("input.txt");
ofstream out("out.txt");

vector<string> mp;

pii A, Z;

int row[] = { -1,0,1,0 };
int col[] = { 0,1,0,-1 };

int dp[130][130][30];

struct node {
	int x, y;
	int dist;
	int lvl;
};

map<pii, pii> portals;
map<pair<char, char>, vector<pii>> portals_list;


void bfs(pii start, pii finish, int part) {
	queue<node> q;
	q.push({ start.first, start.second, 0, 0 });
	vector<vector<vector<bool>>> vis(130, vector<vector<bool>>(130, vector<bool>(130)));

	while (!q.empty()) {
		node nod = q.front();
		q.pop();

		if (vis[nod.x][nod.y][nod.lvl] == true) {
			continue;
		}

		vis[nod.x][nod.y][nod.lvl] = true;

		if (nod.x == finish.first && nod.y == finish.second && nod.lvl == 0) {
			cout << nod.dist << endl;
			break;
		}

		for (int k = 0; k < 4; ++k) {
			if (mp[nod.x + row[k]][nod.y + col[k]] == '.') {
				q.push({ nod.x + row[k], nod.y + col[k], nod.dist + 1, nod.lvl });
			}
		}

		if (portals.find({ nod.x, nod.y }) != portals.end()) {
			if (part == 1) {
				q.push({ portals[{ nod.x, nod.y }].first, portals[{ nod.x, nod.y }].second, nod.dist + 1, nod.lvl});
			}
			else {
				if (((3 <= nod.x) && (nod.x < mp.size() - 3)) && ((3 <= nod.y) && (nod.y < mp[0].size() - 3))) {
					q.push({ portals[{ nod.x, nod.y }].first, portals[{ nod.x, nod.y }].second, nod.dist + 1, nod.lvl + 1 });
				}
				else {
					if (nod.lvl > 0)
						q.push({ portals[{ nod.x, nod.y }].first, portals[{ nod.x, nod.y }].second, nod.dist + 1, nod.lvl - 1 });
				}
			}
		}
	}
}

bool is_char(int x, int y) {
	return ((mp[x][y] >= 'A') && (mp[x][y] <= 'Z'));
}
bool is_point(int x, int y) {
	return (mp[x][y] == '.');
}

void add_portal(int dir, int x, int y) {
	switch (dir) {
	case 0:
		portals_list[{mp[x - 1][y], mp[x][y]}].push_back({ x + 1,y });
		break;
	case 1:
		portals_list[{mp[x][y - 1], mp[x][y]}].push_back({ x,y + 1 });
		break;
	case 2:
		portals_list[{mp[x][y], mp[x + 1][y]}].push_back({ x - 1,y });
		break;
	case 3:
		portals_list[{mp[x][y], mp[x][y + 1]}].push_back({ x,y - 1 });
		break;
	}
}

void read() {
	string s;
	while (!in.eof()) {
		getline(in, s);
		mp.push_back(s);
	}

	for (int i = 1; i < mp.size() - 1; ++i) {
		for (int j = 1; j < mp[0].size() - 1; ++j) {
			if (is_char(i - 1, j) && is_char(i, j) && is_point(i + 1, j))
				add_portal(0, i, j);
			if (is_char(i, j - 1) && is_char(i, j) && is_point(i, j + 1))
				add_portal(1, i, j);
			if (is_char(i + 1, j) && is_char(i, j) && is_point(i - 1, j))
				add_portal(2, i, j);
			if (is_char(i, j + 1) && is_char(i, j) && is_point(i, j - 1))
				add_portal(3, i, j);
		}
	}
	A = portals_list[{'A', 'A'}][0];
	Z = portals_list[{'Z', 'Z'}][0];
	portals_list.erase({ 'A', 'A' });
	portals_list.erase({ 'Z', 'Z' });

	for (auto it : portals_list) {
		portals[it.second[0]] = it.second[1];
		portals[it.second[1]] = it.second[0];
	}

}

int main() {

	read();
	cout << "AA:" << A.first << ' ' << A.second << endl;
	cout << "ZZ:" << Z.first << ' ' << Z.second << endl;
	cout << "Part 1: "; bfs(A, Z, 1);
	cout << "Part 2: "; bfs(A, Z, 2);
}