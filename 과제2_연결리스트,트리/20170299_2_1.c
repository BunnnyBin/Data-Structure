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
//���Ḯ��Ʈ ���� �Լ�
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
//���Ḯ��Ʈ ���� �Լ�
void remove_node(ListNode** phead, ListNode* p, ListNode* removed) {
	if (p == NULL) //ù ��带 ������ ���
		*phead = removed->link; //== (*phead)->link
	else    //p ������ ��� ����
		p->link = removed->link;
	free(removed);
}
//���Ḯ��Ʈ ��� �Լ�(��Ϻ���)
void display(ListNode* head) {
	ListNode* p = head;
	int count = 1;
	while (p != NULL) { //��尡 null�� �ƴҶ����� �ݺ��ؼ� ���
		printf("%d.%3s %s\n",count++, p->name, p->phone);
		p = p->link;
	}
}
//**���Ḯ��Ʈ ���� �Լ�(�̸��� �������� ����)->��������**
void array(ListNode** phead) {
	ListNode* pre = NULL; //���� ��ġ
	ListNode* cur = *phead; //���� ��ġ
	ListNode* next = cur->link; //���� ��ġ(����� ���� ������)
	ListNode* tail = NULL; //���ĵ� ������ �� ó�� ��ġ
	ListNode* temp;

	while (tail != *phead) {
		//�������� �ѹ���
		while (next != tail) {
			for (int i = 0;i < 3;i++) { //�̸� 3���� ����
				if (cur->name[i] > next->name[i]) {
					cur->link = next->link;
					next->link = cur;
					if (cur == *phead)  //��尪�� �ٲ�� ���
						*phead = next;
					else  //������ ���
						pre->link = next;

					SWAP(cur, next, temp); //**���ķ� ���� cur,next ��ġ�� �ڹٲ�-> ����ġ�� ���ư���
					break; //**�̸� �ݺ��� Ż��
				}
				else if (cur->name[i] < next->name[i]) 
					break; //**�̸� �ݺ��� Ż��(�ƹ��͵� ���ϱ�)
			}
			pre = cur;
			cur = cur->link;
			next = next->link;
		}
		tail = cur; //���ĵ� �� ó�� ����(while�ݺ������� ���� cur)
		//**������ġ,������ġ,������ġ �ʱ�ȭ**
		pre = NULL;
		cur = *phead;
		next = cur->link;
	}
}
//���Ḯ��Ʈ Ž�� �Լ�(�ش� �̸�/��ȭ��ȣ ã��)
ListNode* search(ListNode* head, char* data) {
	ListNode* p = head; //��� ������ Ž�� ����
	while (p != NULL) {
		if (!strcmp(p->name, data)) return p; //�� ���ڿ�(�̸�)�� ����
		else if(!strcmp(p->phone, data))  return p;
		p = p->link;
	}
	return p; //Ž�� ���� -> NULL ��ȯ
}
//���Ḯ��Ʈ ���� ��� Ž�� �Լ�(Ž�� ����� ���� ��� ã��)
ListNode* psearch(ListNode* head, char*data) {
	ListNode* p = head;

	if (!strcmp(head->name, data)) return NULL;  //����尡 ã�� ����� ���(���� ���� null��ȯ)

	while (p->link != NULL) { //������ ��� �� �ʿ�x
		if (!strcmp(p->link->name, data)) return p; //�� ���ڿ�(�̸�)�� ����
		p = p->link;
	}
	return p; //Ž�� ����(������ ��� ��ȯ)
}
//���Ḯ��Ʈ ����(��� ����) �Լ�
int get_length(ListNode* head) {
	ListNode* p = head;
	int length = 0;
	if (head != NULL){ //�� ����Ʈ�� �ƴ϶��
		while (p != NULL) {
			length++;
			p = p->link;
		}
	}
	return length;
}

int main() {
	ListNode* head;
	ListNode* new_node;  //������ ���
	ListNode* removed;   //������ ���
	ListNode* before;    //������ ����� ���� ���
	ListNode* target;    //Ž���� ���
	char key[7];  //����ڰ� �Է��� ��ɾ�
	char number[14]; //����ڰ� �Է��� ��ȭ��ȣ(���� ���)
	int phone1, phone2;
	int i, j;
	
	//���Ḯ��Ʈ �ʱ�ȭ
	head = NULL;
	//10���� ������ ������ ����
	srand(time(NULL));
	for (i = 0;i < DATA;i++) {
		//�� ��� ����
		new_node = (ListNode*)malloc(sizeof(ListNode));
		//�̸�(3���ڷ� ����)
		for (j = 0;j < 3;j++)
			new_node->name[j] = rand() % 26 + 'A';
		new_node->name[j] = NULL; //**���ڿ��� �ι��� �ֱ�**
		//��ȭ��ȣ
		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010-%04d-%04d", phone1, phone2);
		
		//�ߺ� �˻�
		if (search(head, new_node->name) != NULL || search(head, new_node->phone) != NULL) { //�ߺ��� ���
			i--;
			free(new_node);
		}
		else { //�ߺ��� �ƴϸ�
			//����Ʈ ó���� ����
			insert_node(&head, NULL, new_node);
		}
	}

	//�÷��� ����
	char removed_name[4];  
	char pkey[7];  //key���纻
	char * token;

	printf("(%d���� �����Ͱ� �ֽ��ϴ�)\n>> ", get_length(head));
	gets(key);
	while (strcmp(key,"exit") != 0) {
		if (strstr(key, "����") != NULL) { //���� ��ɾ��� ���
			strcpy(pkey, key);
			token = strtok(pkey, " ");
			strcpy(key, token); //"����" -> key�� ����ֱ�
			token = strtok(NULL, " ");
			strcpy(removed_name, token); //������ �̸� -> removed_name�� ����ֱ�
		}
		//"�̸�" ��ɾ�
		if (strcmp(key, "���") != 0 && strcmp(key, "����") != 0 && strcmp(key, "����") != 0) {
			target = search(head, key);
			//�ش� �̸��� ���� ���(���� �Լ�)
			if (target == NULL) {
				printf("(�������� �ʴ� �̸��Դϴ�. ��ȭ��ȣ�� �Է��ϼ���)\n��ȭ��ȣ>>> ");
				gets(number);
				//new_node ����(������ ���)
				new_node = (ListNode*)malloc(sizeof(ListNode));
				strcpy(new_node->name, key); 
				strcpy(new_node->phone, number);
				insert_node(&head, NULL, new_node); //���� �Լ�(����Ʈ ó���� ����)
				printf("(%s %s �� �ԷµǾ����ϴ�)\n", key, number);
			}
			//�ش� �̸��� �ִ� ���
			else
				printf("(ã�ҽ��ϴ�) %s\n", target->phone);
		}
		//"���" ��ɾ�
		else if (!strcmp(key, "���"))
			display(head);
		//"����" ��ɾ�
		else if (!strcmp(key, "����")) {
			array(&head);
			display(head);
		}
		//"����" ��ɾ�
		else if (!strcmp(key, "����")) {
			removed = search(head, removed_name); //������ ���
			if (removed != NULL) {
				printf("(%s %s �� �����Ǿ����ϴ�)\n", removed_name, removed->phone);
				before = psearch(head, removed_name); //������ ��� ����
				remove_node(&head, before, removed);    //����
			}
		}
		printf("(%d���� �����Ͱ� �ֽ��ϴ�)\n>> ", get_length(head));
		gets(key);
	}
}