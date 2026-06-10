#include <stdio.h>
#include <stdlib.h>
#define MAXG 102
#define max(a, b) a >= b ? a : b
#define min(a, b) a <= b ? a : b

#define vertype int

int head;
int last;

typedef struct edge {
  int adjvex;
  struct edge* next;
} ELink;

typedef struct ver {
  vertype number;
  ELink* link;
} VLink;

struct edgepair {
  int from;
  int to;
};

ELink* insertedge(ELink* head, int index) {
  ELink *e, *p;
  e = (ELink*)malloc(sizeof(ELink));
  e->adjvex = index;
  e->next = NULL;
  if (head == NULL) {
    head = e;
    return head;
  }
  for (p = head; p->next != NULL; p = p->next);
  p->next = e;
  return head;
}

void creategraph(VLink graph[], struct edgepair ft[], int cnt) {
  for (int i = 0; i < cnt; i++) {
    if (ft[i].from >= 0 && ft[i].to >= 0) {
      graph[ft[i].from].link = insertedge(graph[ft[i].from].link, ft[i].to);
      graph[ft[i].to].link = insertedge(graph[ft[i].to].link, ft[i].from);
    }
  }
}

void printgraph(VLink graph[], int nodecnt) {
  for (int i = 0; i < nodecnt; i++) {
    printf("%d: ", i);
    ELink* p = graph[i].link;
    while (p != NULL) {
      printf("%d ", p->adjvex);
      p = p->next;
    }
    printf("\n");
  }
}

void deletenode(VLink graph[], int deletepos, int edgecnt,
                struct edgepair ft[]) {
  graph[deletepos].link = NULL;
  graph[deletepos].number = -1;
  for (int i = 0; i <= edgecnt; i++) {
    if (ft[i].from == deletepos) {
      ELink* pre = graph[ft[i].to].link;
      while (pre != NULL && pre->next != NULL) {
        if (pre->next->adjvex == deletepos) {
          ELink* tmp = pre->next;
          pre->next = pre->next->next;
          free(tmp);
          return;
        } else {
          pre = pre->next;
        }
      }
    }

    if (ft[i].to == deletepos) {
      ELink* pre = graph[ft[i].from].link;
      while (pre != NULL && pre->next != NULL) {
        if (pre->next->adjvex == deletepos) {
          ELink* tmp = pre->next;
          pre->next = pre->next->next;
          free(tmp);
          return;
        } else {
          pre = pre->next;
        }
      }
    }
  }
}

void DFS(VLink graph[], int visited[], int nodepos) {
  ELink* p;
  visited[nodepos] = 1;
  if (graph[nodepos].number != -1) {
    printf("%d ", nodepos);
  }
  for (p = graph[nodepos].link; p != NULL; p = p->next) {
    if (!visited[p->adjvex]) {
      DFS(graph, visited, p->adjvex);
    }
  }
}

void travelDFS(VLink graph[], int visited[], int nodecnt) {
  for (int i = 0; i < nodecnt; i++) {
    visited[i] = 0;
  }
  for (int i = 0; i < nodecnt; i++) {
    if (visited[i] == 0) {
      DFS(graph, visited, i);
    }
  }
}

void bbst(struct edgepair ft[], int edgecnt) {
  for (int i = 0; i < edgecnt - 1; i++) {
    for (int j = 0; j < edgecnt - 1 - i; j++) {
      if (ft[j].from > ft[j + 1].from) {
        struct edgepair temp = ft[j];
        ft[j] = ft[j + 1];
        ft[j + 1] = temp;
      } else if (ft[j].from == ft[j + 1].from) {
        if (ft[j].to > ft[j + 1].to) {
          struct edgepair temp2 = ft[j];
          ft[j] = ft[j + 1];
          ft[j + 1] = temp2;
        }
      }
    }
  }
}

void initbuf() {
  head = 0;
  last = 0;
}

int ifemptybuf() {
  if (head == last) {
    return 1;
  } else {
    return 0;
  }
}

void enbuf(int readbuf[], int nodepos) {
  readbuf[last] = nodepos;
  last++;
}

int debuf(int readbuf[]) {
  int res = readbuf[head];
  head++;
  return res;
}

void BFS(VLink graph[], int visited[], int readbuf[], int nodepos) {
  ELink* p;
  visited[nodepos] = 1;
  if (graph[nodepos].number != -1) {
    printf("%d ", nodepos);
  }
  enbuf(readbuf, nodepos);
  // printf("%d:", readbuf[head]);
  while (head != last) {
    nodepos = debuf(readbuf);
    for (p = graph[nodepos].link; p != NULL; p = p->next) {
      if (!visited[p->adjvex]) {
        if (graph[p->adjvex].number != -1) {
          printf("%d ", p->adjvex);
        }
        visited[p->adjvex] = 1;
        enbuf(readbuf, p->adjvex);
      }
    }
  }
}

void travelBFS(VLink graph[], int visited[], int readbuf[], int nodecnt) {
  for (int i = 0; i < nodecnt; i++) {
    visited[i] = 0;
  }
  for (int i = 0; i < nodecnt; i++) {
    if (!visited[i]) {
      BFS(graph, visited, readbuf, i);
    }
  }
}

int main() {
  int nodecnt, edgecnt, deletepos;
  struct edgepair edgepr[6000] = {};
  VLink graph[MAXG] = {};
  scanf("%d%d", &nodecnt, &edgecnt);
  for (int i = 0; i < edgecnt; i++) {
    int temp1, temp2;
    scanf("%d%d", &temp1, &temp2);
    edgepr[i].from = min(temp1, temp2);
    edgepr[i].to = max(temp1, temp2);
  }
  scanf("%d", &deletepos);
  bbst(edgepr, edgecnt);
  creategraph(graph, edgepr, edgecnt);
  // printgraph(graph, nodecnt);

  int visited[MAXG] = {};
  int readbuf[MAXG] = {};
  initbuf();
  travelDFS(graph, visited, nodecnt);
  printf("\n");
  travelBFS(graph, visited, readbuf, nodecnt);
  printf("\n");

  deletenode(graph, deletepos, edgecnt, edgepr);
  // printgraph(graph, nodecnt);
  travelDFS(graph, visited, nodecnt);
  printf("\n");
  travelBFS(graph, visited, readbuf, nodecnt);
}