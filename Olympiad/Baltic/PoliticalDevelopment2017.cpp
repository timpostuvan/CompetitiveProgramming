#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 50111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

set<pii> s;
set<int> adj[maxn];

int ans = 0;

void check(int x){
    vector<int> cur;
    cur.pb(x);
    for(int a : adj[x])
        cur.pb(a);

    int num = cur.size();
    for(int bitmask = 0; bitmask < (1 << num); bitmask++){
        bool ok = 1;
        for(int i = 0; i < num && ok; i++){
            if(bitmask & (1 << i)){
                for(int j = 0; j < num && ok; j++){
                	if(i == j)
                		continue;

                    if(bitmask & (1 << j)){
                        if(adj[cur[i]].find(cur[j]) != adj[cur[i]].end())
                            continue;
                        else
                            ok = 0;
                    }
                }
            }
        }
        if(ok)
            ans = max(ans, __builtin_popcount(bitmask));
    }
}


int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++){
        int d;
        scanf("%d", &d);
        while(d--){
            int a;
            scanf("%d", &a);
            adj[i].insert(a);
        }
        s.insert(mp(adj[i].size(), i));
    }

    while(s.size()){
        int x = s.begin() -> se;
        s.erase(s.begin());

        check(x);
        for(int v : adj[x]){
            if(v == x)
                continue;
            if(adj[v].find(x) != adj[v].end()){            
        	    s.erase(mp(adj[v].size(), v));
    	        adj[v].erase(x);
            	s.insert(mp(adj[v].size(), v));
        	}
        }
    }
    printf("%d\n", ans);    
    return 0;
}