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

bool finished = false;

class moon {
public:

	ll x, y, z;
	ll vx, vy, vz;
	moon(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->vx = 0;
		this->vy = 0;
		this->vz = 0;
	}

	void apply_gravity(vector<moon> v) {
		for (int it = 0; it < 4; ++it) {
			if (this->x < v[it].x) this->vx++;
			else if (this->x > v[it].x) this->vx--;
			if (this->y < v[it].y) this->vy++;
			else if (this->y > v[it].y) this->vy--;
			if (this->z < v[it].z) this->vz++;
			else if (this->z > v[it].z) this->vz--;
			
		}
	}

	void apply_velocity() {
		this->x += this->vx;
		this->y += this->vy;
		this->z += this->vz;
	}

	int pot_energy() {
		return abs(this->x) + abs(this->y) + abs(this->z);
	}

	int kin_energy() {
		return abs(this->vx) + abs(this->vy) + abs(this->vz);
	}

	int tot_energy() {
		return this->pot_energy() * this->kin_energy();
	}

};

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}

int main() {
	vector<moon> v;
	v.push_back(moon(-15,1,4));
	v.push_back(moon(1,-10,-8));
	v.push_back(moon(-5,4,9));
	v.push_back(moon(4,6,-2));

	vector<moon>init_state = v;

	ll x = 0;
	ll y = 0;
	ll z = 0;

	for(ll i = 1; i <= 10000000; ++i) {
		for (int it = 0; it < 4; ++it) {
			v[it].apply_gravity(v);

		}

		for (int it = 0; it < 4; ++it) {
			v[it].apply_velocity();
		}

		if (i == 1000) {
			int tot_energy = 0;

			for (auto it : v) {
				tot_energy += it.tot_energy();
			}
			cout << tot_energy << '\n';
		}

		if (!x && (v[0].x == init_state[0].x) && (v[1].x == init_state[1].x) && (v[2].x == init_state[2].x) && (v[3].x == init_state[3].x))
			x = i;
		if (!y && (v[0].y == init_state[0].y) && (v[1].y == init_state[1].y) && (v[2].y == init_state[2].y) && (v[3].y == init_state[3].y))
			y = i;
		if (!z && (v[0].z == init_state[0].z) && (v[1].z == init_state[1].z) && (v[2].z == init_state[2].z) && (v[3].z == init_state[3].z))
			z = i;

		if (x && y && z)
			break;
	}

	cout << x + 1 << ' ' << y + 1 << ' ' << z + 1<< ' ';
	cout << lcm(x + 1, lcm(y + 1, z + 1));
}