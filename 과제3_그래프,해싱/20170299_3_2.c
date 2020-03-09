#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD 46723
#define MOD 70000

//해쉬 테이블의 데이터
typedef struct {
	char word[50];
	char mean[100];
}Word;
//해시 테이블, overflow -> 체이닝
typedef struct ListNode {
	Word data;
	struct ListNode*link;
}ListNode;

typedef struct TreeNode {
	char key[50]; //키 = 단어
	char mean[100];
	struct TreeNode* left; //이진탐색트리를 링크로 구현
	struct TreeNode* right;
}TreeNode;

ListNode * hash[MOD]; //해시 테이블
int hash_count; //해시 테이블 탐색 빈도
int tree_count;

//연결리스트 삽입 함수 - 체이닝
void insert_node(ListNode **phead, ListNode* p, ListNode* new_node) {
	if (*phead == NULL) { //비어있는 연결리스트일 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { //p가 NULL이면 첫 칸에 삽입할 경우
		new_node->link = *phead;
		*phead = new_node;
	}
	else {  //p(previous) 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}

//이진 탐색 트리 삽입함수(단어/키, 의미 데이터 삽입)
void tree_insert_node(TreeNode** root, TreeNode* new_node) {
	TreeNode* p, *t; //p는 부모노드, t는 현재노드
	char* key = new_node->key;  //삽입할 노드의 키값

	t = *root;
	p = NULL;
	//삽입할 위치 탐색
	while (t != NULL) { //트리가 비어있지 않거나 끝이 아닐때까지 반복
		if (!strcmp(t->key,key)) return;  //이미 있는 키인 경우
		p = t;
		if (strcmp(key,t->key) < 0) t = t->left;
		else t = t->right;
	}
	//key가 트리안에 없으므로 삽입가능
	new_node->left = new_node->right = NULL;

	//n을 부모노드p에 링크
	if (p != NULL) {
		if (strcmp(key ,p->key)< 0) p->left = new_node;
		else p->right = new_node;
	}
	else //빈 트리인 경우(root == null)
		*root = new_node;
}
//이진탐색트리 탐색 함수
TreeNode* tree_search(TreeNode* root, char* key, int * count) {
	TreeNode* node = root;
	*count = 0;
	
	while (node != NULL) {
		(*count)++;
		if (!strcmp(key,node->key)) return node; //탐색성공
		else if (strcmp(key,node->key)<0)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;  //탐색실패
}

//해쉬 함수 - 키 주소 리턴 (이차 조사법 변형)
int hash_function(char * word) {
	int key_add = 0;
	int mult = 1;
	for (int i = 0;word[i] != NULL;i++) {
		key_add += (word[i] * mult + (i + 1)*(i + 1)) % MOD;
		mult *= 7;
	}
	if (key_add < 0) key_add = -key_add;  //절대값
	return key_add % MOD;
}
//다 꽉 찼을때 = overflow -> 체이닝
void chaining(int key, char* word, char*mean) {
	ListNode * new_node = NULL;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	new_node->link = NULL;
	strcpy(new_node->data.word, word);
	strcpy(new_node->data.mean, mean);
	insert_node(&hash[key], hash[key], new_node); //체이닝 -> 해시테이블 다음에 연결하기
}
//해시 테이블에 집어넣기
void hash_add(int key, char*word, char*mean) {
	if (!strcmp(hash[key]->data.word,"")) { //해시 테이블이 비어 있다면
		strcpy(hash[key]->data.word, word);
		strcpy(hash[key]->data.mean, mean);
		return;
	}
	else { //충돌 발생 - 선형조사법(약간)
		for (int i = 1;i < MOD/7;i++) {
			if (!strcmp(hash[(key + i) % MOD]->data.word, "")) { //빈칸을 찾음
				strcpy(hash[(key + i) % MOD]->data.word, word);
				strcpy(hash[(key + i) % MOD]->data.mean, mean);
				return; 
			}
		}
		//꽉 찬 경우 -> 체이닝
		chaining(key, word, mean);
	}
}

//해시 테이블 탐색 - 해당 단어가 있는 곳의 의미 출력
char* hash_search(int key, char* key_word, int * count) {
	ListNode* search = NULL;
	*count = 1;

	if (!strcmp(hash[key]->data.word, "")) {
		printf("단어를 다시 입력하시오.\n");
		return NULL;
	}
	else {
		//1. 바로 단어 찾음
		if (!strcmp(hash[key]->data.word, key_word)) 
			return hash[key]->data.mean;
		// 체이닝 연결 리스트 탐색 - 처음 key노드에 링크가 있다면
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
		//2. 선형조사법으로 탐색
		int i = 1;
		(*count)++;
		while (strcmp(hash[(key + i) % MOD]->data.word, hash[key]->data.word) != 0) { //다시 같은 자리로 되돌아오지않을때 까지
			if (!strcmp(hash[(key + i) % MOD]->data.word, key_word))
				return hash[(key + i) % MOD]->data.mean;
			// 체이닝 연결 리스트 탐색 - 이동한 노드에 링크가 있다면
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
			i++; //링크에도 없었으면 다음 테이블로 이동
			(*count)++;
		}
		printf("탐색 오류\n");
		return NULL;
	}
}

int main() {
	FILE * f;
	TreeNode* root, *new_node, *target;
	char str[200]; //파일의 한 줄 문장
	char data_word[30]; //한 줄 문장의 단어
	char data_mean[100]; //한 줄 문장의 의미
	char * tok;
	int key;
	int i;
	
	//해싱 테이블 초기화 -> 삽입이 어느곳에 될지 모르므로
	for (i = 0;i < MOD;i++) {
		hash[i] = (ListNode *)malloc(sizeof(ListNode));
		hash[i]->link = NULL;
		hash[i]->data.mean[0] = NULL;
		hash[i]->data.word[0] = NULL;
	}
	//이진탐색트리 초기화(**이진 탐색 트리의 삽입 함수에서 빈 트리로 시작)
	root = NULL;

	f = fopen("new_dict.txt", "r");
	if (f != NULL) {
		for (i = 0;i < MAX_WORD;i++) {
			new_node = (TreeNode*)malloc(sizeof(TreeNode));

			fgets(str, sizeof(str), f);
			tok = strtok(str, " :");
			strcpy(data_word, tok); //단어
			tok = strtok(NULL, ":\n"); 
			strcpy(data_mean, tok); //의미
			//이진 트리에 노드 넣기
			strcpy(new_node->key, data_word);
			strcpy(new_node->mean, data_mean);
			tree_insert_node(&root, new_node);
			//키 주소 얻기 -> 해시 테이블에 집어넣기
			key = hash_function(data_word); //키 = 단어
			hash_add(key, data_word, data_mean);
		}
	}
	else {
		printf("파일 찾지 못함\n");
		exit(-1);
	}
	fclose(f);

	char tree_ans[100];
	TreeNode* ans = NULL;
	
	printf("단어:");
	gets(str);
	ans = tree_search(root, str,&tree_count);
	printf("%s (%d) -> 이진 탐색 트리\n", ans->mean, tree_count);
	key = hash_function(str);
	printf("%s ", hash_search(key, str,&hash_count));
	printf("(%d) -> 해싱 테이블\n", hash_count);
}