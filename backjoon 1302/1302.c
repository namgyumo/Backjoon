#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//배열에 이름,숫자 구조체 넣고 이진탐색으로 이름 찾고 숫자 증가 후 힙정렬

typedef struct Books {
	char name[51];
	int count;
	int used;
}Books;

int isBestseller(Books a,Books b) {
	if (a.count != b.count) {
		return a.count > b.count;
	}
	return strcmp(a.name, b.name) < 0;
}

int isnamesort(Books a, Books b) {
	return strcmp(a.name, b.name) < 0;
}

void heapify(Books arr[], int arr_size, int i,int islast) {
	int largest = i;
	int left = i * 2 + 1;
	int right = i * 2 + 2;

	if (islast) {
		if (left < arr_size && isBestseller(arr[largest], arr[left])) {
			largest = left;
		}
		if (right < arr_size && isBestseller(arr[largest], arr[right])) {
			largest = right;
		}
	}
	else {
		if (left < arr_size && isnamesort(arr[largest], arr[left])) {
			largest = left;
		}
		if (right < arr_size && isnamesort(arr[largest], arr[right])) {
			largest = right;
		}
	}
	if (largest != i) {
		Books temp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = temp;
		heapify(arr, arr_size, largest,islast);
	}
}

void heapsort(Books arr[], int arr_size,int islast) {
	for (int i = arr_size / 2 - 1; i >= 0; i--) {
		heapify(arr, arr_size, i,islast);
	}
	for (int i = arr_size - 1; i > 0; i--) {
		Books temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0,islast);
	}
}

int same_name(Books arr[], int arr_size, char name[]) {
	heapsort(arr, arr_size, 0);
	int max = arr_size - 1;
	int min = 0;
	while (min <= max) {
		int mid = (min + max) / 2;
		int cmp = strcmp(arr[mid].name, name);
		if (cmp == 0) {
			return mid;
		}
		else if (cmp < 0) {
			min = mid + 1;
		}
		else {
			max = mid - 1;
		}
	}
	return -1;
}

int is_arr_size(Books arr[],int input) {
	int i = 0;
	while (i<input&&arr[i].used == 1) {
		i++;
	}
	return i;
}

void insert_books(char name[],Books arr[], int arr_size) {
	strcpy(arr[arr_size].name, name);
	arr[arr_size].count = 1;
	arr[arr_size].used = 1;
}

int main() {
	int input_number;
	scanf("%d", &input_number);

	Books* books = (Books*)malloc(sizeof(Books) * input_number);
	for (int i = 0; i < input_number; i++) {
		books[i].count = 0;
		books[i].used = 0;
	}
	int arr_size;
	for (int i = 0; i < input_number; i++) {
		char name[51];
		arr_size = is_arr_size(books, input_number);
		scanf("%s", name);
		if (arr_size == 0) {
			insert_books(name, books, 0);
			continue;
		}
		int index = same_name(books, arr_size, name);
		if (index == -1) {
			insert_books(name, books, arr_size);
			continue;
		}
		else {
			books[index].count++;
		}
		
	}
	arr_size = is_arr_size(books, input_number);
	heapsort(books, arr_size, 1);
	printf("%s", books[0].name);
}