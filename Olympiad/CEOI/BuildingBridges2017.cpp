#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct line{
	int type;
	double x;
	ll k, n;
};

bool operator< (line a, line b){
	if(a.type + b.type > 0)	//	to answer query (we need to find line with value x)
		return a.x < b.x;

	return a.k > b.k;		// 	to maintain envelope (we need lines sorted according to slope - k)
}

ll sqr(ll x){
	return x * x;
}

set<line> env;
typedef set<line>::iterator sit;

bool hasPrev(sit it){
	return it != env.begin();
}

bool hasNext(sit it){
	return (it != env.end() && next(it) != env.end());
}

double intersect(sit a, sit b){
	return (double) (b -> n - a -> n) / (a -> k - b -> k);
}

void calcX(sit a){
	if(hasPrev(a)){
		line l = *a;
		l.x = intersect(prev(a), a);
		env.insert(env.erase(a), l);
	}
}

bool irrelevant(sit a){
	if(hasNext(a) && next(a) -> n <= a -> n)	// next(a) has smaller k and smaller n -> it is better than a
		return 1;

	return hasPrev(a) && hasNext(a) && intersect(prev(a), next(a)) <= intersect(prev(a), a);
}

void add(ll k, ll n){

	// handle collinear lines
	sit it = env.lower_bound({0, 0, k, n});
	if(it != env.end() && it -> k == k){
		if(it -> n <= n)
			return;
		else
			env.erase(it);
	}


	// erase irrelevant lines
	it = env.insert({0, 0, k, n}).fi;
	if(irrelevant(it)){
		env.erase(it);
		return;
	}

	while(hasPrev(it) && irrelevant(prev(it)))
		env.erase(prev(it));

	while(hasNext(it) && irrelevant(next(it)))
		env.erase(next(it));

	// recalc left intersection points
	if(hasNext(it))
		calcX(next(it));

	calcX(it);
}

ll query(ll x){
	sit it = env.upper_bound((line) {1, double (x), 0, 0});
	it--;
	return it -> k * x + it -> n;
}

ll h[maxn], w[maxn];
ll dp[maxn];

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", h + i);

	ll sum = 0;
	for(int i = 1; i <= n; i++){
		scanf("%lld", w + i);
		sum += w[i];
	}

	dp[1] = -w[1];
	for(int i = 2; i <= n; i++){
		add(-2 * h[i - 1], dp[i - 1] + sqr(h[i - 1]));
		ll opt = query(h[i]);
		dp[i] = sqr(h[i]) + opt - w[i];
	}

	printf("%lld\n", sum + dp[n]); 
	return 0;
}