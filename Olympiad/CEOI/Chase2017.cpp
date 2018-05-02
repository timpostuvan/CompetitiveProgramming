#include <bits/stdc++.h>
 
using namespace std;
 
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (1LL << 55)
#define maxn 100111
#define maxv 111
 
typedef long long ll;
 
ll ans;

int n, crumbs;
ll p[maxn], gain[maxn];
vector<int> adj[maxn];

ll c[maxn][maxv];   // down - start in i
ll b[maxn][maxv];   // up - end in i
pair<ll, ll> bc[maxv][2];   // best 2 down
pair<ll, ll> bb[maxv][2];   // best 2 up

void dp(int x, int pr){
    for(int v : adj[x]){
        if(v == pr)
            continue;
        dp(v, x);
    }

    for(int i = 0; i <= crumbs; i++){
        c[x][i] = 0;
        for(int j = 0; j < 2; j++)
            bc[i][j] = mp(0, -1);
    }

    for(int v : adj[x]){
        if(pr == -1)
            break;
        if(v == pr)
            continue;

        for(int i = 0; i <= crumbs; i++){
            c[x][i] = max(c[x][i], c[v][i]);
            if(i > 0)
                c[x][i] = max(c[x][i], c[v][i - 1] + gain[x] - p[pr]);
        }
    }

    for(int v : adj[x]){
        if(v == pr)
            continue;
        for(int i = 0; i <= crumbs; i++){
            if(c[v][i] >= bc[i][0].fi){
                bc[i][1] = bc[i][0];
                bc[i][0] = mp(c[v][i], v);
            }
            else{
                if(c[v][i] > bc[i][1].fi)
                    bc[i][1] = mp(c[v][i], v);
            }       
        }
    }    

    for(int i = 0; i <= crumbs; i++){
        b[x][i] = (i == 0 ? 0 : gain[x]);
        for(int j = 0; j < 2; j++){
            bb[i][j] = mp((i == 0 ? 0LL : gain[x]), x);
        }
    }

    for(int v : adj[x]){
        if(v == pr)
            continue;

        for(int i = 0; i <= crumbs; i++){
            b[x][i] = max(b[x][i], b[v][i]);
            if(i > 0)
                b[x][i] = max(b[x][i], b[v][i - 1] + gain[x] - p[v]);
        }
    } 

    for(int v : adj[x]){
        if(v == pr)
            continue;
        for(int i = 0; i <= crumbs; i++){
            ll cur = b[v][i];
            if(i > 0)
                cur = max(cur, b[v][i - 1] + gain[x] - p[v]);
            if(cur >= bb[i][0].fi){
                bb[i][1] = bb[i][0];
                bb[i][0] = mp(cur, v);
            }
            else{
                if(cur > bb[i][1].fi)
                    bb[i][1] = mp(cur, v);
            }       
        }
    }

    for(int i = 0; i <= crumbs; i++){
        ll cur = 0;
        if(bb[i][0].se != bc[crumbs - i][0].se)
            cur = bb[i][0].fi + bc[crumbs - i][0].fi;
        else
            cur = max(bb[i][1].fi + bc[crumbs - i][0].fi, bb[i][0].fi + bc[crumbs - i][1].fi);
        ans = max(ans, cur);
    }
}


 
int main(){
    scanf("%d%d", &n, &crumbs);
    for(int i = 1; i <= n; i++)
        scanf("%lld", p + i);

    for(int i = 0; i < n - 1; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].pb(b);
        adj[b].pb(a);
        gain[a] += p[b];
        gain[b] += p[a];
    }

    dp(1, -1);
    printf("%lld\n", ans);
    return 0;
}