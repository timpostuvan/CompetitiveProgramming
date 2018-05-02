#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 811

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

char c[maxn];
ll arr[maxn][maxn];
ll val[maxn][maxn];
ll down[maxn][maxn], up[maxn][maxn];
ll n, m;

struct state{
	ll h, l, d;
};

ll AddTotal(ll x){
	ll ret = 0;
	ll sum = 0;
	stack<state> st;
	for(ll i = 0; i < m; i++){
		state cur = {down[x][i], i, i};
		while(!st.empty() && cur.h <= st.top().h){
			sum -= (st.top().d - st.top().l + 1) * st.top().h;
			cur.l = st.top().l;
			st.pop();
		}
		sum += (cur.d - cur.l + 1) * cur.h;
		st.push(cur);
		ret += sum;
	}
	return ret;
}

void add(ll i, ll x, ll y, ll cur){
	val[i][x] += cur;
	val[i][y + 1] -= cur;
}

ll BestCell(){
	ll best = 0;
	for(ll i = 0; i < n; i++){
		for(ll j = 0; j < m; j++){
			ll u = up[i][j], d = down[i][j];
			add(i, j, j, u * d);
			for(ll k = j + 1; k < m && u > 0 && d > 0; k++){
				u = min(u, up[i][k]);
				d = min(d, down[i][k]);
				add(i, j, k, u * d);
			}
		}

		for(ll j = 1; j < m; j++){
			val[i][j] += val[i][j - 1];
			best = max(best, val[i][j]);
		}
	}
	return best;
}

int main(){
	ll total = 0;
	ll best = 0;
	scanf("%lld%lld", &n, &m);
	for(ll i = 0; i < n; i++){
		scanf("%s", c);
		for(ll j = 0; j < m; j++)
			arr[i][j] = c[j] - '0';
	}

	for(ll i = 0; i < m; i++){
		up[0][i] = arr[0][i];
		down[n - 1][i] = arr[n - 1][i];
	}

	for(ll i = 1; i < n; i++){
		for(ll j = 0; j < m; j++){
			if(arr[i][j] == 1)
				up[i][j] = up[i - 1][j] + arr[i][j];

			if(arr[i][j] == 0)
				up[i][j] = 0;
		}
	}


	for(ll i = n - 2; i >= 0; i--){
		for(ll j = 0; j < m; j++){
			if(arr[i][j] == 1)
				down[i][j] = down[i + 1][j] + arr[i][j];

			if(arr[i][j] == 0)
				down[i][j] = 0;
		}
	}

	for(ll i = 0; i < n; i++)
		total += AddTotal(i);


	best = BestCell();
	printf("%lld\n", total - best);
	return 0;
}