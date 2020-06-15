#include <stdio.h>
void hanoi(int n, char from, char by, char to) {
	static int count = 1;

	if (n == 1)
		printf("%3d : 원반1를 %c에서 %c로 이동\n", count++, from, to);
	else {
		hanoi(n - 1, from, to, by);  //n-1개 타워를 경유지로 이동
		printf("%3d : 원반%d를 %c에서 %c로 이동\n", count++, n, from, to);  //마지막 n번째 타워를 목적지로 이동
		hanoi(n - 1, by, from, to);  //n-1개 타워를 목적지로 이동
	}
}

int main() {
	hanoi(4, 'A', 'B', 'C');
}