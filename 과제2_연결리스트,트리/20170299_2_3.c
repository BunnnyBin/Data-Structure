#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 50000
#define MAX_STACK_SIZE 50
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key; //�й�
	char name[11];
	char phone[12];
	struct TreeNode* left; //����Ž��Ʈ���� ��ũ�� ����
	struct TreeNode* right;
}TreeNode;

typedef TreeNode* Element;

typedef struct Stack {
	Element stackArr[MAX_STACK_SIZE];
	int top;
}Stack;
//���� ����� �Լ�
Stack* Create(void) {
	Stack* tempstack = (Stack*)malloc(sizeof(Stack));
	tempstack->top = -1;
	return tempstack;
}
//������ ������� �˻� �Լ�
int isEmpty(Stack* pstack) {
	if (pstack->top == -1) return TRUE;
	else
		return FALSE;
}
//������ á���� �˻� �Լ�
int isFull(Stack* pstack) {
	if (pstack->top == MAX_STACK_SIZE - 1) return TRUE;
	else 
		return FALSE;
}
//���ÿ� ����ֱ� �Լ�
void Push(Stack* pstack, Element data) {
	if (!isFull(pstack))
		pstack->stackArr[++pstack->top] = data;
	else {
		printf("����_������ �� á��\n");
		exit(1); //�ý��� ���� ����
	}
}
//���ÿ��� ������� �Լ�
Element Pop(Stack* pstack) {
	if (!isEmpty(pstack))
		return pstack->stackArr[pstack->top--];
	else
		return NULL;
}

//���� Ž�� Ʈ�� �����Լ�(�й�/Ű, �̸�, ��ȭ��ȣ ������ ����)
void insert_node(TreeNode** root, TreeNode* new_node) {
	TreeNode* p, *t; //p�� �θ���, t�� ������
	int key = new_node->key;  //������ ����� Ű��

	t = *root;
	p = NULL;
	//������ ��ġ Ž��
	while(t != NULL) { //Ʈ���� ������� �ʰų� ���� �ƴҶ����� �ݺ�
		if (t->key == key) return;  //�̹� �ִ� Ű�� ���
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	//key�� Ʈ���ȿ� �����Ƿ� ���԰���
	new_node->left = new_node->right = NULL;

	//n�� �θ���p�� ��ũ
	if (p != NULL) {
		if (key < p->key) p->left = new_node;
		else p->right = new_node;
	}
	else //�� Ʈ���� ���(root == null)
		*root = new_node;
}

//����Ž��Ʈ�� Ž�� �Լ�
TreeNode* search(TreeNode* root, int key) {
	TreeNode* node = root;
	while (node != NULL) {
		if (key == node->key) return node; //Ž������
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;  //Ž������
}

//**����Ž��Ʈ�� ���� ��ȸ �Լ� + ����Ž��Ʈ�� �˻� �Լ� -> ����(����Լ��δ� �˻簡 �����)
void inorder(TreeNode* root) { 
	Stack* pstack;
	TreeNode* node;
	int p = 0;  //���� Ű��
	pstack = Create(); //���� �����
	node = root;

	for (;;) {
		for (;node;node = node->left)
			Push(pstack, node);   //���� ��尡 null�� ���� ������ ���ÿ� push
		
		node = Pop(pstack);
		if (!node) break;   //������ �����(��)
		printf("%d ", node->key);
		if (node->key > p)  //���߿� �湮�� ��尡 ���� �湮�� ��忡 ���� ���� �й�
			printf("(OK)\n");
		else
			printf("(ER)\n");
		p = node->key;  //���� Ű

		node = node->right;   //����->��Ʈ->'������ ���' �湮
	}
}

int main() {
	TreeNode* root, *new_node, *target;
	int randid[1000]; //���� ���� �й�
	int myid[1000];   //���� �й�
	int year;
	int id1, id2;
	int phone1, phone2;
	int i, j, k;

	//����Ž��Ʈ�� �ʱ�ȭ(**���� Ž�� Ʈ���� ���� �Լ����� �� Ʈ���� ����)
	root = NULL;

	//5�� ��� ������ ������ �����Ͽ� Ʈ���� ����
	srand((unsigned int)time(NULL));
	k = 0; //myid�� ����
	for (i = 0;i < MAX_NUM;i++) {
		new_node = (TreeNode*)malloc(sizeof(TreeNode));
		//�й�
		year = 2013 + rand() % 7;
		id1 = rand() % 1000;
		id2 = rand() % 100;
		new_node->key = year * 100000 + id1 * 100 + id2;
		//�й� �ߺ� �˻� -> �й��� �ߺ��Ǹ� �ٽ� ����
		if (search(root, new_node->key) != NULL) {
			i--;
			continue;
		}
		//�̸�
		for (j = 0;j < 10;j++)
			new_node->name[j] = rand() % 26 + 'A';
		new_node->name[j] = NULL;
		//��ȭ��ȣ
		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010%04d%04d", phone1, phone2);
		//���ο� ��� ����
		insert_node(&root, new_node);
		if (i >= MAX_NUM - 1000) //���� ������ 1000���� �й� ����
				myid[k++] = new_node->key;
	}

	//�÷��� ����
	printf("Step 1. ���� ��ȸ�ϱ�\n");
	inorder(root);

	printf("\nStep 2. ������ Ž���ϱ�\n");
	for (i = 0;i < 1000;i++) {
		target = search(root, myid[i]);
		printf("%4d. %d %s\n", i + 1, target->key, target->name);
	}
	
	printf("\nStep 3. ������ �й����� �˻��ϱ�\n");
	int count = 0;  //Ʈ������ ã�� �й� ����
	for (i = 0;i < 1000;i++) { //�����ϰ� 1000�� �й� ����
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
			printf("%4d. %d (����)\n", i + 1, randid[i]);
	}
	printf("\n�� %d�� �߰�\n", count);
}
