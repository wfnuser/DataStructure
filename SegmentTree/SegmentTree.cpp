/************************
author: wfnuser date www.element14.site
title: A segment tree 
For DS
************************/

#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

const int MAXNUM = 1000;
const int INFINITE = INT_MAX;

struct Node {
	int val;
} segTree[MAXNUM];

void build (int root, int arr[], int start, int end) 
{
	if (start == end) {
		segTree[root].val = arr[start];
	} else {
		int mid = (start + end) / 2;
		build (root*2+1, arr, start, mid);
		build(root*2+2, arr, mid+1, end);
		segTree[root] = min(segTree[root*2+1].val, segTree[root*2+2].val);
	}
		
}

// qstart is query start
// start is current start
int query (int root, int start, int end, int qstart, int qend)
{
	if (start > qend || end < qstart) {
		return INFINITE;
	}
	if (start >= qstart && end <= qend) {
		return segTree[root].val;
	}

	int mid = (start + end) / 2;
	
	return min (query(root*2+1, start, mid, qstart, qend), query(root*2+2, mid+1, end, qstart, qend));
}

int main()
{
	
}

