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

int run(vector<ll> w, ll input1, ll input2) {
	int pc = 0;
	bool finished = false;
	bool ok = true;

	while (!finished) {
		int op = w[pc] % 100;
		int C = w[pc] / 100 % 10;
		int B = w[pc] / 1000 % 10;
		if (op == 99) {
			finished = true;
			cout << "HALT\n";
		}

		if (op == 1) {
			w[w[pc + 3]] =
				(C == 0 ? w[w[pc + 1]] : w[pc + 1]) + (B == 0 ? w[w[pc + 2]] : w[pc + 2]);
			pc += 4;
			continue;
		}

		if (op == 2) {
			w[w[pc + 3]] =
				(C == 0 ? w[w[pc + 1]] : w[pc + 1]) * (B == 0 ? w[w[pc + 2]] : w[pc + 2]);
			pc += 4;
			continue;
		}

		if (op == 3) {
			if (ok) {
				w[w[pc + 1]] = input1;
				ok = false;
			}
			else {
				w[w[pc + 1]] = input2;
			}
			pc += 2;
			continue;
		}
		if (op == 4) {
			return w[w[pc + 1]];
			pc += 2;
			continue;
		}

		if (op == 5) {
			if ((C == 0 ? w[w[pc + 1]] : w[pc + 1]) != 0)
				pc = (B == 0 ? w[w[pc + 2]] : w[pc + 2]);
			else
				pc += 3;
			continue;
		}

		if (op == 6) {
			if ((C == 0 ? w[w[pc + 1]] : w[pc + 1]) == 0)
				pc = (B == 0 ? w[w[pc + 2]] : w[pc + 2]);
			else
				pc += 3;
			continue;
		}

		if (op == 7) {
			if ((C == 0 ? w[w[pc + 1]] : w[pc + 1]) < (B == 0 ? w[w[pc + 2]] : w[pc + 2])) {
				w[w[pc + 3]] = 1;
			}
			else {
				w[w[pc + 3]] = 0;
			}
			pc += 4;
			continue;
		}

		if (op == 8) {
			if ((C == 0 ? w[w[pc + 1]] : w[pc + 1]) == (B == 0 ? w[w[pc + 2]] : w[pc + 2])) {
				w[w[pc + 3]] = 1;
			}
			else {
				w[w[pc + 3]] = 0;
			}
			pc += 4;
			continue;
		}

	}
}


int main() {
	vector<ll> w;
	ll x;
	bool finished = false;
	while (in >> x) {
		w.push_back(x);
	}
	ll m = LLONG_MIN;

	int phases[] = { 0, 1, 2, 3, 4 };

	while (next_permutation(phases, phases + 5))
	{
		ll res = run(w, phases[4], run(w, phases[3], run(w, phases[2], run(w, phases[1], run(w, phases[0], 0)))));
		m = max(m, res);
		
	}

	cout << m;
}