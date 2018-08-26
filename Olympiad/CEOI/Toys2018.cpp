/*
Idea:
- https://ceoi2018.pl/wp-content/uploads/2018/08/day2.pdf (Toys)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxdiv 5111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> v;
map<int, int> here;
set<int> s[maxdiv];

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i * i <= n; i++){
		if(n % i == 0){
			v.pb(i);
			if(i * i != n)
				v.pb(n / i);
		}
	}

	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++)
		here[v[i]] = i;

	s[0].insert(0);
	for(int i = 0; i < v.size() - 1; i++){
		ll cur = v[i];
		for(int x : v){
			ll nxt = cur * x;
			if(nxt == cur || !here.count(nxt))
				continue;

			int pos = here[nxt];
			for(int v : s[i])
				s[pos].insert(v + x - 1);
		}
	}

	int lst = v.size() - 1;
	printf("%d\n", (int) s[lst].size());
	for(int x : s[lst])
		printf("%d ", x);

	return 0;
}