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
bool run(vector<ll> &w, int &rel_base, int &pc, queue<ll>& input, deque<ll>& output) {

	
	bool finished = false;

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
	while (in >> x) {
		v.push_back(x);
	}


	for (int i = 0; i <= 10000; ++i)
		v.push_back(0);

	ll natx = 0, naty = 0, lx = -1, ly = -1;

	vector<vector<ll>> intcode(50);
	vector<int> pc(50, 0);
	vector<int> r(50, 0);
	vector<queue<ll>> input(50);
	vector<deque<ll>> output(50);
	bool part1 = true;

	for (int i = 0; i < 50; ++i)
		intcode[i] = v;

	for (int i = 0; i < 50; ++i) {
		input[i].push(i);
		input[i].push(-1);
	}
	for (int i = 0; i < 50; ++i) {
		run(intcode[i], r[i], pc[i], input[i], output[i]);
	}
	while (1) {
		for (int i = 0; i < 50; ++i) {
			run(intcode[i], r[i], pc[i], input[i], output[i]);
		}
		for (int i = 0; i < 50; ++i) {
			while(output[i].size()) {
				ll adr, x, y;
				adr = output[i].front(); output[i].pop_front();
				x = output[i].front(); output[i].pop_front();
				y = output[i].front(); output[i].pop_front();
			
				if (adr == 255) {
					natx = x;
					naty = y;
					if (part1) {
						cout << y << endl;
						part1 = false;
					}
				}
				else {
					input[adr].push(x);
					input[adr].push(y);
				}
			}
		}
		bool idle = true;
		for (int i = 0; i < 50; ++i) {
			if (input[i].size() == 0)
				input[i].push(-1);
			else
				idle = false;
		}
		if (idle) {
			input[0].pop();
			if (natx == lx && naty == ly) {
				cout << naty;
				return 0;
			}
			lx = natx;
			ly = naty;
			input[0].push(natx);
			input[0].push(naty);
		}
	}

}