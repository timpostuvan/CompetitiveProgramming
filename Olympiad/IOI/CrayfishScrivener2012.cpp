#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;

struct trie{
	int l;
	char ch;
	int let[27];
	int par[21];
	trie(){
		l = -1;
		memset(let, 0, sizeof(let));
		memset(par, 0, sizeof(par));
	}
};

int cnt, query, cur;
trie t[maxn];
int pt[maxn];

void Init(){

}

void TypeLetter(char c){
	t[cur].let[c - 'a'] = ++cnt;
	t[cnt].ch = c;
	t[cnt].par[0] = cur;
	t[cnt].l = t[cur].l + 1;
	for(int i = 1; i < 19; i++)
		t[cnt].par[i] = t[t[cnt].par[i - 1]].par[i - 1]; 
	pt[query++] = cnt;
	cur = cnt;
}

void UndoCommands(int u){
	cur = pt[query - u - 1];
	pt[query++] = cur;
}

char GetLetter(int u){
	int here = t[cur].l;
	int left = here - u;
	int tren = cur;
	for(int i = 20; i >= 0; i--){
		if((1LL << i) & left){
			tren = t[tren].par[i];
		}
	}
	return t[tren].ch;
}

/*

int main(){
	int n;
	cin >> n;
	while(n--){
		char t;
		int k;
		char c;
		cin >> t;
		if(t == 'T'){
			cin >> c;
			TypeLetter(c);
		}

		if(t == 'P'){
			cin >> k;
			cout << GetLetter(k) << endl;
		}
		
		if(t == 'U'){
			cin >> k;
			UndoCommands(k);
		}
	}
	return 0;
} */