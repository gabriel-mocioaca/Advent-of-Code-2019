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

ifstream in("input1.txt");
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
	/*vector<ll> v;
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

	string s;

	run(v, pc, input, output);

	while (!output.empty()) {
		char c = char(output.front());
		output.pop_front();
		s.push_back(c);
	}
	cout << s;*/
	vector<string> m;
	string s;
	while (in >> s)
		m.push_back(s);
	int sum = 0;


	for (int i = 1; i < m.size() - 1; ++i) {
		for (int j = 1; j < m[0].size() - 1; ++j) {
			if (m[i][j] == '#' && m[i - 1][j] == '#' && m[i + 1][j] == '#' && m[i][j - 1] == '#' && m[i][j + 1] == '#') {
				sum += i * j;
			}
		}
	}
	cout << sum;
}