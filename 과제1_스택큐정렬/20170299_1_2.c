#define MAX_STACK_SIZE 100
#define True 1
#define False 0
#define Error -1
#include <stdio.h>

typedef int Bool;
typedef int Element;
typedef struct {
	Element stackArr[MAX_STACK_SIZE][3];  //���� ��ġ�ϴ� x��ǥ,y��ǥ,�շ��ִ� ����(direction)
	int top;
}Stack;
//���û���
Stack* Create(void) {
	Stack * tempstack;
	tempstack = malloc(sizeof(Stack));
	tempstack->top = -1;  //���� �ʱ�ȭ
	return tempstack;
}
//������ ����ִ��� �˻�
Bool isEmpty(Stack* pstack) {
	if (pstack->top == -1)
		return True;
	else
		return False;
}
//������ á���� �˻�
Bool isFull(Stack* pstack) {
	if (pstack->top == MAX_STACK_SIZE - 1)
		return True;
	else
		return False;
}
//���ÿ� ����ֱ�
void Push(Stack* pstack,Element x,Element y,Element d) {
	if (!isFull(pstack)) {
		pstack->stackArr[++pstack->top][0] = x;
		pstack->stackArr[pstack->top][1] = y;
		pstack->stackArr[pstack->top][2] = d;
	}
	else {
		printf("������ �� á��!\n");
		exit(-1); //���α׷� ����
	}
}
//���ÿ��� ������� �����ϱ�
int* Pop(Stack* pstack) {
	if (!isEmpty(pstack)) 
		return pstack->stackArr[pstack->top--]; //������ �迭 ���(������ �����Ϳ� ȣȯ)
	else {
		printf("������ ����ִ�!\n");
		return Error;  //main�Լ��� ���� �˸���.
	}
}

