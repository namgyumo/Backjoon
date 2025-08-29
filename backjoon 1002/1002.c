#include<stdio.h>
#include<math.h>

int solve(int x1, int y1, int r1, int x2, int y2, int r2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    long long d2 = dx * dx + dy * dy;      // �Ÿ� ����
    long long r_sum = r1 + r2; //������ ��
    long long r_diff = abs(r1 - r2); // ������ ��

    if (d2 == 0 && r1 == r2) return -1;     // ���Ѵ� (����, ������ ����)
    else if (d2 > r_sum * r_sum) return 0;    // �ָ� ������ ����
    else if (d2 < r_diff * r_diff) return 0;  // �� ���� �ٸ� �� �ȿ� ����
    else if (d2 == r_sum * r_sum) return 1;   // ����
    else if (d2 == r_diff * r_diff) return 1; // ����
    else return 2;                          // �� ������ ����
}

int main() {
	int x1, y1; // ������ ��ġ
	int x2, y2; // ���ȯ ��ġ
	int r1, r2; // ����� �Ÿ�
	int number;
    scanf_s("%d", &number);
	for (int i = 0; i < number; i++) {
		scanf_s("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        printf("%d\n",solve(x1, y1, r1, x2, y2, r2));
	}
}