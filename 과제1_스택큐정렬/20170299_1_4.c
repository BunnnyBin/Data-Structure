#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 20 
#define Success 1
#define Error -1
#define Element int
#include <stdio.h>
#include <string.h>

typedef struct {
	int queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;
//ť ���� �Լ�
QueueType * create() {
	QueueType * tempqueue; //����ü�� ������(�ӽ�)

	tempqueue = malloc(sizeof(QueueType));
	tempqueue->front = 0;
	tempqueue->rear = 0;
	return tempqueue;
}
//���� ���� ���� �Լ�
int is_empty(QueueType * q) {
	return(q->front == q->rear);
}
//��ȭ ���� ���� �Լ�
int is_full(QueueType * q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//���� �Լ�
int enqueue(QueueType * q, Element item) {
	if (is_full(q))
		return Error; //���̻� ������ ���� ����
	else{
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
		return Success;
	}
}
//���� �Լ�
Element dequeue(QueueType * q) {
	if (is_empty(q))
		return Error;
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->queue[q->front];
	}
}

void main() {
	char user[25];//����ڿ��� �Է¹޴� ���ڿ�
	QueueType * q;
	int count = 0; //ť�� ������ ����
	int num;
	int i;

	q = create(); //ť ����
	printf(">>> ");
	gets(user);

	while (strcmp(user, "STOP") != 0) {
		//1. ť�� ����ֱ�
		if (user[0] >= 'A') { //��, ����� �Է� ���ڿ��� '����'�� ���
			for (i = 0;i < strlen(user);i++) {
				printf("ADDQUEUE(%c) ", user[i]);
				enqueue(q, user[i]);  //ť�� ���� �ֱ�
				if (count >= 20) //ť�� ���� ���ִٸ� FAIL
					printf("Fail : Queue Full     Queue Size=20/20\n");
				else 
					printf("    Queue Size=%d/20\n", ++count); //�ƴϸ� ������ ���� ����
			}
		}
		//2. ť���� �������
		else if (user[0] >= '0' && user[0] <= '9') { //��, ����� �Է� ���ڿ��� '����'�� ���
			if (user[1] >= '0' && user[1] <= '9')
				num = (user[0] - '0') * 10 + user[1] - '0'; //�Է��� ���ڰ� 10�̻��� ���
			else
				num = user[0] - '0'; //�Է��� ���ڰ� ���� �ڸ��� ���
			for (i = 0;i < num;i++) {
				printf("DELETEQUEUE( ) = %c, Queue Size=%d/20\n",dequeue(q),--count); //������ ������� ������ ���� ����
			}
		}
		printf(">>> ");
		gets(user);
	}
}


