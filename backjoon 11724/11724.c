#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node;

typedef struct AdjList {
    struct Node* node;
    struct AdjList* Next;
} AdjList;

typedef struct Node {
    int data;
    struct Node* Next;
    bool check;
    AdjList* adj;
} Node;

Node* MakeNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->adj = NULL;
    node->Next = NULL;
    node->check = false;
    return node;
}

void InsertNode(Node** head, int data) {
    if (*head == NULL) {
        *head = MakeNode(data);
        return;
    }
    Node* temp = *head;
    while (temp->Next != NULL) temp = temp->Next;
    temp->Next = MakeNode(data);
}

Node* FindNode(Node* head, int data) {
    while (head != NULL) {
        if (head->data == data) return head;
        head = head->Next;
    }
    return NULL;
}

void LinkAdj(Node* head, int data_a, int data_b) {
    Node* a = FindNode(head, data_a);
    Node* b = FindNode(head, data_b);
    if (!a || !b) return;

    AdjList* adj_a = (AdjList*)malloc(sizeof(AdjList));
    adj_a->node = b;
    adj_a->Next = a->adj;
    a->adj = adj_a;

    AdjList* adj_b = (AdjList*)malloc(sizeof(AdjList));
    adj_b->node = a;
    adj_b->Next = b->adj;
    b->adj = adj_b;
}

void Dfs(Node* node) {
    if (node->check) return;
    node->check = true;
    AdjList* adj = node->adj;
    while (adj != NULL) {
        if (!adj->node->check) Dfs(adj->node);
        adj = adj->Next;
    }
}

void FreeGraph(Node* head) {
    while (head != NULL) {
        AdjList* adj = head->adj;
        while (adj != NULL) {
            AdjList* tempadj = adj;
            adj = adj->Next;
            free(tempadj);
        }
        Node* temp = head;
        head = head->Next;
        free(temp);
    }
}

int main() {
    int nodenum, linenum, count = 0;
    scanf("%d %d", &nodenum, &linenum);

    Node* head = NULL;
    for (int i = 1; i <= nodenum; i++) {
        InsertNode(&head, i);
    }

    for (int i = 0; i < linenum; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        LinkAdj(head, a, b);
    }

    Node* temp = head;
    while (temp != NULL) {
        if (!temp->check) {
            count++;
            Dfs(temp);
        }
        temp = temp->Next;
    }

    printf("%d\n", count);
    FreeGraph(head);
}

