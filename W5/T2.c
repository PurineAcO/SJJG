#include <stdio.h>

int a[10005], tmp[10005];
long long ans = 0;

void merge_sort(int l, int r) {
  if (l >= r) return;
  int mid = (l + r) / 2;
  merge_sort(l, mid);
  merge_sort(mid + 1, r);
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j]) {
      tmp[k++] = a[i++];
    } else {
      tmp[k++] = a[j++];
      ans += mid - i + 1;
    }
  }
  while (i <= mid) tmp[k++] = a[i++];
  while (j <= r) tmp[k++] = a[j++];
  for (i = l; i <= r; i++) a[i] = tmp[i];
}

int main() {
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &a[i]);
  merge_sort(0, N - 1);
  printf("%lld\n", ans);
  return 0;
}