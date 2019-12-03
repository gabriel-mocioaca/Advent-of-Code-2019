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

ifstream in("CppIn.txt");

int main() {
	vector<int> w;
	int x;
	while (in >> x) {
		w.push_back(x);
	}

	for (int k = 0; k < 100; k++) {
		for (int l = 0; l < 100; l++) {
			vector<int> v = w;
			v[1] = k;
			v[2] = l;
			int i = 0;
			while (v[i] != 99) {
				if (v[i] > v.size() || v[i + 1] > v.size() || v[i + 2] > v.size() || v[i + 3] > v.size())
					break;
				if (v[i] == 1) {
					v[v[i + 3]] = v[v[i + 1]] + v[v[i + 2]];
				}
				if (v[i] == 2) {
					v[v[i + 3]] = v[v[i + 1]] * v[v[i + 2]];
				}
				i += 4;
			}
			if (v[i] > v.size() || v[i + 1] > v.size() || v[i + 2] > v.size() || v[i + 3] > v.size())
				continue;

			if (v[0] == 19690720)
				cout << k << ' ' << l;
		}
	}

	
}