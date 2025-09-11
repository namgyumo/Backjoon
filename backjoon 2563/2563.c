#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


int main() {
	int input_num;
	scanf("%d", &input_num);
	int** arr = (int**)malloc(sizeof(int*) * input_num);
	for (int i = 0; i < input_num; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
	}
	for (int i = 0; i < input_num; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	int board[100][100] = { 0 };
	for (int i = 0; i < input_num; i++) {
		int x = arr[i][0];
		int y = arr[i][1];
		for (int dx = 0; dx < 10; dx++) {
			for (int dy = 0; dy < 10; dy++) {
				board[x + dx][y + dy] = 1;
			}
		}
	}
	int area = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (board[i][j] == 1) area++;
		}
	}
	printf("%d\n", area);
}
