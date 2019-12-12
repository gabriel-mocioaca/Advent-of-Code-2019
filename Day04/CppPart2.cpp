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

bool check(int x) {
	string s = to_string(x);
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] < s[i - 1])
			return false;
	}
	int cnt = 1;
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] == s[i - 1])
			cnt++;
		else {
			if (cnt == 2)
				return true;
			else
				cnt = 1;
		}
	}
	if (cnt == 2)
		return true;

	return false;
}

int main() {
	int l = 153517, r = 630395;
	int cnt = 0;

	for (int x = l; x <= r; ++x) {
		if (check(x))
			cnt++;
	}
	cout << cnt;
	
}