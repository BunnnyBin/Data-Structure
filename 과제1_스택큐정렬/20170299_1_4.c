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
//큐 생성 함수
QueueType * create() {
	QueueType * tempqueue; //구조체의 포인터(임시)

	tempqueue = malloc(sizeof(QueueType));
	tempqueue->front = 0;
	tempqueue->rear = 0;
	return tempqueue;
}
//공백 상태 검출 함수
int is_empty(QueueType * q) {
	return(q->front == q->rear);
}
//포화 상태 검출 함수
int is_full(QueueType * q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//삽입 함수
int enqueue(QueueType * q, Element item) {
	if (is_full(q))
		return Error; //더이상 데이터 넣지 않음
	else{
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
		return Success;
	}
}
//삭제 함수
Element dequeue(QueueType * q) {
	if (is_empty(q))
		return Error;
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->queue[q->front];
	}
}

void main() {
	char user[25];//사용자에게 입력받는 문자열
	QueueType * q;
	int count = 0; //큐의 데이터 갯수
	int num;
	int i;

	q = create(); //큐 생성
	printf(">>> ");
	gets(user);

	while (strcmp(user, "STOP") != 0) {
		//1. 큐에 집어넣기
		if (user[0] >= 'A') { //즉, 사용자 입력 문자열이 '문자'인 경우
			for (i = 0;i < strlen(user);i++) {
				printf("ADDQUEUE(%c) ", user[i]);
				enqueue(q, user[i]);  //큐에 집어 넣기
				if (count >= 20) //큐가 가득 차있다면 FAIL
					printf("Fail : Queue Full     Queue Size=20/20\n");
				else 
					printf("    Queue Size=%d/20\n", ++count); //아니면 데이터 갯수 증가
			}
		}
		//2. 큐에서 끄집어내기
		else if (user[0] >= '0' && user[0] <= '9') { //즉, 사용자 입력 문자열이 '숫자'인 경우
			if (user[1] >= '0' && user[1] <= '9')
				num = (user[0] - '0') * 10 + user[1] - '0'; //입력한 숫자가 10이상인 경우
			else
				num = user[0] - '0'; //입력한 숫자가 일의 자리인 경우
			for (i = 0;i < num;i++) {
				printf("DELETEQUEUE( ) = %c, Queue Size=%d/20\n",dequeue(q),--count); //데이터 끄집어내고 데이터 갯수 감소
			}
		}
		printf(">>> ");
		gets(user);
	}
}


