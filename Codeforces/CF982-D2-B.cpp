#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

set<pii> s[2];
char t[2 * maxn];
int ans[2 * maxn], w[2 * maxn];

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", w + i);
		s[0].insert(mp(w[i], i));
	}

	scanf("%s", t);

	for(int i = 0; i < 2 * n; i++){
		if(t[i] == '0'){
			ans[i] = s[0].begin() -> se;
			s[1].insert(*s[0].begin());
			s[0].erase(s[0].begin());
		}

		if(t[i] == '1'){
			ans[i] = (--s[1].end()) -> se;
			s[1].erase(--s[1].end());
		}
	}

	for(int i = 0; i < 2 * n; i++)
		printf("%d ", ans[i]);
	
	return 0;
}