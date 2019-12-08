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
	string s;
	in >> s;
	int x = 25, y = 6;
	int len = x * y;
	int pos = 0;
	int n0, n1, n2, min0 = INT_MAX;

	vector<string> ss;
	while (pos < s.size()) {
		string c = s.substr(pos, len);
		ss.push_back(c);
		n0 = count(c.begin(), c.end(), '0');
		if (n0 < min0) {
			n1 = count(c.begin(), c.end(), '1');
			n2 = len - n1 - n0;
			min0 = n0;
		}
		pos += len;
	}

	cout << "Part1:" << n1 * n2 << '\n';

	string ans;

	for (int i = 0; i < len; ++i) {
		int j = 0;
		while (ss[j][i] == '2')j++;
		ans.push_back(ss[j][i]);
	}

	cout << "Part2:\n";
	int k = 0;
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			if (ans[k] == '1')
				cout << '#';
			else
				cout << ' ';
			k++;
		}
		cout << endl;
	}

}