#include <stdio.h>

int total = 0;

void bbst(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = tmp;
        total++;
      }
    }
  }
}

int main() {
  int n;
  int table[10005];
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &table[i]);
  }
  bbst(table, n);
  printf("%d", total);
}