int main() {
	int mazz[12][9] = { {5,3,3,9,7,3,1,9,13},
						{6,3,9,12,5,3,8,12,12},
						{5,3,8,6,10,5,10,12,12},
						{12,13,14,13,13,14,5,10,12},
						{12,12,5,8,6,3,10,5,10},
						{4,10,12,4,3,3,3,10,13},
						{6,3,10,12,5,3,11,5,8},
						{13,5,3,10,12,5,3,10,14},
						{12,6,3,1,10,6,1,3,9},
						{4,3,9,4,9,5,10,13,12},
						{6,9,12,12,12,4,3,10,12},
						{7,10,6,10,6,10,7,3,10} }; //���� �κ� ���ϱ�: ��(1),������(8),����(4),�Ʒ�(2)
	int move[12][9];  //�ѹ� ������ ���� ���������� ǥ���ϱ� ����
	int x = 0, y = 0, d;   //���� x(����),y(����),�շ��ִ� ����(������ ����)
	int *m, *arr;  //����s���� ����� ������, ����r�� �����Ѵ�
	Stack * s, *r;   //������ ���� ����, ������ ��� ���� ����
	int i, j, a;

	for (i = 0;i < 12;i++)
		for (j = 0;j < 9;j++)
			move[i][j] = mazz[i][j]; //�迭move == �迭mazz
	s = Create(); //����ü ����
	r = Create();

	Push(r, 0, 0, 0); //ù ����(0,0)�� ���� ��ο� ����

	while (x != 11 || y != 8) { //<-> x==11 && y==8 (����)
		//1. �����濡 ���δٸ�
		if (move[x][y] == 5) { 
			printf("PUSH(%d, %d, 8)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 8); //������ ����
			Push(s, x, y, 2); //�Ʒ� ����

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		else if (move[x][y] == 9) {
			printf("PUSH(%d, %d, 4)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 4); //���� ����
			Push(s, x, y, 2); //�Ʒ� ����

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		else if (move[x][y] == 3) {
			printf("PUSH(%d, %d, 4)\n", x, y);
			printf("PUSH(%d, %d, 8)\n", x, y);
			Push(s, x, y, 4); //���� ����
			Push(s, x, y, 8); //������ ����

			printf("Pop(%d, %d, 8)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		else if (move[x][y] == 6) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 8)\n", x, y);
			Push(s, x, y, 1); //���� ����
			Push(s, x, y, 8); //������ ����

			printf("Pop(%d, %d, 8)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		else if (move[x][y] == 10) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 4)\n", x, y);
			Push(s, x, y, 1); //���� ����
			Push(s, x, y, 4); //���� ����

			printf("Pop(%d, %d, 4)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		else if (move[x][y] == 12) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 1); //���� ����
			Push(s, x, y, 2); //�Ʒ� ����

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //������ �� ���� ����
			d = m[2]; //������ ����
		}
		//2. �� �����θ� �� �� �ִ� ��(��, ������x)
		else if (move[x][y] == 7)
			d = 8;
		else if (move[x][y] == 13)
			d = 2;
		else if (move[x][y] == 11)
			d = 4;
		else if (move[x][y] == 14)
			d = 1;
		//3. �̷ΰ� ������/�߸��� ���̸�
		else if (move[x][y] == 15) {
			m = Pop(s);
			x = m[0];
			y = m[1];
			d = m[2]; //�ٽ� ������� ���ư���

			arr = Pop(r); //������ġ�� ������� ���ư� �� ���� �ݺ�
			while (arr[0] != x || arr[1] != y)  //<-> arr[0] == x && arr[1] == y
				arr = Pop(r); //������ ������� ���ư���

			Push(r, x, y, 0); //������ ��ġ�� ������ο� ����

			printf("POP(%d, %d, %d)\n", x, y, d);
		}
		//4. �̹� �� ���� �����ϰ� ������ �̵��ϱ�
		if (d == 8)
			move[x][++y] += 4;
		else if (d == 2)
			move[++x][y] += 1;
		else if (d == 4)
			move[x][--y] += 8;
		else if (d == 1)
			move[--x][y] += 2;

		Push(r, x, y, 0);  //��λ� �����̴� x(����), y(����) ����
	}
	printf("�� ã��\n\n\n");

	for (i = 0;i < 12;i++) {
		printf("+");
		for (j = 0;j < 9;j++) {
			if (mazz[i][j] == 1 || mazz[i][j] == 5 || mazz[i][j] == 9 || mazz[i][j] == 3 || mazz[i][j] == 7 || mazz[i][j] == 11 || mazz[i][j] == 13 || mazz[i][j] == 15)
				printf("----+");
			else
				printf("    +");
		}//������ �̷� ǥ��
		printf("\n|");
		for (j = 0;j < 9;j++) { //�������� �� ĭ�� ������ �����ٸ� ǥ���ϸ� ��(���� ĭ���� �˾Ƽ� ���� �������� ä��� ����)
			if (mazz[i][j] == 8 || mazz[i][j] == 9 || mazz[i][j] == 10 || mazz[i][j] == 12 || mazz[i][j] == 11 || mazz[i][j] == 13 || mazz[i][j] == 14 || mazz[i][j] == 15) { //"| �� |"�� ���
				for (a = 0;a <= r->top;a++) //������ ���̸� ��ǥ��
					if (r->stackArr[a][0] == i && r->stackArr[a][1] == j) { //����r���� ������ ��� �˻�
						printf(" �� |");
						break;
					}
				if (a == r->top + 1)
					printf("    |"); //������ ���� �ƴϸ� ��ĭ
			}
			else { //�������� ���� ���
				for (a = 0;a <= r->top;a++) //������ ���̸� ��ǥ��
					if (r->stackArr[a][0] == i && r->stackArr[a][1] == j) { //����r���� ������ ��� �˻�
						printf(" ��  ");
						break;
					}
				if (a == r->top + 1)
					printf("     "); //������ ���� �ƴϸ� ��ĭ
			}
		}//������ �̷� ǥ��
		printf(" %d\n",i);
	}
	printf("+----+----+----+----+----+----+----+----+----+\n");
	printf("   0    1    2    3    4    5    6    7   8\n");
	printf("20170299_������\n");

	free(s);
	free(r);
}