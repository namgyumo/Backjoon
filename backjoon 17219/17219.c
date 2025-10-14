#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Site {
    char adress[21];
    char password[21];
} Site;

int cmp_str(const char* a, const char* b) {
    return strcmp(a, b);
}

void Heapify(Site* site, int n, int i) {
    int largest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    if (left < n && cmp_str(site[left].adress, site[largest].adress) > 0)
        largest = left;
    if (right < n && cmp_str(site[right].adress, site[largest].adress) > 0)
        largest = right;

    if (largest != i) {
        Site temp = site[i];
        site[i] = site[largest];
        site[largest] = temp;
        Heapify(site, n, largest);
    }
}

void HeapSort(Site* site, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(site, n, i);

    for (int i = n - 1; i > 0; i--) {
        Site temp = site[0];
        site[0] = site[i];
        site[i] = temp;
        Heapify(site, i, 0);
    }
}

int BinarySearch(Site* site, int n, const char* key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int c = cmp_str(site[mid].adress, key);
        if (c == 0) return mid;
        else if (c < 0) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    int input_adress, input_password;
    scanf("%d %d", &input_adress, &input_password);

    Site* sites = (Site*)malloc(sizeof(Site) * input_adress);

    for (int i = 0; i < input_adress; i++) {
        scanf("%20s %20s", sites[i].adress, sites[i].password);
    }

    HeapSort(sites, input_adress);

    for (int i = 0; i < input_password; i++) {
        char find[21];
        scanf("%20s", find);
        int idx = BinarySearch(sites, input_adress, find);
        if (idx >= 0) printf("%s\n", sites[idx].password);
        else printf("Not find\n");
    }

    free(sites);
    return 0;
}
