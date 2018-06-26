#include <stdio.h>
#include <conio.h>
#include <math.h>
#define MAX 24
#define bool _Bool
#define true 1
#define false 0

struct DataPair {
	float* dist;
	int* prev;
};

int findMin(bool* Q,int* dist,int size);
struct DataPair djikstraAlg(int** Graph, int source, int size);



int main() {
	struct DataPair p;
	int size, source, i, j, k, l;

	printf("Enter the number of nodes for the Graph: \n");
	scanf_s("%d", &size);

	int** Graph = (int **)malloc(size * sizeof(int *));
	for (k = 0; k < size; k++) {
		Graph[k] = (int *)malloc(size * sizeof(int));
	}

	printf("Enter in Edge Values for each node: \n");
	printf("(Please enter -1 if Edge does not exist)\n\n");

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("What is the weight from node %d to %d \n", i, j);
			scanf_s("%d", &Graph[i][j]);
		}
	}

	printf("Enter in source node: \n");
	scanf_s("%d", &source);

	p = djikstraAlg(Graph, source, size);

	for (i = 0; i < size; i++) {
		int d = (int)p.dist[i];
		printf("Shortest distance to node %d: %d \n", i, d);
	}

	for (j = 0; j < size; j++) {
		int pr =p.prev[j];
		printf("Previous shortest node: %d from: %d \n", pr, j);
	}

	for (l = 0; l < size; l++) {
		free(Graph[l]);
	}
	free(Graph);
	free(p.dist);
	free(p.prev);

	system("pause");
	return 0;
}

struct DataPair djikstraAlg(int** Graph, int source, int size) {
	struct DataPair p;
	bool* Q = (bool *)malloc(size * sizeof(bool));
	float* dist = (int *)malloc(size * sizeof(int));
	int* prev = (int *)malloc(size * sizeof(int));
	int i, j; 
	int setEmptyCounter = 0;
	
	//We will use -1 for undefined prev array since our nodes are assume to be positive numbers
	//Our set Q will be a hashtable which tells you if the node is still in our set
	for (i = 0; i < size; i++) {
		dist[i] = INFINITY;
		prev[i] = -1; 
		Q[i] = true;
	}
	dist[source] = 0;
	
	//Set Empty Counter will count everytime a node in Q becomes false. 
	//Thus, once our counter is the same as the size of our graph our set will be empty.
	while (setEmptyCounter < size) {
		int u = findMin(Q, dist, size);
		Q[u] = false;
		++setEmptyCounter;

		for (j = 0; j < size; j++) {
			int length = Graph[u][j];

			if (length >= 0) {
				int alt = dist[u] + length;
				if (alt < dist[j]) {
					dist[j] = (float)alt;
					prev[j] = u;
				}
			}
			
		}

	}
	p.dist = dist;
	p.prev = prev;
	

	return p;
}

int findMin(bool* Q, int* dist, int size) {
	float min = INFINITY;
	int nodeIndex = 0;;
	int i;

	for (i = 0; i < size; i++) {
		if (min > dist[i] && Q[i] == true) {
			min = dist[i];
			nodeIndex = i;

		}
	}
	return nodeIndex;
}