#include <stdio.h>
void hanoi(int n, char from, char by, char to) {
	static int count = 1;

	if (n == 1)
		printf("%3d : ����1�� %c���� %c�� �̵�\n", count++, from, to);
	else {
		hanoi(n - 1, from, to, by);  //n-1�� Ÿ���� �������� �̵�
		printf("%3d : ����%d�� %c���� %c�� �̵�\n", count++, n, from, to);  //������ n��° Ÿ���� �������� �̵�
		hanoi(n - 1, by, from, to);  //n-1�� Ÿ���� �������� �̵�
	}
}

int main() {
	hanoi(4, 'A', 'B', 'C');
}