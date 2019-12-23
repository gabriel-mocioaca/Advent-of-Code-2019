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
typedef pair<int, int> pii;


ifstream in("input.txt");
ofstream out("out.txt");

vector<int> deck(10007);

void deal_new_stack() {
	reverse(deck.begin(), deck.end());
}

void deal_increment(int n) {
	int pos = 0;
	int cnt = 0;
	vector<int> new_deck(10007);

	while (cnt < deck.size()) {
		new_deck[pos] = deck[cnt];
		cnt++;
		pos = (pos + n) % 10007;
	}

	deck = new_deck;
}

void cut(int n) {
	if (n > 0) {
		rotate(deck.begin(), deck.begin() + n, deck.end());
	}
	else {
		rotate(deck.begin(), deck.end() + n, deck.end());
	}
}

int main() {

	for (int i = 0; i < deck.size(); ++i) {
		deck[i] = i;
	}

	
	string s;
	int n;

	while (!in.eof()) {
		in >> s;
		if (s == "deal") {
			in >> s;
			if (s == "into") {
				in >> s;
				in >> s;
				deal_new_stack();
			}
			else {
				in >> s;
				in >> n;
				deal_increment(n);
			}
		}
		else {
			if (s == "cut") {
				in >> n;
				cut(n);
			}
		}
	}
	
	for (int i = 0; i < deck.size(); ++i) {
		if (deck[i] == 2019)
			cout << i << endl;
	}
}