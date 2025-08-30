#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 리스트 사용, head,tail사용, 이중 포인터 사용

typedef struct Node {
    int data;
    struct Node* child;
} Node;

Node* make_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->child = NULL;
    return node;
}

void insert_node(Node** head,Node** tail,int data) {
    Node* newnode = make_node(data);
    if (*head == NULL) {
        *head = newnode;
        *tail = *head;
        return;
    }
    (*tail)->child = newnode;
    (*tail) = (*tail)->child;
}

int delete_head(Node** head) {
    if (*head == NULL) return -2;
    Node* temp = *head;
    int val = temp->data;
    *head = temp->child;
    free(temp);
    return val;
}

int back_head(Node** head, Node** tail) {
    if (*head == NULL || *tail == NULL) return -2;
    if ((*head)->child == NULL) return -1;

    Node* oldHead = *head;
    *head = oldHead->child;
    oldHead->child = NULL;
    (*tail)->child = oldHead;
    *tail = oldHead;

    return oldHead->data;
}

int main() {
    int input_number;
    scanf("%d", &input_number);

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 1; i <= input_number; i++) {
        insert_node(&head,&tail, i);
    }

    while (head->child != NULL) {
        delete_head(&head);        // 맨 위 카드 버리기
        if (head->child != NULL)   // 카드가 남아있으면 뒤로 보내기
            back_head(&head, &tail);
    }

    printf("%d\n", head->data);
    free(head);
    return 0;
}
