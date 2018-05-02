#include <bits/stdc++.h>
   
using namespace std;
   
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (1LL << 55)
#define maxn 100111
#define logn 20
 
typedef long long ll;
   
struct st{
    int v, smer, id;
};
 
int cnt;
vector<st> adj[maxn], pov[maxn];
int num[maxn], low[maxn], comp[maxn], l[maxn], pid[maxn];
bool used[maxn], tree[maxn], bridge[maxn];
int par[logn][maxn], ans[maxn];
vector<pair<int, int> > v;
pair<int, int> q[maxn];
 
void tarjan(int x, int p){
    num[x] = low[x] = ++cnt;
    for(st i : adj[x]){
        if(i.v == p)
            continue;
        if(!num[i.v]){
            tarjan(i.v, x);
            if(num[x] < low[i.v])
                bridge[i.id] = 1;
            low[x] = min(low[x], low[i.v]);
        }
        else
            low[x] = min(low[x], num[i.v]);
    }
}
 
void color(int x, int p){
    used[x] = 1;
    for(st i : adj[x]){
        if(i.v == p || used[i.v] || bridge[i.id])
            continue;
        comp[i.v] = comp[x];
        color(i.v, x);
    }
}
 
 
void DFS(int x, int p){
    tree[x] = 1;
    par[0][x] = p;
    for(int j = 0; j < pov[x].size(); j++){
        st i = pov[x][j];
        if(i.v == p){
            pid[x] = j;
            continue;
        }
        l[i.v] = l[x] + 1;
        DFS(i.v, x);
    }
}
 
int LCA(int a, int b){
    if(l[a] < l[b])
        swap(a, b);
    int raz = l[a] - l[b];
    for(int i = logn - 1; i >= 0; i--){
        if(raz & (1 << i))
            a = par[i][a];
    }
    if(a == b)
        return a;
 
    for(int i = logn - 1; i >= 0; i--){
        if(par[i][a] != par[i][b]){
            a = par[i][a];
            b = par[i][b];
        }
    }
    return par[0][a];
}
 
void go(int a, int b, int opt){
    while(a != b && !tree[a]){
        tree[a] = 1;
        st c = pov[a][pid[a]];
        if(opt == 0)
            ans[c.id] = 1 - c.smer;
        if(opt == 1)
            ans[c.id] = c.smer;
        a = c.v;
    }
}
 
int main(){
    for(int i = 0; i < maxn; i++)
        ans[i] = 2;
 
    int n, m, p;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        st c = {b, 0, i};
        adj[a].pb(c);
        c = {a, 1, i};
        adj[b].pb(c);
    }
 
    for(int i = 1; i <= n; i++){
        if(!num[i])
            tarjan(i, 0);
    }
 
    cnt = 0;
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            comp[i] = ++cnt;
            color(i, 0);
        }
    }
 
    for(int i = 1; i <= n; i++){
        for(st j : adj[i]){
            int a = comp[i];
            int b = comp[j.v];
            if(a != b)
                pov[a].pb({b, j.smer, j.id});
        }
    }
 
    for(int i = 1; i <= n; i++){
        if(!tree[i]){
            l[i] = 1;
            DFS(i, 0);
        }
    }
 
    for(int i = 1; i < logn; i++){
        for(int j = 1; j <= n; j++)
            par[i][j] = par[i - 1][par[i - 1][j]];
    }
 
    scanf("%d", &p);
    for(int i = 0; i < p; i++){
        scanf("%d%d", &q[i].fi, &q[i].se);
        q[i].fi = comp[q[i].fi];
        q[i].se = comp[q[i].se];
        if(q[i].fi == q[i].se)
            continue;
        v.pb(mp(l[LCA(q[i].fi, q[i].se)], i));
    }
 
    memset(tree, 0, sizeof(tree));
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        int a = q[v[i].se].fi;
        int b = q[v[i].se].se;
        int lca = LCA(a, b);
 
        go(a, lca, 0);
        go(b, lca, 1);
    }
 
    for(int i = 0; i < m; i++){
        if(ans[i] == 0)
            printf("L");
        if(ans[i] == 1)
            printf("R");
        if(ans[i] == 2)
            printf("B");
    }
    printf("\n");
    return 0;
}