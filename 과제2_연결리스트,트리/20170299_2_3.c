#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 50000
#define MAX_STACK_SIZE 50
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key; //학번
	char name[11];
	char phone[12];
	struct TreeNode* left; //이진탐색트리를 링크로 구현
	struct TreeNode* right;
}TreeNode;

typedef TreeNode* Element;

typedef struct Stack {
	Element stackArr[MAX_STACK_SIZE];
	int top;
}Stack;
//스택 만들기 함수
Stack* Create(void) {
	Stack* tempstack = (Stack*)malloc(sizeof(Stack));
	tempstack->top = -1;
	return tempstack;
}
//스택이 비었는지 검사 함수
int isEmpty(Stack* pstack) {
	if (pstack->top == -1) return TRUE;
	else
		return FALSE;
}
//스택이 찼는지 검사 함수
int isFull(Stack* pstack) {
	if (pstack->top == MAX_STACK_SIZE - 1) return TRUE;
	else 
		return FALSE;
}
//스택에 집어넣기 함수
void Push(Stack* pstack, Element data) {
	if (!isFull(pstack))
		pstack->stackArr[++pstack->top] = data;
	else {
		printf("오류_스택이 다 찼다\n");
		exit(1); //시스템 강제 종료
	}
}
//스택에서 끄집어내기 함수
Element Pop(Stack* pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top--];
	else
		return NULL;
}

//이진 탐색 트리 삽입함수(학번/키, 이름, 전화번호 데이터 삽입)
void insert_node(TreeNode** root, TreeNode* new_node) {
	TreeNode* p, *t; //p는 부모노드, t는 현재노드
	int key = new_node->key;  //삽입할 노드의 키값

	t = *root;
	p = NULL;
	//삽입할 위치 탐색
	while(t != NULL) { //트리가 비어있지 않거나 끝이 아닐때까지 반복
		if (t->key == key) return;  //이미 있는 키인 경우
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	//key가 트리안에 없으므로 삽입가능
	new_node->left = new_node->right = NULL;

	//n을 부모노드p에 링크
	if (p != NULL) {
		if (key < p->key) p->left = new_node;
		else p->right = new_node;
	}
	else //빈 트리인 경우(root == null)
		*root = new_node;
}

//이진탐색트리 탐색 함수
TreeNode* search(TreeNode* root, int key) {
	TreeNode* node = root;
	while (node != NULL) {
		if (key == node->key) return node; //탐색성공
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;  //탐색실패
}

//**이진탐색트리 중위 순회 함수 + 이진탐색트리 검사 함수 -> 스택(재귀함수로는 검사가 어려움)
void inorder(TreeNode* root) { 
	Stack* pstack;
	TreeNode* node;
	int p = 0;  //이전 키값
	pstack = Create(); //스택 만들기
	node = root;

	for (;;) {
		for (;node;node = node->left)
			Push(pstack, node);   //왼쪽 노드가 null이 나올 때까지 스택에 push
		
		node = Pop(pstack);
		if (!node) break;   //스택이 비었음(끝)
		printf("%d ", node->key);
		if (node->key > p)  //나중에 방문한 노드가 먼저 방문한 노드에 비해 뒷쪽 학번
			printf("(OK)\n");
		else
			printf("(ER)\n");
		p = node->key;  //이전 키

		node = node->right;   //왼쪽->루트->'오른쪽 노드' 방문
	}
}

int main() {
	TreeNode* root, *new_node, *target;
	int randid[1000]; //새로 생성 학번
	int myid[1000];   //기존 학번
	int year;
	int id1, id2;
	int phone1, phone2;
	int i, j, k;

	//이진탐색트리 초기화(**이진 탐색 트리의 삽입 함수에서 빈 트리로 시작)
	root = NULL;

	//5만 명분 랜덤한 데이터 생성하여 트리에 삽입
	srand((unsigned int)time(NULL));
	k = 0; //myid의 번지
	for (i = 0;i < MAX_NUM;i++) {
		new_node = (TreeNode*)malloc(sizeof(TreeNode));
		//학번
		year = 2013 + rand() % 7;
		id1 = rand() % 1000;
		id2 = rand() % 100;
		new_node->key = year * 100000 + id1 * 100 + id2;
		//학번 중복 검사 -> 학번이 중복되면 다시 생성
		if (search(root, new_node->key) != NULL) {
			i--;
			continue;
		}
		//이름
		for (j = 0;j < 10;j++)
			new_node->name[j] = rand() % 26 + 'A';
		new_node->name[j] = NULL;
		//전화번호
		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010%04d%04d", phone1, phone2);
		//새로운 노드 삽입
		insert_node(&root, new_node);
		if (i >= MAX_NUM - 1000) //가장 마지막 1000명의 학번 저장
				myid[k++] = new_node->key;
	}

	//플레이 시작
	printf("Step 1. 중위 순회하기\n");
	inorder(root);

	printf("\nStep 2. 데이터 탐색하기\n");
	for (i = 0;i < 1000;i++) {
		target = search(root, myid[i]);
		printf("%4d. %d %s\n", i + 1, target->key, target->name);
	}
	
	printf("\nStep 3. 랜덤한 학번으로 검색하기\n");
	int count = 0;  //트리에서 찾은 학번 개수
	for (i = 0;i < 1000;i++) { //랜덤하게 1000개 학번 생성
		year = 2013 + rand() % 7;
		id1 = rand() % 1000;
		id2 = rand() % 100;
		randid[i] = year * 100000 + id1 * 100 + id2;
	}
	for (i = 0;i < 1000;i++) {
		target = search(root, randid[i]);
		if (target != NULL) {
			printf("%4d. %d %s\n", i + 1, target->key, target->name);
			count++;
		}
		else
			printf("%4d. %d (없음)\n", i + 1, randid[i]);
	}
	printf("\n총 %d개 발견\n", count);
}
