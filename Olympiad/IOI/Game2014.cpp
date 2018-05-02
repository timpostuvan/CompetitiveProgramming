#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include "grader.h"

using namespace std;

int comp[1555][1555];
int root[1555];
int N;

int rooting(int x){
	if(root[x] == x) return x;
	else return root[x] = rooting(root[x]);
}

void initialize(int n){
	N = n;
	for(int i = 0; i < N; i++){
		root[i] = i;
		for(int j = 0; j < N; j++) if(i != j) comp[i][j] = 1; 
	}
}

void merge(int u, int v){
	root[u] = v;
	for(int i = 0; i < N; i++){
		comp[v][i] += comp[u][i];
		comp[u][i] = 0;
	}
	for(int i = 0; i < N; i++){
		comp[i][v] += comp[i][u];
		comp[i][u] = 0;
	}
}

int hasEdge(int u, int v){
	int ru, rv;
	ru = rooting(u);
	rv = rooting(v);

	if(ru == rv) return 0;
	if(max(comp[ru][rv], comp[rv][ru]) == 1) {
		comp[ru][rv] = max(0, comp[ru][rv] - 1);
		comp[rv][ru] = max(0, comp[rv][ru] - 1);
		merge(ru, rv); 
		return 1;
	}
	else{
		comp[ru][rv] = max(0, comp[ru][rv] - 1);
		comp[rv][ru] = max(0, comp[rv][ru] - 1);
		return 0;
	}
}

/*
int main(){
	int N;
	scanf("%d", &N);
	initialize(N);
	for(int i = 0; i < N * (N - 1) / 2; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", hasEdge(a, b));
	}
	return 0;
} */