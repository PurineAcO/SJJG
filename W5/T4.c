#include <stdio.h>
#include <string.h>

int trie[100005][26];
int tot = 1;

int main() {
  for (int i = 0; i < 100005; i++) {
    for (int j = 0; j < 26; j++) {
      trie[i][j] = -1;
    }
  }
  char word[70];
  while (scanf("%s", word) != EOF) {
    int u = 0;
    for (int i = 0; word[i]; i++) {
      int c = word[i] - 'A';
      if (trie[u][c] == -1) {
        trie[u][c] = tot++;
      }
      u = trie[u][c];
    }
  }
  printf("%d\n", tot);
  return 0;
}