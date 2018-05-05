/*
Idea:
- binary search for number of days (if we can do it in n days, we can do it in n + 1 days as well)
- if there are more students that can solve some task we always choose the one with lowest cost
- when we choose a student we give him as many tasks as possible (bounded by number of days)
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll n, m, s;
vector<vector<ll> > student, task;
ll b[maxn], c[maxn], ans[maxn];

bool check(ll mid){
	ll cur = s;
	priority_queue<pair<ll, ll> > pq;
	ll pos = 0;

	for(ll i = 0; i < m; i++){
		while(pos < n && student[pos][0] >= task[i][0]){
			pq.push(mp(-student[pos][1], student[pos][2]));
			pos++;
		}

		if(pq.empty())
			return 0;

		ll x = pq.top().se;
		ll val = -pq.top().fi;
		pq.pop();

		ll last = min(m, i + mid);

		for(ll j = i; j < last; j++){
			ll ind = task[j][1];
			ans[ind] = x;
		}

		cur -= val;
		i = last - 1;
	}

	if(cur >= 0)
		return 1;

	return 0;
}

int main(){
	scanf("%lld%lld%lld", &n, &m, &s);
	for(ll i = 0; i < m; i++){
		ll a;
		scanf("%lld", &a);
		task.pb({a, i});
	}

	for(ll i = 0; i < n; i++)
		scanf("%lld", b + i);

	for(ll i = 0; i < n; i++){
		scanf("%lld", c + i);
		student.pb({b[i], c[i], i});
	}

	sort(task.begin(), task.end());
	sort(student.begin(), student.end());

	reverse(task.begin(), task.end());
	reverse(student.begin(), student.end());

	if(task[0][0] > student[0][0] || !check(INF)){
		printf("NO\n");
		return 0;
	}
	
	ll l = 1, d = INF, mid, best = -1;
	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			best = mid;
			d = mid - 1;
		}
		else
			l = mid + 1;
	}

	check(best);

	printf("YES\n");
	for(ll i = 0; i < m; i++)
		printf("%lld ", ans[i] + 1);

	return 0;
}  