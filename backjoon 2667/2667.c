#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Adjlist Adjlist;

struct Adjlist {
    Node* node;
    Adjlist* next;
};

struct Node {
    char data;
    int x, y;
    Adjlist* adj;
};

Node* MakeNode(char data, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->x = x;
    node->y = y;
    node->adj = NULL;
    return node;
}

void AddAdj(Node* from, Node* to) {
    Adjlist* adj = (Adjlist*)malloc(sizeof(Adjlist));
    adj->node = to;
    adj->next = from->adj;
    from->adj = adj;
}

void ConnectNode(Node* grid[25][25], int x, int y, int n) {
    Node* node = grid[x][y];
    if (!node || node->data != '1') return;

    if (x + 1 < n && grid[x + 1][y] && grid[x + 1][y]->data == '1') {
        AddAdj(node, grid[x + 1][y]);
        AddAdj(grid[x + 1][y], node);
    }
    if (y + 1 < n && grid[x][y + 1] && grid[x][y + 1]->data == '1') {
        AddAdj(node, grid[x][y + 1]);
        AddAdj(grid[x][y + 1], node);
    }
}

void Dfs(Node* node, int* count) {
    if (!node || node->data != '1') return;
    node->data = '0';
    (*count)++;
    for (Adjlist* adj = node->adj; adj; adj = adj->next)
        Dfs(adj->node, count);
}

void FreeGraph(Node* grid[25][25], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Node* node = grid[i][j];
            if (node) {
                Adjlist* adj = node->adj;
                while (adj) {
                    Adjlist* next = adj->next;
                    free(adj);
                    adj = next;
                }
                free(node);
            }
        }
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Node* grid[25][25] = { 0 };
    int size[25 * 25] = { 0 }, index = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            char data;
            scanf(" %c", &data);
            grid[i][j] = MakeNode(data, i, j);
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ConnectNode(grid, i, j, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j]->data == '1') {
                int count = 0;
                Dfs(grid[i][j], &count);
                size[index++] = count;
            }

    heapSort(size, index);

    printf("%d\n", index);
    for (int i = 0; i < index; i++)
        printf("%d\n", size[i]);

    FreeGraph(grid, n);
    return 0;
}

