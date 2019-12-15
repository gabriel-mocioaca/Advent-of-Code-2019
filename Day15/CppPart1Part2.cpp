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
using namespace std;

typedef long long ll;

ifstream in("input.txt");
ofstream out("out.txt");

bool finished = false;

ll run(vector<ll>& w, int pc, int rel_base, ll input) {
	while (!finished) {
		int op = w[pc] % 100;

		if (op == 99) {
			finished = true;
			return true;
		}

		int C = w[pc] / 100 % 10;
		int B = w[pc] / 1000 % 10;
		int A = w[pc] / 10000;
		ll par1, par2, par3;

		if (C == 0) {
			par1 = w[pc + 1];
		}
		else if (C == 1) {
			par1 = pc + 1;
		}
		else {
			par1 = w[pc + 1] + rel_base;
		}

		if (B == 0) {
			par2 = w[pc + 2];
		}
		else if (B == 1) {
			par2 = pc + 2;
		}
		else {
			par2 = w[pc + 2] + rel_base;
		}

		if (A == 0) {
			par3 = w[pc + 3];
		}
		else if (A == 1) {
			par3 = pc + 3;
		}
		else {
			par3 = w[pc + 3] + rel_base;
		}



		if (op == 1) {
			w[par3] = w[par1] + w[par2];
			pc += 4;
			continue;
		}

		if (op == 2) {
			w[par3] = w[par1] * w[par2];
			pc += 4;
			continue;
		}

		if (op == 3) {
			
			w[par1] = input;

			pc += 2;
			continue;
		}
		if (op == 4) {
			return w[par1];
			pc += 2;
			continue;
		}

		if (op == 5) {
			if (w[par1] != 0)
				pc = w[par2];
			else
				pc += 3;
			continue;
		}

		if (op == 6) {
			if (w[par1] == 0)
				pc = w[par2];
			else
				pc += 3;
			continue;
		}

		if (op == 7) {
			if (w[par1] < w[par2]) {
				w[par3] = 1;
			}
			else {
				w[par3] = 0;
			}
			pc += 4;
			continue;
		}

		if (op == 8) {
			if (w[par1] == w[par2]) {
				w[par3] = 1;
			}
			else {
				w[par3] = 0;
			}
			pc += 4;
			continue;
		}

		if (op == 9) {
			rel_base += w[par1];
			pc += 2;
		}

	}
}



map <pair<int, int>, vector<ll>> states;
map<pair<int, int>, int> game;

int d[] = { 1, 2, 3, 4 };
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int ox, oy;

void bfs(pair<pair<int, int>, int> s) {
	queue<pair<pair<int,int>, int>> q;
	set<pair<int, int>> vis;

	q.push(s);

	vis.insert(s.first);

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dist = q.front().second;

		q.pop();

		for (int k = 0; k < 4; ++k) {

			if (vis.find({ x + dx[k], y + dy[k] }) == vis.end()) {

				vector<ll> copy = states[{x, y}];
				int ans = run(copy, 0, 0, d[k]);
				if (ans == 2) {
					cout << dist << endl;
					ox = x + dx[k];
					oy = y + dy[k];
				}
				game[{ x + dx[k], y + dy[k] }] = ans;
				vis.insert({ x + dx[k], y + dy[k] });
				if (ans != 0) {
					states[{ x + dx[k], y + dy[k] }] = copy;
					q.push({{ x + dx[k], y + dy[k] }, dist + 1});
				}
			}
		}


	}
}

int max_dist = -1;
void oxygenbfs() {
	queue<pair<pair<int, int>, int>> q;
	set<pair<int, int>> vis;

	q.push({ {ox, oy}, 0 });
	vis.insert({ ox,oy });

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dist = q.front().second;

		q.pop();

		max_dist = max(max_dist, dist);

		for (int k = 0; k < 4; ++k) {

			if (vis.find({ x + dx[k], y + dy[k] }) == vis.end()) {

				vis.insert({ x + dx[k], y + dy[k] });
				if (game[{ x + dx[k], y + dy[k] } ] != 0) {
					q.push({ { x + dx[k], y + dy[k] }, dist + 1 });
				}
			}
		}


	}
}

int main() {
	vector<ll> v;
	ll x;
	int pc = 0, r = 0;
	while (in >> x) {
		v.push_back(x);
	}

	for (int i = 0; i <= 10000; ++i)
		v.push_back(0);



	states[{0, 0}] = v;

	bfs({{ 0,0 }, 1});

	for (int i = -25; i <= 25; ++i) {
		for (int j = -25; j <= 25; ++j) {
			if (game[{i, j}] == 0)
				cout << '#';
			else {
				if (game[{i, j}] == 2)
					cout << '$';
				else
					cout << '.';
			}
		}
		cout << endl;
	}

	oxygenbfs();
	cout << max_dist;
}