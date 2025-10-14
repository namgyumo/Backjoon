#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    long long* ps = (long long*)malloc(sizeof(long long) * (N + 1));
    ps[0] = 0;

    for (int i = 1; i <= N; i++) {
        long long x;
        scanf("%lld", &x);
        ps[i] = ps[i - 1] + x;
    }

    for (int q = 0; q < M; q++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%lld\n", ps[r] - ps[l - 1]);
    }

    free(ps);
    return 0;
}
