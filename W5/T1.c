#include <stdio.h>
int main() {
  int M, N;
  scanf("%d %d", &M, &N);
  int memory[105];
  int size = 0;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    int word;
    scanf("%d", &word);
    int found = 0;
    for (int j = 0; j < size; j++) {
      if (memory[j] == word) {
        found = 1;
        break;
      }
    }
    if (!found) {
      ans++;
      if (size < M) {
        memory[size++] = word;
      } else {
        for (int j = 0; j < size - 1; j++) {
          memory[j] = memory[j + 1];
        }
        memory[size - 1] = word;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}