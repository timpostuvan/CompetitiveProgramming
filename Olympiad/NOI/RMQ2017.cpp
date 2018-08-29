#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

multiset<int> add[maxn], rem[maxn], pos;
vector<pii> change;
vector<int> v;

pii range[maxn];
int arr[maxn];
bool used[maxn], ok;


pii intersect(pii a, pii b){
	return mp(max(a.fi, b.fi), min(a.se, b.se));
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);

	for(int i = 0; i < n; i++)
		range[i] = mp(1, n);

	for(int i = 0; i < q; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a++; b++;

		range[c] = intersect(range[c], mp(a, b));
		add[a].insert(c);
		rem[b + 1].insert(c);
	}

	for(int i = 1; i <= n; i++){
		if(add[i - 1].size() > add[i].size())
			swap(add[i - 1], add[i]);

		for(int x : add[i - 1])
			add[i].insert(x);
		
		for(int x : rem[i])
			add[i].erase(add[i].find(x));

		if(add[i].size())
			arr[i] = *(--add[i].end());
		else
			arr[i] = -1;
	}

	for(int i = 1; i <= n; i++){
		if(arr[i] == -1){
			change.pb(mp(arr[i], i));
			continue;
		}

		int x = arr[i];
		if(!used[x] && range[x].fi <= i && i <= range[x].se)
			used[x] = 1;
		else
			change.pb(mp(arr[i], i));
	}

	for(int i = 0; i < n; i++){
		if(!used[i])
			v.pb(i);
	}

	sort(v.begin(), v.end());	
	sort(change.begin(), change.end());

	ok = 1;
	int ind = 0;
	for(int i = 0; i < v.size(); i++){
		int val = v[i];
		while(ind < change.size() && change[ind].fi <= val){
			pos.insert(change[ind].se);
			ind++;
		}

		auto it = pos.lower_bound(range[val].fi);
		if(it != pos.end() && *it <= range[val].se){
			arr[*it] = val;
			pos.erase(it);
		}
		else{
			ok = 0;
			break;
		}
	}

	if(!ok)
		memset(arr, -1, sizeof(arr));

	for(int i = 1; i <= n; i++)
		printf("%d ", arr[i]);

	return 0;
}