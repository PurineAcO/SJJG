#include <stdio.h>
#include <string.h>
#define MAXN 50

int stack[MAXN] = {};
int top;

void initstack() { top = -1; }
int ifempty() { return top == -1; }
void push(int item) {
  top++;
  stack[top] = item;
}
int pop() {
  int r = stack[top];
  top--;
  return r;
}

void printstack() {
  for (int i = 0; i <= top; i++) {
    printf("%d ", stack[i]);
  }
}

int main() {
  char string[51];
  scanf("%s", string);
  initstack();

  int thisnum = 0;
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] >= '0' && string[i] <= '9') {
      thisnum = thisnum * 10 + string[i] - '0';
    }
    if (string[i] == '.') {
      push(thisnum);
      thisnum = 0;
    }
    if (string[i] == '+' || string[i] == '-' || string[i] == '*' ||
        string[i] == '/') {
      int a = pop();
      int b = pop();
      if (string[i] == '+') {
        push(b + a);
      }
      if (string[i] == '-') {
        push(b - a);
      }
      if (string[i] == '*') {
        push(b * a);
      }
      if (string[i] == '/') {
        push((int)b / a);
      }
      // printf("%d %c %d = %d\n",a,string[i],b,stack[top]);
    }
  }

  printstack();

  return 0;
}