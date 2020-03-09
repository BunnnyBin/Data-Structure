#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) (t)=(x),(x)=(y),(y)=(t)
#define DATA 10
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	char name[4];
	char phone[14];
	struct ListNode*link;
}ListNode;
//연결리스트 삽입 함수
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
//연결리스트 삭제 함수
void remove_node(ListNode** phead, ListNode* p, ListNode* removed) {
	if (p == NULL) //첫 노드를 삭제할 경우
		*phead = removed->link; //== (*phead)->link
	else    //p 다음의 노드 삭제
		p->link = removed->link;
	free(removed);
}
//연결리스트 출력 함수(목록보기)
void display(ListNode* head) {
	ListNode* p = head;
	int count = 1;
	while (p != NULL) { //헤드가 null이 아닐때까지 반복해서 출력
		printf("%d.%3s %s\n",count++, p->name, p->phone);
		p = p->link;
	}
}
//**연결리스트 정렬 함수(이름을 기준으로 정렬)->버블정렬**
void array(ListNode** phead) {
	ListNode* pre = NULL; //이전 위치
	ListNode* cur = *phead; //현재 위치
	ListNode* next = cur->link; //다음 위치(현재와 비교할 데이터)
	ListNode* tail = NULL; //정렬된 구간의 맨 처음 위치
	ListNode* temp;

	while (tail != *phead) {
		//버블정렬 한바퀴
		while (next != tail) {
			for (int i = 0;i < 3;i++) { //이름 3글자 제한
				if (cur->name[i] > next->name[i]) {
					cur->link = next->link;
					next->link = cur;
					if (cur == *phead)  //헤드값이 바뀌는 경우
						*phead = next;
					else  //나머지 경우
						pre->link = next;

					SWAP(cur, next, temp); //**정렬로 인해 cur,next 위치가 뒤바뀜-> 재위치로 돌아가기
					break; //**이름 반복문 탈출
				}
				else if (cur->name[i] < next->name[i]) 
					break; //**이름 반복문 탈출(아무것도 않하기)
			}
			pre = cur;
			cur = cur->link;
			next = next->link;
		}
		tail = cur; //정렬된 맨 처음 구간(while반복문에서 나온 cur)
		//**현재위치,이전위치,다음위치 초기화**
		pre = NULL;
		cur = *phead;
		next = cur->link;
	}
}
//연결리스트 탐색 함수(해당 이름/전화번호 찾기)
ListNode* search(ListNode* head, char* data) {
	ListNode* p = head; //헤드 노드부터 탐색 시작
	while (p != NULL) {
		if (!strcmp(p->name, data)) return p; //두 문자열(이름)비교 성공
		else if(!strcmp(p->phone, data))  return p;
		p = p->link;
	}
	return p; //탐색 실패 -> NULL 반환
}
//연결리스트 이전 노드 탐색 함수(탐색 노드의 이전 노드 찾기)
ListNode* psearch(ListNode* head, char*data) {
	ListNode* p = head;

	if (!strcmp(head->name, data)) return NULL;  //헤드노드가 찾는 노드인 경우(이전 노드는 null반환)

	while (p->link != NULL) { //마지막 노드 볼 필요x
		if (!strcmp(p->link->name, data)) return p; //두 문자열(이름)비교 성공
		p = p->link;
	}
	return p; //탐색 실패(마지막 노드 반환)
}
//연결리스트 길이(요소 개수) 함수
int get_length(ListNode* head) {
	ListNode* p = head;
	int length = 0;
	if (head != NULL){ //빈 리스트가 아니라면
		while (p != NULL) {
			length++;
			p = p->link;
		}
	}
	return length;
}

int main() {
	ListNode* head;
	ListNode* new_node;  //삽입할 노드
	ListNode* removed;   //삭제할 노드
	ListNode* before;    //삭제할 노드의 이전 노드
	ListNode* target;    //탐색할 노드
	char key[7];  //사용자가 입력할 명령어
	char number[14]; //사용자가 입력할 전화번호(삽입 노드)
	int phone1, phone2;
	int i, j;
	
	//연결리스트 초기화
	head = NULL;
	//10명의 랜덤한 데이터 생성
	srand(time(NULL));
	for (i = 0;i < DATA;i++) {
		//새 노드 생성
		new_node = (ListNode*)malloc(sizeof(ListNode));
		//이름(3글자로 제한)
		for (j = 0;j < 3;j++)
			new_node->name[j] = rand() % 26 + 'A';
		new_node->name[j] = NULL; //**문자열에 널문자 넣기**
		//전화번호
		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010-%04d-%04d", phone1, phone2);
		
		//중복 검사
		if (search(head, new_node->name) != NULL || search(head, new_node->phone) != NULL) { //중복된 경우
			i--;
			free(new_node);
		}
		else { //중복이 아니면
			//리스트 처음에 삽입
			insert_node(&head, NULL, new_node);
		}
	}

	//플레이 시작
	char removed_name[4];  
	char pkey[7];  //key복사본
	char * token;

	printf("(%d명의 데이터가 있습니다)\n>> ", get_length(head));
	gets(key);
	while (strcmp(key,"exit") != 0) {
		if (strstr(key, "삭제") != NULL) { //삭제 명령어인 경우
			strcpy(pkey, key);
			token = strtok(pkey, " ");
			strcpy(key, token); //"삭제" -> key에 집어넣기
			token = strtok(NULL, " ");
			strcpy(removed_name, token); //삭제할 이름 -> removed_name에 집어넣기
		}
		//"이름" 명령어
		if (strcmp(key, "목록") != 0 && strcmp(key, "정렬") != 0 && strcmp(key, "삭제") != 0) {
			target = search(head, key);
			//해당 이름이 없는 경우(삽입 함수)
			if (target == NULL) {
				printf("(존재하지 않는 이름입니다. 전화번호를 입력하세요)\n전화번호>>> ");
				gets(number);
				//new_node 생성(삽입할 노드)
				new_node = (ListNode*)malloc(sizeof(ListNode));
				strcpy(new_node->name, key); 
				strcpy(new_node->phone, number);
				insert_node(&head, NULL, new_node); //삽입 함수(리스트 처음에 삽입)
				printf("(%s %s 가 입력되었습니다)\n", key, number);
			}
			//해당 이름이 있는 경우
			else
				printf("(찾았습니다) %s\n", target->phone);
		}
		//"목록" 명령어
		else if (!strcmp(key, "목록"))
			display(head);
		//"정렬" 명령어
		else if (!strcmp(key, "정렬")) {
			array(&head);
			display(head);
		}
		//"삭제" 명령어
		else if (!strcmp(key, "삭제")) {
			removed = search(head, removed_name); //삭제할 노드
			if (removed != NULL) {
				printf("(%s %s 가 삭제되었습니다)\n", removed_name, removed->phone);
				before = psearch(head, removed_name); //삭제할 노드 이전
				remove_node(&head, before, removed);    //삭제
			}
		}
		printf("(%d명의 데이터가 있습니다)\n>> ", get_length(head));
		gets(key);
	}
}