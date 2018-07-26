/*
Idea:
- https://discuss.codechef.com/questions/130200/invitation-for-ioi-training-camp-ioitc-replay-contest-1/130261
(CIRCINTE)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 501111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll l[maxn], r[maxn], pos[maxn];
int n;
ll m;

bool check(ll dist){
	pos[n - 1] = r[n - 1];
	for(int cnt = 0; cnt < 2; cnt++){
		for(int i = 0; i < n; i++){
			if(i == 0){
				ll cur = m - pos[n - 1]; 
				pos[i] = dist - cur;
			}
			else
				pos[i] = pos[i - 1] + dist;
			
			pos[i] = min(pos[i], r[i]);
			pos[i] = max(pos[i], l[i]);
		}
	}

	for(int i = 0; i < n; i++){
		ll cur;
		if(i == 0)
			cur = pos[i] + (m - pos[n - 1]);
		else
			cur = pos[i] - pos[i - 1];

		if(cur < dist)
			return 0;
	}
	return 1;
}


int main(){
	scanf("%lld%d", &m, &n);
	for(int i = 0; i < n; i++)
		scanf("%lld%lld", l + i, r + i);

	ll leva = 0, desna = m, mid, ans;
	while(leva <= desna){
		mid = (leva + desna) / 2;
		if(check(mid)){
			ans = mid;
			leva = mid + 1;
		}
		else
			desna = mid - 1;
	}

	printf("%lld\n", ans);
	return 0;
}