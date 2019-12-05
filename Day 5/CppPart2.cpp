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

int main() {
	vector<int> w;
	int x, input, pc = 0;
	bool finished = false;
	while (in >> x) {
		w.push_back(x);
	}
	
	while (!finished) {
		int op = w[pc] % 100;
		int C = w[pc] / 100 % 10;
		int B = w[pc] / 1000 % 10;
		if (op == 99) {
			finished = true;
			cout << "HALT\n";
			continue;
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
			w[w[pc + 1]] = 5;
			pc += 2;
			continue;
		}
		if (op == 4) {
			cout << w[w[pc + 1]] << '\n';
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