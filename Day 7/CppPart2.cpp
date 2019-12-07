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

bool run(vector<ll> &w, int &pc, queue<ll> &input, queue<ll> &output) {
	bool finished = false;

	while (!finished) {
		int op = w[pc] % 100;
		int C = w[pc] / 100 % 10;
		int B = w[pc] / 1000 % 10;
		if (op == 99) {
			finished = true;
			return true;
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
			if (input.empty()) {
				return false;
			}
			w[w[pc + 1]] = input.front();
			input.pop();

			pc += 2;
			continue;
		}
		if (op == 4) {
			output.push(w[w[pc + 1]]);
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
	vector<ll> v;
	ll x;
	bool finished = false;
	while (in >> x) {
		v.push_back(x);
	}
	ll m = LLONG_MIN;

	int phases[] = { 5, 6, 7, 8, 9 };

	while (next_permutation(phases, phases + 5))
	{
		vector<vector<ll>> w(5);
		for (int i = 0; i < 5; ++i) {
			w[i] = v;
		}
		vector<queue<ll>> input_buffer(5);
		vector<int> pc(5, 0);
		bool halt = false;

		input_buffer[0].push(phases[0]);
		input_buffer[0].push(0);
		input_buffer[1].push(phases[1]);
		input_buffer[2].push(phases[2]);
		input_buffer[3].push(phases[3]);
		input_buffer[4].push(phases[4]);

		while (!halt) {
			run(w[0], pc[0], input_buffer[0], input_buffer[1]);
			run(w[1], pc[1], input_buffer[1], input_buffer[2]);
			run(w[2], pc[2], input_buffer[2], input_buffer[3]);
			run(w[3], pc[3], input_buffer[3], input_buffer[4]);
			if (run(w[4], pc[4], input_buffer[4], input_buffer[0]))
				halt = true;
		}
		m = max(m, input_buffer[0].front());
	}

	cout << m;
}