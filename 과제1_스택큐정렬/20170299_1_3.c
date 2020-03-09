#define MAX_STACK_SIZE 50
#define True 1
#define False 0
#define Error -1
#include <stdio.h>

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
//���ÿ��� ������ �ʰ� �������
Element Peek(Stack*pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top];
	else {
		printf("������ ����ִ�!\n");
		return Error;  //main�Լ��� ���� �˸���.
	}
}

int main() {
	char user[10]; //����ڰ� �Է��ϴ� ������ ���� ����
	int start[9];  //ó�� ������ ���� ����
	Stack * s1,* s2;   //����1, ����2
	int least1, least2; //����1,2���� �ּڰ�
	int index1, index2;   //����1,2���� �ּڰ��� ��ġ
	int count = 1,result = 1; //���� Ƚ��, �ش� ��� ����
	int i,j;

	printf("���� ��ȣ �Է� : ");
	gets(user);
	for (i = 0;i < 9;i++)
		start[i] = user[i] - '0'; //�Է��� ���� ������ �������·� ����

	s1 = Create();
	s2 = Create(); //���� ����

	i = 0;
	while (result < 10) { //������ ���� 9�� ����� �� ������
		//least1, least2 �ʱ�ȭ
		if (isEmpty(s1))  //������ ����ִٸ�
			least1 = 10; //ó������ �ʱ�ȭ(������ ����ִٴ� ��)
		else {  //���ÿ� ���Ұ� �ִٸ�
			if (s1->top == 0) {  //���ÿ� 1���� ���Ҹ� ���� ��(�� �ʿ�x)
				least1 = s1->stackArr[s1->top]; index1 = s1->top;
			}
			for (j = s1->top;j > 0 && (j - 1) >= 0;j--)  //���� ���Ұ� 2�� �̻��� ��, 1������ 0������ �񱳰� ������ ��
				if (s1->stackArr[j] <= s1->stackArr[j - 1]) {
					least1 = s1->stackArr[j]; index1 = j;
				}
				else {
					least1 = s1->stackArr[j - 1]; index1 = j - 1;
				}
		}
		if (isEmpty(s2)) 
			least2 = 10; 
		else {  
			if (s2->top == 0) {
				least2 = s2->stackArr[s2->top]; index2 = s2->top;
			}

			for (j = s2->top;j > 0 && (j - 1) >= 0;j--) 
				if (s2->stackArr[j] <= s2->stackArr[j - 1]) {
					least2 = s2->stackArr[j]; index2 = j;
				}
				else {
					least2 = s2->stackArr[j - 1]; index2 = j-1;
				}
		}

		//1. IN�� ���ڰ� �ٷ� �ش� ������ ��
		if (i <= 8 && start[i] == result) {
			printf("%2d : IN(%d)\n", count++, start[i]);
			printf("%2d : OUT(%d)\n", count++, start[i]);
			result++; //�ٷ� OUT
			i++; //�Է��� ���� ���� ����(IN)
		}
		//2. ����1�� �ش� ���ڰ� ���� ��
		else if (least1 == result) {
			if (s1->stackArr[s1->top] == least1) { //���� ����1�� top�� �־����� 
				printf("%2d : POP(1)\n", count++);
				printf("%2d : OUT(%d)\n", count++, Pop(s1));
				result++; //POP �ٷ� OUT!
			}
			else {  //�׷����ʰ� ����1 �߰��� ������
				for (j = s1->top;j > index1;j--) {  //����1�� �ش� ���� ���� �ִ� ���������� POP -> PUSH(����2��)
					printf("%2d : POP(1)\n", count++);
					printf("%2d : PUSH(2,%d)\n", count++, s1->stackArr[j]);
					Push(s2, Pop(s1));
				}
				printf("%2d : POP(1)\n", count++);
				printf("%2d : OUT(%d)\n", count++, Pop(s1));
				result++; //����1�� top�� �ִ� ���ڸ� POP -> OUT
			}
		}
		//3. ����2�� �ش� ���ڰ� ���� ��
		else if (least2 == result) {
			if (s2->stackArr[s2->top] == least2) { //���� ����2�� top�� �־����� 
				printf("%2d : POP(2)\n", count++);
				printf("%2d : OUT(%d)\n", count++, Pop(s2));
				result++; //POP �ٷ� OUT!
			}
			else {  //�׷����ʰ� ����2 �߰��� ������
				for (j = s2->top;j > index2;j--) { //����2���� �ش� ���� ���� �ִ� ���ڵ��� ����1�� POP -> PUSH
					printf("%2d : POP(2)\n", count++);
					printf("%2d : PUSH(1,%d)\n", count++, s2->stackArr[j]);
					Push(s1, Pop(s2));
				}
				printf("%2d : POP(2)\n", count++);
				printf("%2d : OUT(%d)\n", count++, Pop(s2));
				result++; //����2�� top�� �ִ� ���ڸ� POP -> OUT
			}
		}
		//4. ���� �ش� ���ڰ� �� ������ �� PUSH!(OUT����)
		else if(i <= 8){
			printf("%2d : IN(%d)\n", count++, start[i]); //IN()�Լ�
			
			if (isEmpty(s1)) { //����1�� ������� ��
				printf("%2d : PUSH(1, %d)\n", count++, start[i]);
				Push(s1, start[i]);
				least1 = start[i];
			}
			else if (isEmpty(s2)) { //����2�� ������� ��
				printf("%2d : PUSH(2, %d)\n", count++, start[i]);
				Push(s2, start[i]);
				least2 = start[i];
			}
			else if (!isEmpty(s1) && least1 < start[i]) { //����1�� �� ��� �ִµ� �ּڰ����� IN�� �� ũ��
				printf("%2d : PUSH(2, %d)\n", count++, start[i]);
				Push(s2, start[i]);
			}
			else if (!isEmpty(s1) && least1 > start[i]) { //����1�� �� ��� �ִµ� IN�� �ּڰ��̸�
				printf("%2d : PUSH(1, %d)\n", count++, start[i]);
				Push(s1, start[i]);
				least1 = start[i];
			}
			i++;  //�Է��� ���� ���� ����(IN)
		}
	}
	printf("����(�� %dȸ)\n", --count);
	printf("20170299_������\n");
}