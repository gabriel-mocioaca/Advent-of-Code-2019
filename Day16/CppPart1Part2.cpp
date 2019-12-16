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

vector<int> get_pattern(int step, int len) {
	vector<int> local_pattern;
	for (int i = 1; i <= step - 1; ++i) {
		if (local_pattern.size() == len) {
			return local_pattern;
		}
		local_pattern.push_back(0);
	}
	while (1) {
		for (int i = 1; i <= step; ++i) {
			if (local_pattern.size() == len) {
				return local_pattern;
			}
			local_pattern.push_back(1);
		}
		for (int i = 1; i <= step; ++i) {
			if (local_pattern.size() == len) {
				return local_pattern;
			}
			local_pattern.push_back(0);
		}
		for (int i = 1; i <= step; ++i) {
			if (local_pattern.size() == len) {
				return local_pattern;
			}
			local_pattern.push_back(-1);
		}
		for (int i = 1; i <= step; ++i) {
			if (local_pattern.size() == len) {
				return local_pattern;
			}
			local_pattern.push_back(0);
		}
	}
}

string update1(string s, int step) {
	int len = s.size();
	string ss;

	for (int it = 1; it <= len; it++) {
		vector<int> pattern = get_pattern(it, len);
		int sum = 0;
		for (int iti = 0; iti < len; iti++) {
			int c = s[iti] - '0';
			sum += c * pattern[iti];
		}
		ss.push_back('0' + (abs(sum) % 10));
		//cout << sum << ' ';
	}
	return ss;
}


int main() {
	string s, s1, s2;
	in >> s;

	s1 = s;
	for (int i = 1; i <= 100; ++i) {
		s1 = update1(s1, i);
	}
	cout << s1.substr(0, 8) << endl;


	int offset = 5970157;
	for (int i = 0; i < 10000; ++i) {
		s2 += s;
	}
	cout << s2.size() << endl;

	for (int i = 1; i <= 100; ++i) {
		vector<int> dp;
		for (auto it : s2) {
			int c = it - '0';
			if (!dp.empty()) 
				c += dp.back();
			dp.push_back(c);
		}

		for (int it = s2.size() / 2; it < s2.size(); ++it) {
			s2[it] = '0' + ((dp[s2.size() - 1] - dp[it - 1]) % 10);
		}
		
	}
	cout << s2.substr(offset, 8) << endl;
	
}