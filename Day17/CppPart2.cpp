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

			//cout << w[par1] << '\n';
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

	for (int i = 0; i <= 10000; ++i)
		v.push_back(0);

	// by hand 
	string m = "A,B,A,C,A,B,C,A,B,C\n";
	string m1 = "R,8,R,10,R,10\n";
	string m2 = "R,4,R,8,R,10,R,12\n";
	string m3 = "R,12,R,4,L,12,L,12\n";

	for (int i = 0; i < m.size(); ++i) {
		input.push(ll(m[i]));
	}
	for (int i = 0; i < m1.size(); ++i) {
		input.push(ll(m1[i]));
	}
	for (int i = 0; i < m2.size(); ++i) {
		input.push(ll(m2[i]));
	}
	for (int i = 0; i < m3.size(); ++i) {
		input.push(ll(m3[i]));
	}

	input.push(ll('n'));
	input.push(ll('\n'));

	v[0] = 2;

	run(v, pc, input, output);


	cout << output.back();
}