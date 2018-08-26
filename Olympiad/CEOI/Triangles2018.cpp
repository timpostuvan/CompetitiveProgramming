#include <bits/stdc++.h>
#include "trilib.h"

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 40111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int n;
vector<int> divide[2], hull[2];

bool is_less(int a, int b){
	return is_clockwise(1, a, b);
}

int main(){
	n = get_n();
	divide[0] = divide[1] = {2};	
	for(int i = 3; i <= n; i++)
		divide[is_clockwise(1, 2, i)].pb(i);

	for(int h = 0; h < 2; h++){
		sort(divide[h].begin(), divide[h].end(), is_less);

		for(int i : divide[h]){
			int sz = hull[h].size();
			while(sz >= 2 && !is_clockwise(hull[h][sz - 2], hull[h][sz - 1], i)){
				sz--;
				hull[h].pop_back();
			}
			hull[h].pb(i);
		}

		if(h == 1)
			reverse(hull[h].begin(), hull[h].end());

		hull[h].insert(hull[h].begin(), 1);
	}

	if(min(hull[0].size(), hull[1].size()) == 2){
		give_answer(max(hull[0].size(), hull[1].size()));
		return 0;
	}

	for(int h = 0; h < 2; h++){
		hull[0].pop_back();

		while(1){
			bool finish = 1;
			int sz = hull[0].size();
			if(sz >= 2 && !is_clockwise(hull[0][sz - 2], hull[0][sz - 1], hull[1].back())){
				hull[0].pop_back();
				finish = 0;
			}
			sz = hull[1].size();
			if(sz >= 2 && !is_clockwise(hull[0].back(), hull[1][sz - 1], hull[1][sz - 2])){
				hull[1].pop_back();
				finish = 0;
			}

			if(finish)
				break;
		}

		for(int i = 0; i < 2; i++)
			reverse(hull[i].begin(), hull[i].end());

		swap(hull[0], hull[1]);
	}

	give_answer(hull[0].size() + hull[1].size());
	return 0;
}