#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e18)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct node{
	node *lft, *rgt;
	ll sum, val, lazy;
	int cnt;

	node(){
		lft = rgt = NULL;
		cnt = sum = lazy = 0;
		val = INF;
	}
};

ll n, m, one_cnt;
node* root;

void push(node* x){
	if(x -> lft){
		x -> lft -> val += x -> lazy;
		x -> lft -> lazy += x -> lazy;
	}

	if(x -> rgt){
		x -> rgt -> val += x -> lazy;
		x -> rgt -> lazy += x -> lazy;
	}

	x -> lazy = 0;
}

void add(node* x, ll l, ll d, ll pos, ll vred, ll sums){
	x -> cnt++;
	x -> sum += vred;

	if(l == d && l == pos){
		x -> val = sums + 1 - vred;
		return;
	}

	push(x);

	ll mid = (l + d) / 2;

	if(pos <= mid){
		if(!x -> lft)
			x -> lft = new node();

		if(x -> rgt){
			x -> rgt -> val += vred;
			x -> rgt -> lazy += vred;
		}
		add(x -> lft, l, mid, vred, pos, sums);
	}
	else{
		if(!x -> rgt)
			x -> rgt = new node();

		if(x -> lft)
			sums += x -> lft -> sum;

		add(x -> rgt, mid + 1, d, vred, pos, sums);
	}

	x -> val = INF;
	if(x -> lft)
		x -> val = min(x -> val, x -> lft -> val);
	if(x -> rgt)
		x -> val = min(x -> val, x -> rgt -> val);
}

void del(node* x, ll l, ll d, ll pos, ll vred, ll sums){
	x -> cnt--;
	x -> sum -= vred;

	if(l == d && l == pos){
		if(x -> cnt == 0)
			x -> val = INF;

		return;
	}

	push(x);

	ll mid = (l + d) / 2;

	if(pos <= mid){
		if(x -> rgt){
			x -> rgt -> val -= vred;
			x -> rgt -> lazy -= vred;
		}
		del(x -> lft, l, mid, vred, pos, sums);
	}
	else{
		if(x -> lft)
			sums += x -> lft -> sum;

		del(x -> rgt, mid + 1, d, vred, pos, sums);
	}

	x -> val = INF;
	if(x -> lft)
		x -> val = min(x -> val, x -> lft -> val);
	if(x -> rgt)
		x -> val = min(x -> val, x -> rgt -> val);
}

void check(){
	push(root);

	int ret = 0;
	if(root -> cnt == 0)
		ret = 1;

	if(root -> val >= 0 && one_cnt > 0)
		ret = 1;

	printf("%d\n", ret);
}

vector<ll> v;

int main(){
	root = new node();

	scanf("%lld%lld", &n, &m);
	for(int i = 0; i < n; i++){
		ll x;
		scanf("%lld", &x);
		if(x == 1)
			one_cnt++;

		add(root, 1, m, x, x, 0);
	}

	check();
	
	int q;
	scanf("%d", &q);
	while(q--){
		int t, k;
		scanf("%d%d", &t, &k);
		v.clear();

		while(k--){
			ll x;
			scanf("%lld", &x);
			v.pb(x);
		}

		if(t == 1){
			for(ll x : v){
				if(x == 1)
					one_cnt++;

				add(root, 1, m, x, x, 0);
			}
		}

		if(t == -1){
			for(ll x : v){
				if(x == 1)
					one_cnt--;

				del(root, 1, m, x, x, 0);
			}
		}

		check();
	}

	return 0;
}