#include<stdio.h>
#include<math.h>

int solve(int x1, int y1, int r1, int x2, int y2, int r2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    long long d2 = dx * dx + dy * dy;      // 거리 제곱
    long long r_sum = r1 + r2; //반지름 합
    long long r_diff = abs(r1 - r2); // 반지름 차

    if (d2 == 0 && r1 == r2) return -1;     // 무한대 (동심, 반지름 같음)
    else if (d2 > r_sum * r_sum) return 0;    // 멀리 떨어져 있음
    else if (d2 < r_diff * r_diff) return 0;  // 한 원이 다른 원 안에 있음
    else if (d2 == r_sum * r_sum) return 1;   // 외접
    else if (d2 == r_diff * r_diff) return 1; // 내접
    else return 2;                          // 두 점에서 만남
}

int main() {
	int x1, y1; // 조규현 위치
	int x2, y2; // 백승환 위치
	int r1, r2; // 류재명 거리
	int number;
    scanf_s("%d", &number);
	for (int i = 0; i < number; i++) {
		scanf_s("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        printf("%d\n",solve(x1, y1, r1, x2, y2, r2));
	}
}