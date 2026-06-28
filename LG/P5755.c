#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 33000   

typedef struct Node {
    int child[26];       
} Node;

Node trie[MAX_NODES];
int nodeCnt = 0;       

// 插入一个单词
void insertWord(char s[]) {
    int curr = 0;        
    for (int i = 0; s[i] != '\0'; i++) {
        int idx = s[i] - 'A';
        if (trie[curr].child[idx] == 0) {
            // 如果对应子节点不存在，创建新节点
            trie[curr].child[idx] = ++nodeCnt;
        }
        curr = trie[curr].child[idx];
    }
}

int main() {
    char word[100];      
    while (scanf("%s", word) != EOF) {
        insertWord(word);
    }
    printf("%d\n", nodeCnt + 1);
    return 0;
}