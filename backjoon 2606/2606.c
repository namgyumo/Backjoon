#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct AbjNode {
	int data;
	struct AbjNode* Next;
}AbjNode;

typedef struct Node {
	int data;
	struct Node* Next;
	AbjNode* abj;
}Node;

Node* MakeNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->Next = NULL;
	node->abj = NULL;
	return  node;
}

void InsertNode(Node** head, int data) {
	if (*head == NULL) {
		*head = MakeNode(data);
		return;
	}
	Node* temp = *head;
	while (temp->Next != NULL) {
		temp = temp->Next;
	}
	temp->Next = MakeNode(data);
}

Node* FindNode(Node* head, int data) {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->data == data) {
			return temp;
		}
		temp = temp->Next;
	}
	return NULL;
}

void AbjLink(Node* head, int first_data, int second_data) {
	Node* first = FindNode(head, first_data);
	Node* second = FindNode(head, second_data);
	if (first == NULL || second == NULL) return;
	AbjNode* first_abj = (AbjNode*)malloc(sizeof(AbjNode));
	first_abj->data = second_data;
	first_abj->Next = first->abj;
	first->abj = first_abj;
	AbjNode* second_abj = (AbjNode*)malloc(sizeof(AbjNode));
	second_abj->data = first_data;
	second_abj->Next = second->abj;
	second->abj = second_abj;
}

void Dfs(Node* head, int start_data, bool visited[], int* count) {
	Node* temp = FindNode(head, start_data);
	if (temp == NULL) return;

	visited[start_data - 1] = true;
	(*count)++;

	AbjNode* cur = temp->abj;
	while (cur != NULL) {
		if (!visited[cur->data - 1]) {
			Dfs(head, cur->data, visited, count);
		}
		cur = cur->Next;
	}
}

int main() {
	int input,num,count = 0;
	Node* head = NULL;
	scanf("%d", &input);
	bool visited[100] = { false };
	for (int i = 0; i < input; i++) {
		InsertNode(&head, i + 1);
	}
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		int first_data, secnod_data;
		scanf("%d %d", &first_data, &secnod_data);
		AbjLink(head, first_data, secnod_data);
	}
	Dfs(head, 1, visited, &count);
	printf("%d", count-1);
}
