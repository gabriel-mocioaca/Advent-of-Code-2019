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

struct point{
    int x;
    int y;
    int cnt;
      bool operator<(const point& rhs) const
    {
        return x < rhs.x || (!(rhs.x < x) && y < rhs.y);
    }
    bool operator==(const point& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

int main() {
	int n;
    int mid = 0;
	set<point> vis;

	int i = mid, j = mid;
	in >> n;
	char x;
	int len;
	int cnt = 0;
	for (int it = 0; it < n; ++it) {
		in >> x;
		in >> len;
		cout << i << ' ' << j << '\n';
		if (x == 'U') {
			while (len--) {
                cnt++;
				vis.insert({--i, j, cnt});
			}
		}
		if (x == 'D') {
			while (len--) {
                cnt++;
				vis.insert({++i, j, cnt});
			}
		}
		if (x == 'L') {
			while (len--) {
                cnt++;
				vis.insert({i, --j, cnt});
			}
		}
		if (x == 'R') {
			while (len--) {
                cnt++;
				vis.insert({i, ++j, cnt});;
			}
		}
	}

	int min_dist = INT_MAX;
	in >> n;
	i = mid, j = mid;
	cnt = 0;
	for (int it = 0; it < n; ++it) {
		in >> x;
		in >> len;
		cout << i << ' ' << j << ' ' << min_dist << '\n';
		if (x == 'U') {
			while (len--) {
                cnt++;
                auto h = vis.find({--i, j, cnt});
				if (h != vis.end())
					min_dist = min(min_dist, cnt + (*h).cnt);
			}
		}
		if (x == 'D') {
			while (len--) {
                cnt++;
                auto h = vis.find({++i, j, cnt});
				if (h != vis.end())
					min_dist = min(min_dist, cnt + (*h).cnt);
			}
		}
		if (x == 'L') {
			while (len--) {
                cnt++;
                auto h = vis.find({i, --j, cnt});
				if (h!= vis.end())
					min_dist = min(min_dist, cnt + (*h).cnt);
			}
		}
		if (x == 'R') {
			while (len--) {
                cnt++;
                auto h = vis.find({i, ++j, cnt});
				if (h!= vis.end())
					min_dist = min(min_dist, cnt + (*h).cnt);
			}
		}
	}

	cout << min_dist;
	return  0;
}
