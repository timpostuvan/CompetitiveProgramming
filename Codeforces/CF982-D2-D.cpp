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

vector<pii> v;
multiset<int> sz;
set<pii> s;
int d[maxn];

int main(){
	int n, ans_num = 0, ans_k = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", d + i);
		v.pb(mp(d[i], i));
	}

	sort(v.begin(), v.end());
	for(int i = 0; i < n; i++){
		int pos = v[i].se;
		pii cur = mp(pos, pos);
		
		if(s.size()){
			auto it = s.lower_bound(mp(pos, pos));
			if(it != s.begin()){
				it--;
				if(it -> se + 1 == pos){
					int cur_sz = it -> se - it -> fi + 1;
					sz.erase(sz.find(cur_sz));
					cur.fi = it -> fi;
					s.erase(it);
				}
			}

			it = s.upper_bound(mp(pos, pos));
			if(it != s.end()){
				if(pos + 1 == it -> fi){
					int cur_sz = it -> se - it -> fi + 1;
					sz.erase(sz.find(cur_sz));
					cur.se = it -> se;
					s.erase(it);
				}
			}
		}

		s.insert(cur);
		sz.insert(cur.se - cur.fi + 1);

		if(*sz.begin() == *(--sz.end()) && sz.size() > ans_num){
			ans_num = sz.size();
			ans_k = v[i].fi + 1;			
		}
	}

	printf("%d\n", ans_k);
	return 0;
}