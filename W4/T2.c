#include <stdio.h>
#include <stdlib.h>
#define MAXG 1000

struct edge {
  int no;
  int adjvex;
  struct edge* next;
};

struct ver {
  struct edge* link;
};

struct ver graph[MAXG] = {};
char visited[MAXG] = {};
int path[MAXG] = {};

struct edge* insertedge(struct edge* head, int adjvex, int no) {
  struct edge *e, *p;
  e = (struct edge*)malloc(sizeof(struct edge));
  e->adjvex = adjvex;
  e->no = no;
  e->next = NULL;
  if (head == NULL) {
    head = e;
    return head;
  }
  for (p = head; p->next != NULL; p = p->next);
  p->next = e;
  return head;
}

void creategraph(int edgecnt) {
  int no, from, to;
  for (int i = 0; i < edgecnt; i++) {
    scanf("%d%d%d", &no, &from, &to);
    graph[from].link = insertedge(graph[from].link, to, no);
    graph[to].link = insertedge(graph[to].link, from, no);
  }
}

void printpath(int level) {
  for (int i = 0; i < level; i++) {
    printf("%d ", path[i]);
  }
  printf("\n");
}

void eDFS(int nownode, int level, int nodelast) {
  struct edge* p;
  if (nownode == nodelast) {
    printpath(level);
    return;
  }
  for (p = graph[nownode].link; p != NULL; p = p->next) {
    if (!visited[p->adjvex]) {
      path[level] = p->no;
      visited[p->adjvex] = 1;
      eDFS(p->adjvex, level + 1, nodelast);
      visited[p->adjvex] = 0;
    }
  }
}

int main() {
  int nodecnt, edgecnt;
  scanf("%d %d", &nodecnt, &edgecnt);
  creategraph(edgecnt);
  int node0 = 0;
  int nodelast = nodecnt - 1;
  visited[node0] = 1;
  eDFS(node0, 0, nodelast);
  return 0;
}