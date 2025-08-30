#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Grade {
    char name[11];
    int korean;
    int english;
    int math;
} Grade;

int isHigher(Grade a, Grade b) {
    if (a.korean != b.korean)
        return a.korean < b.korean; 
    if (a.english != b.english)
        return a.english > b.english; 
    if (a.math != b.math) {
        return a.math < b.math;
    }
    return strcmp(a.name, b.name) < 0;
}

void heapify(Grade arr[], int n, int i) { //make full heap
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && isHigher(arr[left], arr[largest]))
        largest = left;
    if (right < n&& isHigher(arr[right], arr[largest]))
        largest = right;

    if (largest != i) {
        Grade temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapsort(Grade arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        Grade temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int input_number;
    scanf("%d", &input_number);


    Grade* students = (Grade*)malloc(sizeof(Grade) * input_number);

    for (int i = 0; i < input_number; i++) {
        scanf("%s %d %d %d", students[i].name,
            &students[i].korean,
            &students[i].english,
            &students[i].math);
    }

    heapsort(students, input_number);

    for (int i = 0; i < input_number; i++) {
        printf("%s\n", students[i].name);
    }

    free(students);
    return 0;
}
