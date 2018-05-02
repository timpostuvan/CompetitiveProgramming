#include <cstdio>
#include <algorithm>
#include <vector>
#include <vector>
#include <cstring>

using namespace std;

struct trie{
	char ch;
	int let[26];
	bool end;
	bool pot;
};

trie t[500111];
int cnt, n, maks;
char str[222], naj[222];

void add(char* str, int ind, int tren){
	if(strlen(str) == ind) {t[tren].end = 1; return;}
	int c = (long long) (str[ind] - 'a');
	if(t[tren].let[c] == 0){
		t[tren].let[c] = cnt;
		t[cnt].ch = str[ind];
		cnt++;
	}
	add(str, ind + 1, t[tren].let[c]);
}



void DFS(int ind, int tren, int p){
	if(ind > maks) return;

	if(tren != 0) printf("%c\n", t[tren].ch);
	int c = (long long) (naj[ind] - 'a');
	if(t[tren].end == 1) printf("P\n");
	for(int i = 0; i < 26; i++){
		if(t[tren].let[i] != 0 && (i != c || p == 0) ){
			DFS(ind + 1, t[tren].let[i], 0);
		}
	}

	if((tren == 0 || t[tren].ch == naj[ind - 1]) && p) DFS(ind + 1, t[tren].let[c], p);
	if(p == 0) printf("-\n");
	return;
}

int main(){
	cnt = 1;
	maks = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", str);
		if(strlen(str) > maks){
			maks = strlen(str);
			for(int i = 0; i < maks; i++) naj[i] = str[i];
		}
		add(str, 0, 0);
	}
	cnt--;

	printf("%d\n", cnt * 2 - maks + n);
	DFS(0, 0, 1);
	return 0;
}