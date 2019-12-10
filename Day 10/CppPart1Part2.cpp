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

int xm, ym;

int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

bool is_in_bounds(int x, int y) {
	return x >= 0 && x < xm && y >= 0 && y < ym;
}

int check(vector<string> ss, int sx, int sy) {
	set<pair<int, int>> visited;
	int cnt = 0;
	queue<pair<int, int>> q;

	visited.insert({ sx,sy });

	for (int k = 0; k < 4; k++) {
		if (is_in_bounds(sx + dx[k], sy + dy[k]) && visited.find({ sx + dx[k], sy + dy[k] }) == visited.end()) {
			visited.insert({ sx + dx[k], sy + dy[k] });
			q.push({ sx + dx[k], sy + dy[k] });
		}
	}

	while (!q.empty()) {
		int x, y;
		x = q.front().first;
		y = q.front().second;

		q.pop();

		if (ss[x][y] == '#') {
			cnt++;
			int px = x - sx, py = y - sy;
			int g = gcd(abs(px), abs(py));
			px /= g;
			py /= g;
			int cx = x + px, cy = y + py;
			while (is_in_bounds(cx, cy)) {
				ss[cx][cy] = '.';
				
				cx += px;
				cy += py;
				
			}
		}
		for (int k = 0; k < 4; k++) {
			if (is_in_bounds(x + dx[k], y + dy[k]) && visited.find({ x + dx[k], y + dy[k] }) == visited.end()) {
				visited.insert({ x + dx[k], y + dy[k] });
				q.push({ x + dx[k], y + dy[k] });
			}
		}
	}
	return cnt;
}

struct asteroid {
	float ang;
	float dist;
	int x;
	int y;
};

float angle(pair<int, int> p1, pair<int, int> p2)
{
	return (float)atan2(p1.first - p2.first, p1.second - p2.second);
}

float distance(pair<int, int> p1, pair<int, int> p2) {
	return (float)sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}




void destroy(vector<string> ss, int x, int y) {
	list<asteroid> left_asteroids;
	list<asteroid> right_asteroids;
	list<asteroid> all;

	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ss[i].size(); ++j) {
			if (ss[i][j] == '#') {
				if (angle({ x,y }, { j,i }) <= 0) {
					right_asteroids.push_back({ angle({x,y}, {j,i}), distance({x,y}, {j,i}), j, i });
				}
				else {
					left_asteroids.push_back({ angle({x,y}, {j,i}), distance({x,y}, {j,i}), j, i });
				}
			}
		}
	}
	right_asteroids.sort([](asteroid a, asteroid b) -> bool {
		if (a.ang == b.ang)
			return a.dist < b.dist;
		else
			return fabs(a.ang) < fabs(b.ang);

	});
	left_asteroids.sort([](asteroid a, asteroid b) -> bool{
		if (a.ang == b.ang)
			return a.dist < b.dist;
		else
			return fabs(a.ang) > fabs(b.ang);
	});
	

	all.insert(all.end(), right_asteroids.begin(), right_asteroids.end());
	all.insert(all.end(), left_asteroids.begin(), left_asteroids.end());

	asteroid last = all.front();
	int  cnt = 1;
	all.pop_front();
	auto curr = all.begin();
	/*for (auto it : all) {
		cout << it.ang << ' ' << it.dist << ' ' << it.x << ' ' << it.y << '\n';
	}*/

	while(cnt < 200) {
		auto temp = curr;
		if ((*temp).ang != last.ang) {
			cnt++;
			last = *temp;
			curr = all.erase(temp);
		}
		else {
			curr++;
		}
		if (curr == all.end())
			curr = all.begin();
	}
	cout << last.x << ' ' << last.y;
}


int main() {
	string s;
	vector<string> ss;
	while (!in.eof()) {
		in >> s;
		ss.push_back(s);
	}
	
	xm = ss.size();
	ym = ss[0].size();

	/*for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ss[i].size(); ++j) {
			cout << ss[i][j];
		}
		cout << endl;
	}
	cout << endl;*/
	int m = INT_MIN;
	int xmax, ymax;
	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ss[i].size(); ++j) {
			if (ss[i][j] == '#') {
				int curr = check(ss, i, j);
				if (curr > m) {
					m = curr;
					xmax = j;
					ymax = i;
				}
			}
		}
	}
	cout << m << ' ' << xmax << ' ' << ymax << endl;

	int x = xmax;
	int y = ymax;
	destroy(ss, x, y);
}
