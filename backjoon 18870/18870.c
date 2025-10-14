#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//정렬 후 중복 제거 후 이진탐색으로 인덱스 추출

bool can_merge(int left_side,int right_side,int mid,int right) {
	return left_side <= mid && right_side <= right;
}

void merge(int arr[], int left, int mid, int right) {
	int left_side = left;
	int right_side = mid+1;
	int i = 0;
	int max_index = right - left + 1;
	int* insert_arr = (int*)malloc(sizeof(int) * max_index);
	while (can_merge(left_side, right_side, mid, right) && i < max_index) {
		if (arr[left_side] > arr[right_side]) insert_arr[i++] = arr[right_side++];
		else insert_arr[i++] = arr[left_side++];
	}
	while (left_side <= mid && i < max_index) {
		insert_arr[i++] = arr[left_side++];
	}
	while (right_side <= right && i < max_index) {
		insert_arr[i++] = arr[right_side++];
	}
	for (int i = 0; i < max_index; i++) {
		arr[left+i] = insert_arr[i];
	}
	free(insert_arr);
}

void merge_sort(int arr[], int left, int right) {
	if (right - left <= 0) return;
	int mid = (right + left) / 2;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

int binary_search(int arr[], int arr_size, int find_value) {
	int max = arr_size-1;
	int min = 0;
	while (min <= max) {
		int mid = (min + max) / 2;
		if (arr[mid] > find_value) {
			max = mid - 1;
		}
		else if (arr[mid] < find_value) {
			min = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

int main() {
	int input_num;
	scanf("%d", &input_num);
	int* arr = (int*)malloc(sizeof(int) * input_num);
	int* second_arr = (int*)malloc(sizeof(int) * input_num);
	for (int i = 0; i < input_num; i++) {
		scanf("%d", &arr[i]);
		second_arr[i] = arr[i];
	}
	merge_sort(second_arr, 0, input_num-1);
	int new_size = 0;
	for (int i = 0; i < input_num; i++) {
		if (new_size == 0 || second_arr[i] != second_arr[new_size - 1]) {
			second_arr[new_size++] = second_arr[i];
		}
	}
	int second_size = new_size;
	for (int i = 0; i < input_num; i++) {
		int data = binary_search(second_arr, second_size, arr[i]);
		printf("%d ", data);
	}
	free(arr);
	free(second_arr);
}
