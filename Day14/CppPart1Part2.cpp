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

ifstream in("test.txt");
ofstream out("out.txt");



map <string, vector<pair<string, ll>>> eq;
map <string, ll> at_once;
map <string, ll> leftovers;

ll solve(string chem, ll amm) {
	if (chem == "ORE")
		return amm;

	ll cnt = min(leftovers[chem], amm);
	amm -= cnt;
	leftovers[chem] -= cnt;

	ll m = amm / at_once[chem] + (amm % at_once[chem] != 0);

	ll sum = 0;
	for (auto it : eq[chem]) {
		sum += solve(it.first, it.second * m);
	}

	leftovers[chem] += (at_once[chem] * m) - amm;

	return sum;

}

int main() {
	while (!in.eof()) {
		int n;
		string chem;
		ll amm;
		in >> amm;
		in >> chem;
		in >> n;
		at_once[chem] = amm;

		for (int i = 0; i < n; ++i) {
			string reagent;
			ll val;
			in >> val;
			in >> reagent;
			eq[chem].push_back({ reagent,val });
		}
	}

	/*for (auto it : at_once) {
		cout << it.first << ' ' << it.second << '\n';
		for (auto iti : eq[it.first])
			cout << iti.first << ' ' << iti.second << ',';
		cout << endl;
	}*/
	cout << "Part1: " <<  solve("FUEL", 1) << endl;

	ll ore = 1000000000000;
	ll fuel = 10000000;

	ll l = 0, r = fuel;

	while (l + 1 < r) {
		leftovers.clear();
		ll mid = (l + r )/ 2;
		if (solve("FUEL", mid) <= ore) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	cout << "Part2: " << l << endl;
}