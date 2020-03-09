#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_STACK_SIZE 50
#define True 1
#define False 0
#define Error -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int stdnum[9];
	char name[11];
	int phone[11];
}Student;

typedef int Bool;
typedef int Element;
typedef struct {
	Element stackArr[MAX_STACK_SIZE];
	int top;
}Stack;
//���� ����
Stack* Create(void) {
	Stack* tempstack; //����ü�� ������
	tempstack = malloc(sizeof(Stack)); //������ �����Ҵ�
	tempstack->top = -1; //���� �ʱ�ȭ(top = -1)
	return tempstack;
}
//������ ����ִ��� �˻�
Bool isEmpty(Stack* pstack) {
	if (pstack->top == -1)
		return True;
	else
		return False;
}
//������ �� á���� �˻�
Bool isFull(Stack* pstack) {
	if (pstack->top == MAX_STACK_SIZE - 1)
		return True;
	else
		return False;
}
//���ÿ� ����ֱ�
void Push(Stack*pstack, Element Data) {
	if (!isFull(pstack))
		pstack->stackArr[++pstack->top] = Data;
	else {
		printf("������ �� á��!\n");
		exit(-1); //���α׷� ����
	}
}
//���ÿ��� ������� ���ֱ�
Element Pop(Stack*pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top--];
	else {
		printf("������ ����ִ�!\n");
		return Error;  //main�Լ��� ���� �˸���.
	}
}

//���ȣ�� �� ����
int partition(Student * list[], int left, int right) {
	int pivot[9]; //�ǹ� ��
	Student * temp;
	int low, high;  //�ǹ� ���� ���� ���� �ε���, �ǹ����� ū ���� �ε���
	int i;

	low = left;
	high = right + 1;

	for (i = 0;i < 9;i++)
		pivot[i] = list[left]->stdnum[i]; //�ǹ��� �迭�� �� ó�� ��

	do {
		do {
			low++;
			for (i = 0;i < 9;i++) {  //low�� �ǹ��� ������ i++(���� ���ڷ� �̵�)
				if (list[low]->stdnum[i] < pivot[i])  //low�� �й��� �ǹ����� �� ���ڶ� ������
					break; //while������
				else if (list[low]->stdnum[i] > pivot[i]) //low�� �й� �� �� ���ڰ� �ǹ����� ũ��
					break;
			}
		} while (low < right && list[low]->stdnum[i] < pivot[i]); //low�� �迭�� �Ѿ�� �ʰ� ����
		do {
			high--;
			for (i = 0;i < 9;i++) {
				if (list[high]->stdnum[i] > pivot[i])
					break;
				else if (list[high]->stdnum[i] < pivot[i])
					break;
			}
		} while (high > left && list[high]->stdnum[i] > pivot[i]);

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp); //���� ������ ���� ������ ��ġ�� �ǹ��� ��ȯ!
	return high; //�ǹ� ��ġ ��ȯ
}
void quick_sort(Student * list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right); //���� -> �ǹ����� ū��, ���������� ����(�ǹ� ��ġ ��ȯ)
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//���� �� ����
int partition_stack(Student * list[], int left, int right) {
	int pivot[9];
	Student * temp;
	int low, high;
	int i;

	low = left;
	high = right + 1;

	for (i = 0;i < 9;i++)
		pivot[i] = list[left]->stdnum[i];

	do {
		do {
			low++;
			for (i = 0;i < 9;i++) {
				if (list[low]->stdnum[i] < pivot[i])
					break;
				else if (list[low]->stdnum[i] > pivot[i])
					break;
			}
		} while (low < right && list[low]->stdnum[i] < pivot[i]);
		do {
			high--;
			for (i = 0;i < 9;i++) {
				if (list[high]->stdnum[i] > pivot[i])
					break;
				else if (list[high]->stdnum[i] < pivot[i])
					break;
			}
		} while (high > left && list[high]->stdnum[i] > pivot[i]);

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp);
	return high;
}
void quick_sort_stack(Student * list[], int left, int right) {
	Stack * s;
	int q, l, r;
	s = Create();
	Push(s, left);
	Push(s, right);
	while (!isEmpty(s)) {
		r = Pop(s);
		l = Pop(s);
		if (0 <= l && l < r) {
			q = partition_stack(list, l, r);
			Push(s, l);
			Push(s, q - 1);
			Push(s, q + 1);
			Push(s, r);
		}
	}
}

