#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int testcase;
    long long arr[101];
    arr[1] = arr[2] = arr[3] = 1;
    arr[4] = arr[5] = 2;
    scanf("%d", &testcase);
    for (int t = 0; t < testcase; t++) {
        int n;
        scanf("%d", &n);

        if (n <= 5) {
            printf("%lld\n", arr[n]);
            continue;
        }

        for (int i = 6; i <= n; i++) {
            arr[i] = arr[i - 1] + arr[i - 5];
        }

        printf("%lld\n", arr[n]);
    }
    return 0;
}

