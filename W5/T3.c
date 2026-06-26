#include <stdio.h>
#include <string.h>

int head[10005], to[200005], nxt[200005], ecnt;
int q[10005], dist[10005];
long long cnt[10005];

void add(int u, int v) {
  to[++ecnt] = v;
  nxt[ecnt] = head[u];
  head[u] = ecnt;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    add(x, y);
    add(y, x);
  }

  memset(dist, -1, sizeof(dist));
  dist[1] = 0;
  cnt[1] = 1;
  int l = 0, r = 0;
  q[r++] = 1;

  while (l < r) {
    int u = q[l++];
    for (int e = head[u]; e; e = nxt[e]) {
      int v = to[e];
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        cnt[v] = cnt[u];
        q[r++] = v;
      } else if (dist[v] == dist[u] + 1) {
        cnt[v] += cnt[u];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    printf("%lld\n", cnt[i]);
  }
  return 0;
}