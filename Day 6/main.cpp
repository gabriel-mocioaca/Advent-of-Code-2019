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

map<string, vector<string>> graph;
set<string> visited;
map<string, int> dist;

void dfs(string v, bool part2, int d) {
	visited.insert(v);
	if (v == "SAN" && part2) {
		cout << "Part2 " << ' ' << d - 2 << '\n';
		return;
	}

	for (string u : graph[v]) {
		if (visited.find(u) == visited.end()) {
			dist[u] = d;
			dfs(u, part2, d + 1);
		}
	}
}

int main() {
	
	while (!in.eof()) {
		string a, b;
		in >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	dfs("COM", false, 1);
	int sum = 0;
	for (auto it : dist) {
		sum += it.second;
	}
	cout << "Part1 " << ' ' << sum << '\n';
	visited.clear();

	dfs("YOU", true, 0);
	
}