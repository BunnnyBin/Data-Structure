#define MAX_STACK_SIZE 100
#define True 1
#define False 0
#define Error -1
#include <stdio.h>

typedef int Bool;
typedef int Element;
typedef struct {
	Element stackArr[MAX_STACK_SIZE][3];  //현재 위치하는 x좌표,y좌표,뚫려있는 방향(direction)
	int top;
}Stack;
//스택생성
Stack* Create(void) {
	Stack * tempstack;
	tempstack = malloc(sizeof(Stack));
	tempstack->top = -1;  //스택 초기화
	return tempstack;
}
//스택이 비어있는지 검사
Bool isEmpty(Stack* pstack) {
	if (pstack->top == -1)
		return True;
	else
		return False;
}
//스택이 찼는지 검사
Bool isFull(Stack* pstack) {
	if (pstack->top == MAX_STACK_SIZE - 1)
		return True;
	else
		return False;
}
//스택에 집어넣기
void Push(Stack* pstack,Element x,Element y,Element d) {
	if (!isFull(pstack)) {
		pstack->stackArr[++pstack->top][0] = x;
		pstack->stackArr[pstack->top][1] = y;
		pstack->stackArr[pstack->top][2] = d;
	}
	else {
		printf("스택이 다 찼다!\n");
		exit(-1); //프로그램 종료
	}
}
//스택에서 끄집어내고 삭제하기
int* Pop(Stack* pstack) {
	if (!isEmpty(pstack)) 
		return pstack->stackArr[pstack->top--]; //일차원 배열 출력(일차원 포인터와 호환)
	else {
		printf("스택이 비어있다!\n");
		return Error;  //main함수에 오류 알린다.
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
						{7,10,6,10,6,10,7,3,10} }; //막힌 부분 더하기: 위(1),오른쪽(8),왼쪽(4),아래(2)
	int move[12][9];  //한번 지나간 길은 막힌것으로 표시하기 위해
	int x = 0, y = 0, d;   //현재 x(세로),y(가로),뚫려있는 방향(가려는 방향)
	int *m, *arr;  //스택s에서 끄집어낸 갈림길, 스택r을 보조한다
	Stack * s, *r;   //갈림길 저장 스택, 움직인 경로 저장 스택
	int i, j, a;

	for (i = 0;i < 12;i++)
		for (j = 0;j < 9;j++)
			move[i][j] = mazz[i][j]; //배열move == 배열mazz
	s = Create(); //구조체 생성
	r = Create();

	Push(r, 0, 0, 0); //첫 시작(0,0)를 최종 경로에 저장

	while (x != 11 || y != 8) { //<-> x==11 && y==8 (도착)
		//1. 갈림길에 놓인다면
		if (move[x][y] == 5) { 
			printf("PUSH(%d, %d, 8)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 8); //오른쪽 방향
			Push(s, x, y, 2); //아래 방향

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		else if (move[x][y] == 9) {
			printf("PUSH(%d, %d, 4)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 4); //왼쪽 방향
			Push(s, x, y, 2); //아래 방향

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		else if (move[x][y] == 3) {
			printf("PUSH(%d, %d, 4)\n", x, y);
			printf("PUSH(%d, %d, 8)\n", x, y);
			Push(s, x, y, 4); //왼쪽 방향
			Push(s, x, y, 8); //오른쪽 방향

			printf("Pop(%d, %d, 8)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		else if (move[x][y] == 6) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 8)\n", x, y);
			Push(s, x, y, 1); //위쪽 방향
			Push(s, x, y, 8); //오른쪽 방향

			printf("Pop(%d, %d, 8)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		else if (move[x][y] == 10) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 4)\n", x, y);
			Push(s, x, y, 1); //위쪽 방향
			Push(s, x, y, 4); //왼쪽 방향

			printf("Pop(%d, %d, 4)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		else if (move[x][y] == 12) {
			printf("PUSH(%d, %d, 1)\n", x, y);
			printf("PUSH(%d, %d, 2)\n", x, y);
			Push(s, x, y, 1); //왼쪽 방향
			Push(s, x, y, 2); //아래 방향

			printf("Pop(%d, %d, 2)\n", x, y);
			m = Pop(s); //갈림길 중 방향 선택
			d = m[2]; //가려는 방향
		}
		//2. 한 쪽으로만 갈 수 있는 길(즉, 갈림길x)
		else if (move[x][y] == 7)
			d = 8;
		else if (move[x][y] == 13)
			d = 2;
		else if (move[x][y] == 11)
			d = 4;
		else if (move[x][y] == 14)
			d = 1;
		//3. 미로가 막히면/잘못된 길이면
		else if (move[x][y] == 15) {
			m = Pop(s);
			x = m[0];
			y = m[1];
			d = m[2]; //다시 갈림길로 돌아가기

			arr = Pop(r); //현재위치가 갈림길로 돌아갈 때 까지 반복
			while (arr[0] != x || arr[1] != y)  //<-> arr[0] == x && arr[1] == y
				arr = Pop(r); //실제로 갈림길로 돌아가기

			Push(r, x, y, 0); //갈림길 위치를 최종경로에 저장

			printf("POP(%d, %d, %d)\n", x, y, d);
		}
		//4. 이미 간 길을 봉쇄하고 실제로 이동하기
		if (d == 8)
			move[x][++y] += 4;
		else if (d == 2)
			move[++x][y] += 1;
		else if (d == 4)
			move[x][--y] += 8;
		else if (d == 1)
			move[--x][y] += 2;

		Push(r, x, y, 0);  //경로상 움직이는 x(세로), y(가로) 저장
	}
	printf("길 찾음\n\n\n");

	for (i = 0;i < 12;i++) {
		printf("+");
		for (j = 0;j < 9;j++) {
			if (mazz[i][j] == 1 || mazz[i][j] == 5 || mazz[i][j] == 9 || mazz[i][j] == 3 || mazz[i][j] == 7 || mazz[i][j] == 11 || mazz[i][j] == 13 || mazz[i][j] == 15)
				printf("----+");
			else
				printf("    +");
		}//가로줄 미로 표시
		printf("\n|");
		for (j = 0;j < 9;j++) { //세로줄은 한 칸의 오른쪽 세로줄만 표시하면 됨(이전 칸에서 알아서 왼쪽 세로줄을 채우기 때문)
			if (mazz[i][j] == 8 || mazz[i][j] == 9 || mazz[i][j] == 10 || mazz[i][j] == 12 || mazz[i][j] == 11 || mazz[i][j] == 13 || mazz[i][j] == 14 || mazz[i][j] == 15) { //"| ○ |"인 경우
				for (a = 0;a <= r->top;a++) //지나간 길이면 ○표시
					if (r->stackArr[a][0] == i && r->stackArr[a][1] == j) { //스택r에서 지나간 경로 검사
						printf(" ○ |");
						break;
					}
				if (a == r->top + 1)
					printf("    |"); //지나간 길이 아니면 빈칸
			}
			else { //세로줄이 없는 경우
				for (a = 0;a <= r->top;a++) //지나간 길이면 ○표시
					if (r->stackArr[a][0] == i && r->stackArr[a][1] == j) { //스택r에서 지나간 경로 검사
						printf(" ○  ");
						break;
					}
				if (a == r->top + 1)
					printf("     "); //지나간 길이 아니면 빈칸
			}
		}//세로줄 미로 표시
		printf(" %d\n",i);
	}
	printf("+----+----+----+----+----+----+----+----+----+\n");
	printf("   0    1    2    3    4    5    6    7   8\n");
	printf("20170299_김유빈\n");

	free(s);
	free(r);
}