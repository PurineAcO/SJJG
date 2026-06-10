#include <stdio.h>
#define MAXG 110
#define INF 114514

struct edge {
    int id;
    int weight;
};

struct edge graph[MAXG][MAXG] = {0};
int edges[MAXG] = {0};
int weight[MAXG][MAXG];

void prim(int nodecnt, int src) {
    int minweight[MAXG];
    int min, k;
    for (int i = 0; i < nodecnt; i++) {
        minweight[i] = weight[src][i];
        edges[i] = src;
    }
    minweight[src] = 0;
    for (int i = 1; i < nodecnt; i++) {
        min = INF;
        k = -1;
        for (int j = 0; j < nodecnt; j++) {
            if (minweight[j] != 0 && minweight[j] < min) {
                min = minweight[j];
                k = j;
            }
        }
        minweight[k] = 0;
        for (int j = 0; j < nodecnt; j++) {
            if (minweight[j] != 0 && weight[k][j] < minweight[j]) {
                minweight[j] = weight[k][j];
                edges[j] = k;
            }
        }
    }
}

void bbst(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

int main() {
    int nodecnt, edgecnt, sumweight = 0;
    int edgeno[MAXG];
    
    scanf("%d%d", &nodecnt, &edgecnt);
    
    // 初始化权重矩阵为INF
    for (int i = 0; i < nodecnt; i++)
        for (int j = 0; j < nodecnt; j++)
            weight[i][j] = INF;
    
    
    for (int i = 0; i < edgecnt; i++) {
        int id, u, v, w;
        scanf("%d%d%d%d", &id, &u, &v, &w);
        graph[u][v].id = graph[v][u].id = id;
        graph[u][v].weight = graph[v][u].weight = w;
        weight[u][v] = weight[v][u] = w;
    }
    
    prim(nodecnt, 0);

    for (int i = 1; i < nodecnt; i++) {
        sumweight += graph[i][edges[i]].weight;
        edgeno[i-1] = graph[i][edges[i]].id;   
    }
    
    bbst(edgeno, nodecnt-1);
    
    printf("%d\n", sumweight);
    for (int i = 0; i < nodecnt-1; i++)
        printf("%d ", edgeno[i]);
    printf("\n");
    
    return 0;
}