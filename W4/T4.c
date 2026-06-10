#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 114514

int main() {
  int n, src;
  scanf("%d", &n);
  scanf("%d", &src);
  src--;

  int dist[80][80];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) dist[i][j] = INF;

  char token[10];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%s", token);
      if (token[0] == '-' && token[1] == '\0') {
        continue;
      }
      dist[i][j] = atoi(token);
    }
  }

  for (int i = 0; i < n; ++i) dist[i][i] = 0;

  // Floyd‑Warshall
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (dist[i][k] != INF && dist[k][j] != INF &&
            dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];

  for (int v = 0; v < n; ++v) {
    if (v == src) continue;
    printf("(%d -> %d) = %d\n", src + 1, v + 1, dist[src][v]);
  }

  return 0;
}