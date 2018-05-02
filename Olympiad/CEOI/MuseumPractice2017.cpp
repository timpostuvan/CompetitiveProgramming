#include <bits/stdc++.h>
  
using namespace std;
  
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (1LL << 55)
#define maxn 10011
 
typedef long long ll;
  
vector<pair<int, int> > adj[maxn];
int f[maxn][maxn];  // he finishes here (2 * path - longest path)
int g[maxn][maxn];  // he goes back to x (2 * path)
int sz[maxn]; 

void DFS(int x, int p){
    sz[x] = 1;
    for(auto v : adj[x]){
        if(v.fi == p)
            continue;
        DFS(v.fi, x);
        sz[x] += sz[v.fi];        
    }
      
    for(int i = 2; i <= sz[x]; i++)
        f[x][i] = g[x][i] = 1e9;
      
    sz[x] = 1;
    for(auto v : adj[x]){
        if(v.fi == p)
            continue;
        for(int i = sz[x]; i >= 0; i--){
            for(int j = sz[v.fi]; j >= 0; j--){
                f[x][i + j] = min(f[x][i + j], f[x][i] + g[v.fi][j] + 2 * v.se);
                f[x][i + j] = min(f[x][i + j], g[x][i] + f[v.fi][j] + v.se);
                g[x][i + j] = min(g[x][i + j], g[x][i] + g[v.fi][j] + 2 * v.se);
            }
        }        
        sz[x] += sz[v.fi];
    }
}
  
int main(){
    int n, k, x;
    scanf("%d%d%d", &n, &k, &x);
    for(int i = 0; i < n - 1; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].pb(mp(b, c));
        adj[b].pb(mp(a, c));        
    }
      
    DFS(x, -1);
    printf("%d\n", f[x][k]);    
    return 0;
}