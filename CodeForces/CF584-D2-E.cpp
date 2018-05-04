/*
Idea:
- we know ending position for every element so upper bound cost is abs(end position(i) - start position(j)) for all elements
- but we don't damage the optimal answer (we improve it) if we always check whether some element at position k (i <= k and k <= j) needs to be transported to the right
- this logic is correct because abs(i - j) = abs(i - k) + abs(j - k) when (i <= k && k <= j)
- when we did this move we reduced time by at least one so this move is better than just swapping positions i and j (element k is closer to his ending position)
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2011

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<pii> ans;
int a[maxn], b[maxn], cur_pos[maxn], wanted_pos[maxn];

int main(){
	int n, min_ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
		cur_pos[a[i]] = i;
	}

	for(int i = 0; i < n; i++){
		scanf("%d", b + i);
		wanted_pos[b[i]] = i;
	}

	for(int i = 0; i < n; i++){
		int x = b[i];
		if(cur_pos[x] == i)
			continue;

		for(int j = cur_pos[x]; j >= i; j--){
			int y = a[j];
			int final = wanted_pos[y];

			if(y == x)
				continue;

			if(cur_pos[x] >= cur_pos[y] && cur_pos[x] <= final){
				ans.pb(mp(cur_pos[x], j));
				swap(a[j], a[cur_pos[x]]);
				min_ans += abs(cur_pos[x] - cur_pos[y]);
				cur_pos[y] = cur_pos[x];
				cur_pos[x] = j;
			}
		}
	}

	printf("%d\n%d\n", min_ans, (int) ans.size());
	for(pii i : ans)
		printf("%d %d\n", i.fi + 1, i.se + 1);

	return 0;
}  