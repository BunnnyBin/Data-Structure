#define MAX_STACK_SIZE 100
#define True 1
#define False 0
#define Error -1
#include <stdio.h>
#include <string.h>

typedef int Bool;
typedef int Element;
typedef struct {
	Element stackArr[MAX_STACK_SIZE];
	int top;
}Stack;
//스택 생성
Stack* Create(void) { 
	Stack* tempstack; //구조체의 포인터
	tempstack = malloc(sizeof(Stack)); //스택을 동적할당
	tempstack->top = -1; //스택 초기화(top = -1)
	return tempstack;
}
//스택이 비어있는지 검사
Bool isEmpty(Stack* pstack) { 
	if (pstack->top == -1)
		return True;
	else
		return False;
}
//스택이 다 찼는지 검사
Bool isFull(Stack* pstack) {  
	if (pstack->top == MAX_STACK_SIZE - 1)
		return True;
	else
		return False;
}
//스택에 집어넣기
void Push(Stack*pstack, Element Data) {
	if (!isFull(pstack))
		pstack->stackArr[++pstack->top] = Data;
	else{
		printf("스택이 다 찼다!\n");
		exit(-1); //프로그램 종료
	}
}
//스택에서 끄집어내고 없애기
Element Pop(Stack*pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top--];
	else {
		printf("스택이 비어있다!\n");
		return Error;  //main함수에 오류 알린다.
	}
}
//스택에서 없애지 않고 끄집어내기
Element Peek(Stack*pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top];
	else {
		printf("스택이 비어있다!\n");
		return Error;  //main함수에 오류 알린다.
	}
}

//연산자 우선순위를 숫자로 반환(숫자값이 낮을 수록 우선순위가 높음)
int operator_value(char ch) {  
	switch (ch) {
	case '+': case '-': 
		return 4; break;
	case '*': case '/':
		return 3; break;
	case '%':
		return 2; break;
	case '!':
		return 1; break; //연산자** -> !
	}
	return Error;  //수식어 오류
}

/*후위 표기법으로 계산하기
int evaluation(char arr[]) {
	int op1, op2, value;
	int i;
	char ch;
	Stack * s;

	s = Crearte();

	for (i = 0;i < strlen(arr);i++) {
		ch = arr[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '!') {  //입력이 피연산자일 때
			if(arr[i] == '1' && arr[i] == '0' && arr[i] == '1')
			if ((arr[i + 1] >= '0' && arr[i + 1] <= '9')&&(arr[i + 2] >= '0' && arr[i + 2] <= '9'))
		}
}*/

int main() {
	Stack* pstack;
	char user[50],eval[50] = ""; //사용자 입력 수식, 후위 표기법 수식을 저장한다.
	char ch, e; //수식 하나하나를 비교한다, 스택에서 끄집어낸 문자
	char open_ch;  //여는 괄호
	int answer;    //계산 결과값
	int i;

	pstack = Create();
	printf("수식을 입력하시오>> ");
	gets(user);
	
	//<괄호 검사>-------------------------------------------
	for (i = 0;i<strlen(user);i++) {
		ch = user[i];

		switch (ch) {
		case '(':
		case '{':
		case '[':
			Push(pstack, ch);
			break;
		case ')':
		case '}':
		case ']':
			if (isEmpty(pstack)) {
				//printf("%s이 위치에 오류가 있습니다. %c가 부족합니다.\n");
				return Error;   //스택이 비었다. 즉, 여는 괄호의 갯수 부족
			}
			else {
				open_ch = Pop(pstack);
				if ((open_ch == '(' && ch == ')') || (open_ch == '{' && ch == '}') || (open_ch == '[' && ch == ']'))
					;
				else {
					//printf("%s이 위치에 오류가 있습니다. %c가 부족합니다.\n");
					return Error;  //여는 괄호'('와 닫는 괄호가 서로 짝이 아니다.
				}
			}
			break;
		}
	}
	if (!isEmpty(pstack)) {
		//printf("%s이 위치에 오류가 있습니다. %c가 부족합니다.\n");
		return Error;
	}

	pstack->top = -1; //스택 초기화

	//<Postfix 구현>-----------------------------------------
	for (i = 0;i<strlen(user);i++) {
		ch = user[i];
		if (user[i] == '*' && user[i + 1] == '*') {
			ch = '!'; //연산자** -> 연산자!
			i++; //'**'다음으로 넘어간다.
		}
		switch (ch) {
		case '+': case '-': case '*': case '/': case '%': case '!':  //연산자인 경우
			if (operator_value(Peek(pstack)) <= operator_value(ch)) //스택의 연산자가 집어넣으려는 연산자보다 우선순위가 빠를 때
				strcat(eval, Pop(pstack)); //스택 연산자를 후위 표기법 수식으로 끄집어낸다(출력).
			Push(pstack, ch);
			break;
		case '(': case '{': case '[':  //왼쪽 괄호인 경우
			Push(pstack, ch);
			break;

		case ')': case '}': case ']':  //오른쪽 괄호인 경우
			strcat(eval, Pop(pstack)); //스택 연산자를 후위 표기법 수식으로 끄집어낸다(출력).
			e = Pop(pstack);
			while (e != '(' && e != '{' && e != '[') {  //스택에서 왼쪽 괄호가 나오지 않을 때까지
				strcat(eval, e);  //후위 표기법 수식으로 끄집어낸다.
				e = Pop(pstack);
			}
			break;
		default: //피연산자인 경우!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			strcat(eval, Pop(pstack)); 
			break;
		}
	}
	while(!isEmpty(pstack))
		strcat(eval, Pop(pstack));  //스택에 나머지들을 출력한다.
	
	answer = evaluation(eval);
	printf("=%d\n", answer);
}
