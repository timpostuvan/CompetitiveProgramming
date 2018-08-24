/*
Idea:
- http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2018/2018-open-xylophone-sol-en.pdf
*/

#include "xylophone.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (int) (2 * 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 5111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int ret[maxn];
bool used[maxn];

void solve(int N){
	int l = 2, d = N, max_ind = -1;
	while(l <= d){
		int mid = (l + d) / 2;
		int val = query(1, mid);
		if(val == N - 1){
			max_ind = mid;
			d = mid - 1;
		}
		else
			l = mid + 1; 
	}

	ret[max_ind] = N;
	used[N] = 1;

	if(max_ind + 1 <= N){
		int cur = query(max_ind, max_ind + 1);
		ret[max_ind + 1] = N - cur;
		used[N - cur] = 1;
	}

	if(max_ind - 1 >= 1){
		int cur = query(max_ind - 1, max_ind);
		ret[max_ind - 1] = N - cur;
		used[N - cur] = 1;
	}

	for(int i = max_ind + 2; i <= N; i++){
		int diff = query(i - 1, i);
		int opt1 = ret[i - 1] + diff;
		int opt2 = ret[i - 1] - diff;

		if(opt1 < 1 || opt1 > N || used[opt1]){
			ret[i] = opt2;
			used[ret[i]] = 1;
			continue;
		}

		if(opt2 < 1 || opt2 > N || used[opt2]){
			ret[i] = opt1;
			used[ret[i]] = 1;
			continue;
		}

		int updown = query(i - 2, i);
		if(max(ret[i - 2], max(ret[i - 1], opt1)) - min(ret[i - 2], min(ret[i - 1], opt1)) == updown){
			ret[i] = opt1;
		}
		else
			ret[i] = opt2;

		used[ret[i]] = 1;
	}

	for(int i = max_ind - 2; i >= 1; i--){
		int diff = query(i, i + 1);
		int opt1 = ret[i + 1] + diff;
		int opt2 = ret[i + 1] - diff;

		if(opt1 < 1 || opt1 > N || used[opt1]){
			ret[i] = opt2;
			used[ret[i]] = 1;
			continue;
		}

		if(opt2 < 1 || opt2 > N || used[opt2]){
			ret[i] = opt1;
			used[ret[i]] = 1;
			continue;
		}

		int updown = query(i, i + 2);
		if(max(ret[i + 2], max(ret[i + 1], opt1)) - min(ret[i + 2], min(ret[i + 1], opt1)) == updown){
			ret[i] = opt1;
		}
		else
			ret[i] = opt2;

		used[ret[i]] = 1;
	}

	for(int i = 1; i <= N; i++){
		answer(i, ret[i]);
	}
}