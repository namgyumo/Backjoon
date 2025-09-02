#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void change_land(int** map, int x, int y,int max_x,int max_y) {
	if (max_x > x+1 && map[y][x + 1] == 1) {
		map[y][x + 1] = 0;
		change_land(map, x + 1, y, max_x, max_y);
	}
	if (x-1>=0 && map[y][x -1] == 1) {
		map[y][x - 1] = 0;
		change_land(map, x - 1, y, max_x, max_y);
	}
	if (max_y > y+1 && map[y+1][x] == 1) {
		map[y+1][x] = 0;
		change_land(map, x, y+1, max_x, max_y);
	}
	if (y-1>=0 && map[y-1][x] == 1) {
		map[y-1][x] = 0;
		change_land(map, x, y-1, max_x, max_y);
	}
	if (max_x > x+1 && max_y > y+1 && map[y+1][x + 1] == 1) {
		map[y+1][x + 1] = 0;
		change_land(map, x + 1, y+1, max_x, max_y);
	}
	if (max_x > x+1 && y-1>=0 && map[y-1][x + 1] == 1) {
		map[y-1][x + 1] = 0;
		change_land(map, x + 1, y-1, max_x, max_y);
	}
	if (x - 1 >= 0 && max_y > y + 1 && map[y+1][x - 1] == 1) {
		map[y+1][x - 1] = 0;
		change_land(map, x - 1, y+1, max_x, max_y);
	}
	if (x-1>=0&&y-1>=0 && map[y-1][x - 1] == 1) {
		map[y-1][x - 1] = 0;
		change_land(map, x - 1, y-1, max_x, max_y);
	}
	return;
}

int island(int** map,int max_x,int max_y) {
	int count = 0;
	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			if (map[i][j] == 1) {
				count++;
				change_land(map, j, i, max_x, max_y);
			}
		}
	}
	return count;
}

int main() {
	int size_x,size_y;
	while (1) {
		scanf("%d %d", &size_x, &size_y);
		if (size_x == 0 && size_y == 0) {
			break;
		}
		else if (size_x == 0 || size_y == 0) {
			continue;
		}
		int** map = (int**)malloc(sizeof(int*) * (size_y));
		for (int i = 0; i < size_y; i++) {
			map[i] = (int*)malloc(sizeof(int) * (size_x));
		}
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		printf("%d\n",island(map, size_x, size_y));

		for (int i = 0; i < size_y; i++) free(map[i]);
		free(map);
	}
}