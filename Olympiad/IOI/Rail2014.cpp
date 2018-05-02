#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 5111

typedef long long ll;
typedef long double ld;

int n;
int dist0[maxn], distmin[maxn];
bool onleft[maxn];

vector<pair<int, int> > v;
vector<pair<int, int> > tmp;

void make(int location[], int stype[], int type, int pos){ 		//type: 1-onleft, 2-onright
	tmp.clear();
	for(auto i : v){
		if(tmp.empty()){
			stype[i.se] = type;
			if(type == 1)
				location[i.se] = location[pos] - i.fi;

			if(type == 2)
				location[i.se] = location[pos] + i.fi;
			tmp.pb(i);
			continue;
		}

		bool found = 0;
		int longdist = getDistance(i.se, tmp.back().se);
		for(auto j : tmp){
			int p;
			if(type == 1)
				p = longdist - abs(location[tmp.back().se] - location[j.se]);

			if(type == 2)
				p = longdist - abs(location[tmp.back().se] - location[j.se]);

			if(j.fi + p == i.fi){
				stype[i.se] = 3 - type;
				if(stype[i.se] == 1)
					location[i.se] = location[j.se] - p;

				if(stype[i.se] == 2)
					location[i.se] = location[j.se] + p;

				found = 1;
				break;
			}
		}

		if(!found){
			stype[i.se] = type;
			if(type == 1)
				location[i.se] = location[pos] - i.fi;

			if(type == 2)
				location[i.se] = location[pos] + i.fi;
			tmp.pb(i);
		}
	}
}

void findLocation(int N, int first, int location[], int stype[]){
	n = N;
	location[0] = first;
	stype[0] = 1;
	int pos = -1, mini = 1e9;
	for(int i = 1; i < n; i++){
		dist0[i] = getDistance(0, i);
		if(dist0[i] < mini){
			mini = dist0[i];
			pos = i;
		}
	}

	location[pos] = first + mini;
	stype[pos] = 2;

	for(int i = 1; i < n; i++){
		if(i == pos)
			continue;
		distmin[i] = getDistance(i, pos);
		if(dist0[i] == distmin[i] + dist0[pos])
			onleft[i] = 1;
	}

	for(int i = 1; i < n; i++){
		if(onleft[i])
			v.pb(mp(distmin[i], i));
	}

	sort(v.begin(), v.end());
	make(location, stype, 1, pos);
	v.clear();
	for(int i = 1; i < n; i++){
		if(i != pos && !onleft[i])
			v.pb(mp(dist0[i] - dist0[pos], i));
	}
	sort(v.begin(), v.end());
	make(location, stype, 2, pos);
	v.clear();
}