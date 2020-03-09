#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD 46723
#define MOD 70000

//�ؽ� ���̺��� ������
typedef struct {
	char word[50];
	char mean[100];
}Word;
//�ؽ� ���̺�, overflow -> ü�̴�
typedef struct ListNode {
	Word data;
	struct ListNode*link;
}ListNode;

typedef struct TreeNode {
	char key[50]; //Ű = �ܾ�
	char mean[100];
	struct TreeNode* left; //����Ž��Ʈ���� ��ũ�� ����
	struct TreeNode* right;
}TreeNode;

ListNode * hash[MOD]; //�ؽ� ���̺�
int hash_count; //�ؽ� ���̺� Ž�� ��
int tree_count;

//���Ḯ��Ʈ ���� �Լ� - ü�̴�
void insert_node(ListNode **phead, ListNode* p, ListNode* new_node) {
	if (*phead == NULL) { //����ִ� ���Ḯ��Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { //p�� NULL�̸� ù ĭ�� ������ ���
		new_node->link = *phead;
		*phead = new_node;
	}
	else {  //p(previous) ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}

//���� Ž�� Ʈ�� �����Լ�(�ܾ�/Ű, �ǹ� ������ ����)
void tree_insert_node(TreeNode** root, TreeNode* new_node) {
	TreeNode* p, *t; //p�� �θ���, t�� ������
	char* key = new_node->key;  //������ ����� Ű��

	t = *root;
	p = NULL;
	//������ ��ġ Ž��
	while (t != NULL) { //Ʈ���� ������� �ʰų� ���� �ƴҶ����� �ݺ�
		if (!strcmp(t->key,key)) return;  //�̹� �ִ� Ű�� ���
		p = t;
		if (strcmp(key,t->key) < 0) t = t->left;
		else t = t->right;
	}
	//key�� Ʈ���ȿ� �����Ƿ� ���԰���
	new_node->left = new_node->right = NULL;

	//n�� �θ���p�� ��ũ
	if (p != NULL) {
		if (strcmp(key ,p->key)< 0) p->left = new_node;
		else p->right = new_node;
	}
	else //�� Ʈ���� ���(root == null)
		*root = new_node;
}
//����Ž��Ʈ�� Ž�� �Լ�
TreeNode* tree_search(TreeNode* root, char* key, int * count) {
	TreeNode* node = root;
	*count = 0;
	
	while (node != NULL) {
		(*count)++;
		if (!strcmp(key,node->key)) return node; //Ž������
		else if (strcmp(key,node->key)<0)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;  //Ž������
}

//�ؽ� �Լ� - Ű �ּ� ���� (���� ����� ����)
int hash_function(char * word) {
	int key_add = 0;
	int mult = 1;
	for (int i = 0;word[i] != NULL;i++) {
		key_add += (word[i] * mult + (i + 1)*(i + 1)) % MOD;
		mult *= 7;
	}
	if (key_add < 0) key_add = -key_add;  //���밪
	return key_add % MOD;
}
//�� �� á���� = overflow -> ü�̴�
void chaining(int key, char* word, char*mean) {
	ListNode * new_node = NULL;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	new_node->link = NULL;
	strcpy(new_node->data.word, word);
	strcpy(new_node->data.mean, mean);
	insert_node(&hash[key], hash[key], new_node); //ü�̴� -> �ؽ����̺� ������ �����ϱ�
}
//�ؽ� ���̺� ����ֱ�
void hash_add(int key, char*word, char*mean) {
	if (!strcmp(hash[key]->data.word,"")) { //�ؽ� ���̺��� ��� �ִٸ�
		strcpy(hash[key]->data.word, word);
		strcpy(hash[key]->data.mean, mean);
		return;
	}
	else { //�浹 �߻� - ���������(�ణ)
		for (int i = 1;i < MOD/7;i++) {
			if (!strcmp(hash[(key + i) % MOD]->data.word, "")) { //��ĭ�� ã��
				strcpy(hash[(key + i) % MOD]->data.word, word);
				strcpy(hash[(key + i) % MOD]->data.mean, mean);
				return; 
			}
		}
		//�� �� ��� -> ü�̴�
		chaining(key, word, mean);
	}
}

//�ؽ� ���̺� Ž�� - �ش� �ܾ �ִ� ���� �ǹ� ���
char* hash_search(int key, char* key_word, int * count) {
	ListNode* search = NULL;
	*count = 1;

	if (!strcmp(hash[key]->data.word, "")) {
		printf("�ܾ �ٽ� �Է��Ͻÿ�.\n");
		return NULL;
	}
	else {
		//1. �ٷ� �ܾ� ã��
		if (!strcmp(hash[key]->data.word, key_word)) 
			return hash[key]->data.mean;
		// ü�̴� ���� ����Ʈ Ž�� - ó�� key��忡 ��ũ�� �ִٸ�
		if (hash[key]->link != NULL) {
			search = hash[key]->link;
			(*count)++;
			while (search) {
				if (!strcmp(search->data.word, key_word))
					return search->data.mean;
				search = search->link;
				(*count)++;
			}
		}
		//2. ������������� Ž��
		int i = 1;
		(*count)++;
		while (strcmp(hash[(key + i) % MOD]->data.word, hash[key]->data.word) != 0) { //�ٽ� ���� �ڸ��� �ǵ��ƿ��������� ����
			if (!strcmp(hash[(key + i) % MOD]->data.word, key_word))
				return hash[(key + i) % MOD]->data.mean;
			// ü�̴� ���� ����Ʈ Ž�� - �̵��� ��忡 ��ũ�� �ִٸ�
			if (hash[(key + i) % MOD]->link != NULL) {
				search = hash[(key + i) % MOD]->link;
				(*count)++;
				while (search) {
					if (!strcmp(search->data.word, key_word))
						return search->data.mean;
					search = search->link;
					(*count)++;
				}
			}
			i++; //��ũ���� �������� ���� ���̺�� �̵�
			(*count)++;
		}
		printf("Ž�� ����\n");
		return NULL;
	}
}

int main() {
	FILE * f;
	TreeNode* root, *new_node, *target;
	char str[200]; //������ �� �� ����
	char data_word[30]; //�� �� ������ �ܾ�
	char data_mean[100]; //�� �� ������ �ǹ�
	char * tok;
	int key;
	int i;
	
	//�ؽ� ���̺� �ʱ�ȭ -> ������ ������� ���� �𸣹Ƿ�
	for (i = 0;i < MOD;i++) {
		hash[i] = (ListNode *)malloc(sizeof(ListNode));
		hash[i]->link = NULL;
		hash[i]->data.mean[0] = NULL;
		hash[i]->data.word[0] = NULL;
	}
	//����Ž��Ʈ�� �ʱ�ȭ(**���� Ž�� Ʈ���� ���� �Լ����� �� Ʈ���� ����)
	root = NULL;

	f = fopen("new_dict.txt", "r");
	if (f != NULL) {
		for (i = 0;i < MAX_WORD;i++) {
			new_node = (TreeNode*)malloc(sizeof(TreeNode));

			fgets(str, sizeof(str), f);
			tok = strtok(str, " :");
			strcpy(data_word, tok); //�ܾ�
			tok = strtok(NULL, ":\n"); 
			strcpy(data_mean, tok); //�ǹ�
			//���� Ʈ���� ��� �ֱ�
			strcpy(new_node->key, data_word);
			strcpy(new_node->mean, data_mean);
			tree_insert_node(&root, new_node);
			//Ű �ּ� ��� -> �ؽ� ���̺� ����ֱ�
			key = hash_function(data_word); //Ű = �ܾ�
			hash_add(key, data_word, data_mean);
		}
	}
	else {
		printf("���� ã�� ����\n");
		exit(-1);
	}
	fclose(f);

	char tree_ans[100];
	TreeNode* ans = NULL;
	
	printf("�ܾ�:");
	gets(str);
	ans = tree_search(root, str,&tree_count);
	printf("%s (%d) -> ���� Ž�� Ʈ��\n", ans->mean, tree_count);
	key = hash_function(str);
	printf("%s ", hash_search(key, str,&hash_count));
	printf("(%d) -> �ؽ� ���̺�\n", hash_count);
}