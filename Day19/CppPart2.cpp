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
bool run(vector<ll> w, int pc, queue<ll>& input, deque<ll>& output) {

	int rel_base = 0;
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
	int pc = 0;
	queue<ll> input;
	deque<ll> output;
	while (in >> x) {
		v.push_back(x);
	}


	for (int i = 0; i <= 10000; ++i)
		v.push_back(0);


	int cnt = 0;

	vector<vector<int>> mat;
	ll len = 2000;
	ll slen = 100;
	for (ll i = 0; i < len; ++i) {
		vector<int> s;
		for (ll j = 0; j < len; ++j) {
			input.push(i);
			input.push(j);
			run(v, pc, input, output);
			s.push_back(output.front());
			output.pop_front();
		}
		mat.push_back(s);

	}
	cout << "YES";
	
	int i = 99;
	int j = 0;

	while (1) {
		while (mat[i][j] == 0)
			++j;

		cout << i << ' ' << j << endl;
		if (mat[i - 99][j + 99]) {
			cout << i - 99 << ' ' << j << endl;
			return 0;

		}

		if (mat[i][j] == 1) i++;

	}


	
}