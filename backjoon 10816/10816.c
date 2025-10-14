#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//구조체로 숫자와 카운트 저장, 힙정렬 후 이분탐색 ....... (성공)

typedef struct Node {
	int data;
	int count;
}Node;

bool can_swap(int i, Node arr[],int arr_size, int largest) {
	return i < arr_size && arr[i].data > arr[largest].data;
}

void heapify(Node arr[], int arr_size, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (can_swap(left, arr, arr_size, largest)) {
		largest = left;
	}
	if (can_swap(right, arr, arr_size, largest)) {
		largest = right;
	}
	if (largest != i) {
		Node temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, arr_size, largest);
	}
}

void heapsort(Node arr[], int arr_size) {
	for (int i = arr_size / 2 - 1; i >= 0; i--) {
		heapify(arr, arr_size, i);
	}
	for (int i = arr_size - 1; i > 0; i--) {
		Node temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0);
	}
}

Node make_node(int data) {
	Node node;
	node.data = data;
	node.count = 1;
	return node;
}

int binary_search(Node arr[], int data, int arr_size) {
	int max = arr_size-1;
	int min = 0;
	while (min <= max) {
		int mid = (max + min) / 2;
		if (arr[mid].data < data) {
			min = mid + 1;
		}
		else if (arr[mid].data > data) {
			max = mid - 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

int main() {
	int input01, input02;
	scanf("%d", &input01);
	Node* arr = (Node*)malloc(sizeof(Node) * input01);
	int arr_size = 0;
	for (int i = 0; i < input01; i++) {
		int data;
		scanf("%d", &data);
		arr[arr_size] = make_node(data);
		arr_size++;
	}
	heapsort(arr, arr_size);
	int new_size = 0;
	for (int i = 0; i < arr_size; i++) {
		if (new_size > 0 && arr[new_size - 1].data == arr[i].data) {
			arr[new_size - 1].count++;
		}
		else {
			arr[new_size] = arr[i];
			new_size++;
		}
	}
	arr_size = new_size;
	scanf("%d", &input02);
	for (int i = 0; i < input02; i++) {
		int data;
		scanf("%d", &data);
		int index = binary_search(arr, data, arr_size);
		if (index == -1) {
			printf("0 ");
		}
		else {
			printf("%d ", arr[index].count);
		}
	}
}
