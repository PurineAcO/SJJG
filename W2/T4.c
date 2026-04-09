#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *create_list() {
    int x;
    struct ListNode *head = NULL;
    struct ListNode *r = NULL;
    while (scanf("%d", &x) != EOF) {
        struct ListNode *p = (struct ListNode *)malloc(sizeof(struct ListNode));
        p->val = x;
        p->next = NULL;
        if (head == NULL)
            head = p;
        else
            r->next = p;
        r = p;
    }
    return head;
}



struct ListNode *delete_duplicates(struct ListNode *head){

    struct ListNode* different[400]={};
    int cntter[300]={};
    int differentcnt=0;
    struct ListNode* nowplace=head;

    while(nowplace!=NULL){cntter[nowplace->val+100]++;nowplace = nowplace->next;}
    nowplace = head;
    while(nowplace!=NULL){
        if(cntter[nowplace->val+100]==1){
        different[differentcnt]=nowplace;
        differentcnt++;}
        nowplace = nowplace->next;
    }

    struct ListNode* realhead=NULL;
    struct ListNode* realtail=NULL;
    for(int i=0;i<differentcnt;i++){
        struct ListNode* p =malloc(sizeof(struct ListNode));
        p->val = different[i]->val;
        p->next = NULL;
        if(realhead ==NULL){realhead=p;}
        else{realtail->next = p;}
        realtail = p;
    }


    return realhead;
}

int main() {

    struct ListNode *head = create_list();

    head = delete_duplicates(head);

    for (struct ListNode *p = head; p; p = p->next) {
        printf("%d", p->val);
        if (p->next)
            printf(" ");
    }
    return 0;
}