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
	vector<int> v;
	int x;
	while (in >> x) {
		v.push_back(x);
	}

	v[1] = 12;
	v[2] = 2;
	int i = 0;
	while (v[i] != 99) {
		if (v[i] == 1) {
			v[v[i + 3]] = v[v[i + 1]] +v[ v[i + 2]];
		}
		if (v[i] == 2) {
			v[v[i + 3]] = v[v[i + 1]] * v[v[i + 2]];
		}
		i += 4;
	}

	cout << v[0];
}