#include <stdio.h>
#include <stdlib.h>

typedef struct nodeptr{
    int data;
    struct nodeptr* next;
}*node;

node initlist(int firstnum) {
    node head;
    head = (node)malloc(sizeof(struct nodeptr));
    head->data = firstnum;
    head->next = head;
    return head;
}

node insert(node head,node place, int newdata) {
    node thisdata;
    thisdata = (node)malloc(sizeof(struct nodeptr));
    thisdata->data = newdata;
    thisdata->next = head;
    place->next = thisdata;
    return thisdata;
}

// void printlist(node head) {
//     printf("%d ",head->data);
//     for (node p = head->next; p !=head; p = p->next) {
//         printf("%d ", p->data);
//     }
// }


int judge(int number){
    if(number%7==0){return 1;}
    while(number>0){
        if(number%10==7){return 1;}
        number = number/10;
    }
    return 0;
}

int main(){
    int total;
    node head = initlist(1);
    node cur=head;
    scanf("%d",&total);
    if(total==1){printf("1");return 0;}
    for(int i=2;i<=total;i++){cur = insert(head,cur,i);}
    int outcnt=0;int cnt=2;cur = head->next;
    node prev;
    while(outcnt<total-1){
        if(judge(cnt)==1){
            node tmp=cur;
            prev->next = tmp->next;
            cur = tmp->next;
            // printf("%d\n",tmp->data);
            free(tmp);
            outcnt++;
            cnt++;
            continue;
        }
        if(outcnt==total-1){break;}
        prev = cur;
        cur = cur->next;
        cnt++;
    }
    printf("%d",prev->data);

}