#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 4111
#define base 11

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

char str[maxn][maxn];
int arr[maxn][maxn];
ll pw[maxn], hash_val[maxn][4];

int get_val(char ch){
    if(ch == 'A')
        return 0;

    if(ch == 'C')
        return 1;

    if(ch == 'T')
        return 2;

    if(ch == 'G')
        return 3;
}

void preprocess(){
    pw[0] = 1;
    for(int i = 1; i < maxn; i++)
        pw[i] = pw[i - 1] * base % MOD;
}

int main(){
    preprocess();

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < n; i++){
        scanf("%s", str[i]);
        for(int j = 0; j < m; j++){
            arr[i][j] = get_val(str[i][j]);
            hash_val[j][arr[i][j]] = (hash_val[j][arr[i][j]] + pw[i]) % MOD; 
        }
    }

    int ans = -1;
    for(int i = 0; i < n; i++){

        ll all = 0;
        for(int j = 0; j < n; j++){
            if(i == j)
                continue;

            all = (all + pw[j] * k) % MOD;
        }

        ll cur = 0;
        for(int j = 0; j < m; j++){
            for(int ch = 0; ch < 4; ch++){
                if(ch == arr[i][j])
                    continue;

                cur = (cur + hash_val[j][ch]) % MOD;
            }
        }
        
        if(cur == all){
            ans = i + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}