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

ll arr[maxn];

int main(){
	int n, k;
	ll sum = 0;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%lld", arr + i);
		if(arr[i] < 0){
			sum += arr[i];
			arr[i] = -arr[i];
		}
	}

	sort(arr, arr + n);
	printf("%lld\n", sum);
	k--;

	priority_queue< pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
	pq.push(mp(arr[0], 0));

	while(k--){
		printf("%lld\n", sum + pq.top().fi);
		pair<ll, int> cur = pq.top();
		pq.pop();

		if(cur.se + 1 == n)
			continue;

		pq.push(mp(cur.fi - arr[cur.se] + arr[cur.se + 1], cur.se + 1));
		pq.push(mp(cur.fi + arr[cur.se + 1], cur.se + 1));
	}
	
	return 0;
}