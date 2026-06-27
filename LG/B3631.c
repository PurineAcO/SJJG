#include <stdio.h>
#include <stdlib.h>

typedef struct nodeptr {
  int data;
  struct nodeptr* next;
}* node;  // node 的性质是指针

// 一般可以用指针数组来加快find的速度,使之变成O(1),但是根治的手段是使用双向链表
// 或者可以根据操作次数,来判断是否需要进行这种优化
node nodelist[1000009] = {};

node initlist(int firstnum) {
  // 初始化整个链表
  node head;
  // 插入一个firstnum,返回整个链表头指针p
  head = (node)malloc(sizeof(struct nodeptr));
  head->data = firstnum;
  head->next = NULL;
  // nodelist[firstnum] = head; // 可选
  return head;
}

void insert(node place, int newdata) {
  // 向链表place后面插入某个数据data,先临时形成一个node,再进行插入,你需要先知道place是啥
  node thisdata;
  thisdata = (node)malloc(sizeof(struct nodeptr));
  thisdata->data = newdata;
  thisdata->next = place->next;
  place->next = thisdata;
  // nodelist[newdata] = thisdata; // 可选
}

node find(node head, int target) {
  // 查找某个target的位置,这里没有处理找不到的情况
  for (node fast = head; fast != NULL; fast = fast->next) {
    if (fast->data == target) {
      return fast;
    }
  }
  // return nodelist[target]; 优化手段
}

void del_one(node nowplace) {
  // 删除nowplace后面的元素
  node temp = nowplace->next;
  if (temp == NULL) {
    return;
  }
  nowplace->next = temp->next;
  free(temp);
}

node del_two(node head, int target) {
  // 处理头结点
  if (head->data == target) {
    node temp = head->next;
    free(head);
    return temp;
  }

  // 查找目标及其前驱
  node prev = head;
  node cur = head->next;
  while (cur != NULL && cur->data != target) {
    prev = cur;
    cur = cur->next;
  }

  // 删除 cur
  prev->next = cur->next;
  free(cur);
  return head;
}

void printlist(node head) {
  // 打印链表内容 一般用于测试
  for (node p = head; p != NULL; p = p->next) {
    printf("%d ", p->data);
  }
}

int main() {
  node head = initlist(1);
  int total, token, first, second;
  scanf("%d", &total);
  for (int cnt = 1; cnt <= total; cnt++) {
    scanf("%d", &token);
    if (token == 1) {
      scanf("%d %d", &first, &second);
      insert(find(head, first), second);
    }

    if (token == 2) {
      scanf("%d", &first);
      node nowplace = find(head, first);
      if (nowplace->next != NULL) {
        printf("%d\n", nowplace->next->data);
      } else if (nowplace->next == NULL) {
        printf("0\n");
      }
    }

    if (token == 3) {
      scanf("%d", &first);
      head = del_two(head, first);
    }
  }
  printlist(head);

  return 0;
}