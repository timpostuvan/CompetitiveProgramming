/*
Idea:
- http://www.ceoi2016.ro/competition/tasks/ (ICC solution)
*/

#include <icc.h>
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (30013)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int id[maxn];
vector<int> comp[maxn], v[2];
int nn;

/*
bool query(int a, int b, int c[], int d[]){
	cout << "query: " <<endl;
	for(int i = 0; i < a; i++)
		cout << c[i] << " ";
	cout << endl;

	for(int i = 0; i < b; i++)
		cout << d[i] << " ";
	cout << endl;

	cout << endl;

	bool ret;
	cin >> ret;

	return ret;
}

void setRoad(int a, int b){
	cout << "setRoad " << a  << " " << b << endl << endl;
} */

bool ask(int l0, int d0, int l1, int d1){
	vector<int> a, b;
	for(int i = l0; i <= d0; i++)
		a.pb(v[0][i]);

	for(int i = l1; i <= d1; i++)
		b.pb(v[1][i]);

	return query(a.size(), b.size(), &a[0], &b[0]);
}

void merge(int a, int b){
	int posa = id[a];
	int posb = id[b];

	for(int i : comp[posb])
		comp[posa].pb(i);

	comp[posb].clear();

	nn = 0;
	for(int i = 1; i < maxn; i++){
		if(comp[i].size())
			comp[++nn] = comp[i];
	}

	for(int i = nn + 1; i < maxn; i++)
		comp[i].clear();

	for(int i = 1; i <= nn; i++){
	//	cout << i << ":  " << endl;
		for(int j : comp[i]){
			id[j] = i;
	//		cout << j << " "<< endl;
		}
	//	cout <<  endl << endl;
	} 
} 

void run(int n){
	nn = n;
	for(int i = 1; i <= n; i++){
		comp[i].pb(i);
		id[i] = i;
	}

	for(int edge_count = 0; edge_count < n - 1; edge_count++){
		for(int bit = 0; (1 << bit) <= n; bit++){
			v[0].clear();
			v[1].clear();

			for(int i = 1; i <= nn; i++){
				int pos = (i >> bit) & 1;
				for(int x : comp[i])
					v[pos].pb(x);
			}

			bool ret = ask(0, v[0].size() - 1, 0, v[1].size() - 1);
			if(ret == 1)
				break;
		}

		pii road;
		int l = 0, d = v[0].size() - 1, mid, ans = -1;
		while(l <= d){
			if(l == d){
				ans = l;
				break;
			}

			mid = (l + d) / 2;
			bool cur = ask(l, mid, 0, v[1].size() - 1);
			if(cur == 1)
				d = mid;
			else
				l = mid + 1;
		}
		road.fi = v[0][ans];

		l = 0; d = v[1].size() - 1; ans = -1;
		while(l <= d){
			if(l == d){
				ans = l;
				break;
			}

			mid = (l + d) / 2;
			bool cur = ask(0, v[0].size() - 1, l, mid);
			if(cur == 1)
				d = mid;
			else
				l = mid + 1;
		}
		road.se = v[1][ans];

		setRoad(road.fi, road.se);
		merge(road.fi, road.se);
	}
}

/*

int main(){
	int n;
	scanf("%d", &n);
	run(n);
	return 0;
}
*/