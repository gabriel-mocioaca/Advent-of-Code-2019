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

int rel_base = 0;

bool run(vector<ll>& w, int& pc, queue<ll>& input, deque<ll>& output) {
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
			if (input.empty()) {
				return false;
			}
			w[par1] = input.front();
			input.pop();

			pc += 2;
			continue;
		}
		if (op == 4) {
			output.push_back(w[par1]);
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


int main() {
	vector<ll> v;
	ll x;
	int pc = 0;
	queue<ll> input;
	deque<ll> output;
	while (in >> x) {
		v.push_back(x);
	}


	input.push(0);

	for (int i = 0; i <= 10000; ++i)
		v.push_back(0);

	v[0] = 2;
	
	map<pair<int, int>, int> game;
	ll y, id;

	while (!finished) {
		run(v, pc, input, output);

		int ballx, padx;

		while (!output.empty()) {
			x = output.front();
			output.pop_front();
			y = output.front();
			output.pop_front();
			id = output.front();
			output.pop_front();
			game[{x, y}] = id;

			if (id == 3) {
				padx = x;
			}

			if (id == 4) {
				ballx = x;
			}

			if (x == -1 && y == 0)
				cout << id << '\n';
		}

		/*for (int j = -1; j < 25; ++j) {
			for (int i = -1; i < 50; ++i) {
				switch (game[{i, j}]) {
				case 0: cout << ' '; break;
				case 1: cout << '@'; break;
				case 2: cout << '#'; break;
				case 3: cout << '_'; break;
				case 4: cout << '*'; break;
				}
			}
			cout << endl;
		}*/
		//cout << padx << ' ' << ballx << ' ' << (padx < ballx ? -1 : (padx > ballx ? 1 : 0)) << endl;
		input.push( padx < ballx ? 1 : (padx > ballx ? -1 : 0));
	}
	
	//cout << m[2];
}