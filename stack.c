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
	else{
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

//������ �켱������ ���ڷ� ��ȯ(���ڰ��� ���� ���� �켱������ ����)
int operator_value(char ch) {  
	switch (ch) {
	case '+': case '-': 
		return 4; break;
	case '*': case '/':
		return 3; break;
	case '%':
		return 2; break;
	case '!':
		return 1; break; //������** -> !
	}
	return Error;  //���ľ� ����
}

/*���� ǥ������� ����ϱ�
int evaluation(char arr[]) {
	int op1, op2, value;
	int i;
	char ch;
	Stack * s;

	s = Crearte();

	for (i = 0;i < strlen(arr);i++) {
		ch = arr[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '!') {  //�Է��� �ǿ������� ��
			if(arr[i] == '1' && arr[i] == '0' && arr[i] == '1')
			if ((arr[i + 1] >= '0' && arr[i + 1] <= '9')&&(arr[i + 2] >= '0' && arr[i + 2] <= '9'))
		}
}*/

int main() {
	Stack* pstack;
	char user[50],eval[50] = ""; //����� �Է� ����, ���� ǥ��� ������ �����Ѵ�.
	char ch, e; //���� �ϳ��ϳ��� ���Ѵ�, ���ÿ��� ����� ����
	char open_ch;  //���� ��ȣ
	int answer;    //��� �����
	int i;

	pstack = Create();
	printf("������ �Է��Ͻÿ�>> ");
	gets(user);
	
	//<��ȣ �˻�>-------------------------------------------
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
				//printf("%s�� ��ġ�� ������ �ֽ��ϴ�. %c�� �����մϴ�.\n");
				return Error;   //������ �����. ��, ���� ��ȣ�� ���� ����
			}
			else {
				open_ch = Pop(pstack);
				if ((open_ch == '(' && ch == ')') || (open_ch == '{' && ch == '}') || (open_ch == '[' && ch == ']'))
					;
				else {
					//printf("%s�� ��ġ�� ������ �ֽ��ϴ�. %c�� �����մϴ�.\n");
					return Error;  //���� ��ȣ'('�� �ݴ� ��ȣ�� ���� ¦�� �ƴϴ�.
				}
			}
			break;
		}
	}
	if (!isEmpty(pstack)) {
		//printf("%s�� ��ġ�� ������ �ֽ��ϴ�. %c�� �����մϴ�.\n");
		return Error;
	}

	pstack->top = -1; //���� �ʱ�ȭ

	//<Postfix ����>-----------------------------------------
	for (i = 0;i<strlen(user);i++) {
		ch = user[i];
		if (user[i] == '*' && user[i + 1] == '*') {
			ch = '!'; //������** -> ������!
			i++; //'**'�������� �Ѿ��.
		}
		switch (ch) {
		case '+': case '-': case '*': case '/': case '%': case '!':  //�������� ���
			if (operator_value(Peek(pstack)) <= operator_value(ch)) //������ �����ڰ� ����������� �����ں��� �켱������ ���� ��
				strcat(eval, Pop(pstack)); //���� �����ڸ� ���� ǥ��� �������� �������(���).
			Push(pstack, ch);
			break;
		case '(': case '{': case '[':  //���� ��ȣ�� ���
			Push(pstack, ch);
			break;

		case ')': case '}': case ']':  //������ ��ȣ�� ���
			strcat(eval, Pop(pstack)); //���� �����ڸ� ���� ǥ��� �������� �������(���).
			e = Pop(pstack);
			while (e != '(' && e != '{' && e != '[') {  //���ÿ��� ���� ��ȣ�� ������ ���� ������
				strcat(eval, e);  //���� ǥ��� �������� �������.
				e = Pop(pstack);
			}
			break;
		default: //�ǿ������� ���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			strcat(eval, Pop(pstack)); 
			break;
		}
	}
	while(!isEmpty(pstack))
		strcat(eval, Pop(pstack));  //���ÿ� ���������� ����Ѵ�.
	
	answer = evaluation(eval);
	printf("=%d\n", answer);
}
