#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//4방향 연결그래프 활용
//2차원 동적 배열 활용 
//재귀 함수 활용
//자료구조, 포인터 공부

typedef struct Node {
	int x, y;
	int flag;
	struct Node* front;
	struct Node* back;
	struct Node* left;
	struct Node* right;
}Node;

Node make_node(int flag,int x, int y) {
	Node node;
	node.x = x;
	node.y = y;
	node.front = NULL;
	node.back = NULL;
	node.left = NULL;
	node.right = NULL;
	node.flag = 0;
	if (flag == 1) {
		node.flag = 1;
	}
	return node;
}

void change_flag(Node** nodes, int x, int y) {
	nodes[x][y].flag = 0;
	if (nodes[x][y].right != NULL && nodes[x][y].right->flag == 1) {
		change_flag(nodes, x + 1, y);
	}
	if (nodes[x][y].left != NULL && nodes[x][y].left->flag == 1) {
		change_flag(nodes, x - 1, y);
	}
	if (nodes[x][y].back != NULL && nodes[x][y].back->flag == 1) {
		change_flag(nodes, x, y - 1);
	}
	if (nodes[x][y].front != NULL && nodes[x][y].front->flag == 1) {
		change_flag(nodes, x , y + 1);
	}
	
}

int find_num(Node** nodes, int max_x, int max_y) {
	int count = 0;
	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			if (nodes[i][j].flag == 1) {
				change_flag(nodes, i, j); 
				count++;
			}
		}
	}
	return count;
}


void make_nodes(int max_x,int max_y,int casenum) {
	Node** nodes = (Node**)malloc(sizeof(Node*)*max_x);
	for (int i = 0; i < max_x; i++) {
		nodes[i] = (Node*)malloc(sizeof(Node)*max_y);
	}
	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			nodes[i][j] = make_node(0, i, j);
		}
	}

	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			if (i > 0) {
				nodes[i][j].left = &nodes[i - 1][j];
			}
			if (i < max_x - 1) {
				nodes[i][j].right = &nodes[i + 1][j];
			}
			if (j > 0) {
				nodes[i][j].back = &nodes[i][j - 1];
			}
			if (j < max_y - 1) {
				nodes[i][j].front = &nodes[i][j + 1];
			}
		}
	}

	for (int i = 0; i < casenum; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		nodes[x][y].flag = 1;
	}
	int resert = find_num(nodes, max_x, max_y);
	printf("%d\n", resert);
	free(nodes);
}

int main() {
	int input;
	scanf("%d", &input);
	for (int i = 0; i < input; i++) {
		int x, y, casenum;
		scanf("%d %d %d", &x, &y, &casenum);
		make_nodes(x, y, casenum);
	}
}

