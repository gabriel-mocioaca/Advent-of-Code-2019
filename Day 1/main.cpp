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

ifstream in("input.txt");

int main() {
	long long sum = 0;
	long long x;
	while (in >> x) {
		while (x > 0) {
			if (x / 3 - 2 > 0)
				sum += x / 3 - 2;
			x = x / 3 - 2;
		}
	}
	cout << sum;
}