int main() {
	Student * a[1000], *a2[1000]; //����ü�� ����Ű�� '�������� �迭'(�ϳ��� ��� �� ����, �ٸ� �ϳ��� ���� �� ����)
	char again; //�ߺ� �˻縦 �������� �ؾ��ϴ°�
	clock_t start, finish; //���Ŀ� �ҿ�Ǵ� �ð� ���
	double duration;
	int i, j, x, y;

	for (i = 0;i < 1000;i++) {
		a[i] = malloc(sizeof(Student));
		a2[i] = a[i];
	}
	srand(time(NULL));
	//1000���� ���� ������ ����
	for (i = 0;i < 1000;i++) {
		again = 1;
		while (again) {  //<�й�>
			a[i]->stdnum[0] = 2;
			a[i]->stdnum[1] = 0;
			a[i]->stdnum[2] = 1;
			a[i]->stdnum[3] = (rand() % 7) + 3;
			for (j = 4;j < 9;j++)
				a[i]->stdnum[j] = rand() % 10;

			again = 0;
			for (x = 0;x < i;x++) { //�ߺ� ������ �˻�
				for (y = 0;y < 9;y++) {
					if (a[x]->stdnum[y] != a[i]->stdnum[y])  //x��° ����ü���� �� ���ڶ� �ٸ���
						break; //y�ݺ��� ������
				}
				if (y == 10) { //x��° ����ü�� ���� ����ü�� ���ٸ�
					again = 1; //�ٽ� �й� ���ϱ�
					break; //x�ݺ����� ������
				} //���� �ٸ��ٸ� ���� ����ü �˻�
			}
		}//�й�
		again = 1;
		a[i]->name[10] = NULL; //���ڿ� �ʱ�ȭ
		while (again) {  //<�̸�>
			for (j = 0;j < 10;j++)
				a[i]->name[j] = (rand() % 26) + 65; //ascii code

			again = 0;
			for (x = 0;x < i;x++) { //'�ߺ� ������ �˻�'
				if (strcmp(a[x]->name, a[i]->name) == 0) { //x��° ����ü �й��� ������ ****
					again = 1; //�ٽ� �й� ���ϱ�
					break; //x�ݺ��� ������
				}
			}
		}//�̸�
		again = 1;
		while (again) {  //<��ȭ��ȣ>
			a[i]->phone[0] = 0;
			a[i]->phone[1] = 1;
			a[i]->phone[2] = 0;
			for (j = 3;j < 11;j++)
				a[i]->phone[j] = rand() % 10;

			again = 0;
			for (x = 0;x < i;x++) { //�ߺ� ������ �˻�
				for (y = 0;y < 11;y++) {
					if (a[x]->phone[y] != a[i]->phone[y])
						break;
				}
				if (y == 10) {
					again = 1;
					break;
				}
			}
		}//��ȭ��ȣ
	}//���� ������ ����

	printf("<��� ȣ�� �� ����>\n");
	start = clock();
	quick_sort(a, 0, 999);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("�й��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 0;i < 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", a[i]->stdnum[j]);
		printf(" ");
		printf("%s ", a[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", a[i]->phone[j]);
		printf("\n");
	}

	printf("\n<���� �� ����>\n");
	start = clock();
	quick_sort_stack(a2, 0, 999);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("�й��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 0;i < 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", a2[i]->stdnum[j]);
		printf(" ");
		printf("%s ", a2[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", a2[i]->phone[j]);
		printf("\n");
	}
}