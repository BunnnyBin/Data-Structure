#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 10000
#include <stdio.h>
#include <stdlib.h>

typedef struct DlistNode {
	int id;
	char name[11];
	char phone[12];
	struct DlistNode* link;
	struct DlistNode* id_link;
	struct DlistNode* name_link;
}DlistNode;

//���� ���Ḯ��Ʈ ���� �Լ�(���ο� ��� ����Ʈ �� ó���� ���� -> �̸�,�й� ��ũ ����)
void insert_node(DlistNode* head, DlistNode* new_node) {
	DlistNode* pre; //���ο� ����� ���� ���
	DlistNode* next; //���ο� ����� ���� ���
	
	new_node->link = head->link;
	head->link = new_node;
	//�й� ��ũ ����
	pre = head;
	next = pre->id_link;
	if (next == NULL) { //**����Ʈ�� ����ִ� ��� 
		new_node->id_link = NULL;
		head->id_link = new_node;
		new_node->name_link = NULL;
		head->name_link = new_node;
	}
	else {
		while (next != NULL) {
			if (new_node->id < next->id) {
				new_node->id_link = next;
				pre->id_link = new_node;
				break;
			}
			else if (next->id_link == NULL) { //**���ο� ��带 �������� ����
				new_node->id_link = NULL;
				next->id_link = new_node;
				break;
			}
			else { //������ ���� �ƴϸ� �̵��ϱ�
				pre = pre->id_link;
				next = next->id_link;
			}
		}
		//�̸� ��ũ ����
		pre = head;
		next = pre->name_link;
		while (next != NULL) {
			if (strcmp(new_node->name, next->name) < 0) {
				new_node->name_link = next;
				pre->name_link = new_node;
				break;
			}
			else if (next->name_link == NULL) { 
				new_node->name_link = NULL;
				next->name_link = new_node;
				break;
			}
			else {
				pre = pre->name_link;
				next = next->name_link;
			}
		}
	}
}

//���� ���Ḯ��Ʈ ��� �Լ�
void display(DlistNode* head, int choice) {
	DlistNode* p = head;
	int count = 1;
	//�й� ������ ����ϱ�
	if (choice == 1) {
		p = p->id_link;
		while (p != NULL) {
			printf("%5d.%d %s %s\n",count++, p->id, p->name, p->phone);
			p = p->id_link;
		}
	}
	else if (choice == 2) {
		p = p->name_link;
		while (p != NULL) {
			printf("%5d.%d %s %s\n",count++, p->id, p->name, p->phone);
			p = p->name_link;
		}
	}
}
//���� ���Ḯ��Ʈ Ž�� �Լ�(�ش� �й� ã��)
DlistNode* search_id(DlistNode* head, int id) {
	DlistNode* p = head->id_link; //��� ������ Ž�� ����
	while (p != NULL) {
		if (p->id == id) return p; //�� ����
		p = p->id_link;
	}
	return p; //Ž�� ���� -> NULL ��ȯ
}
//���� ���Ḯ��Ʈ Ž�� �Լ�(�ش� �̸�,��ȭ��ȣ ã��)
DlistNode* search_namephone(DlistNode* head, char* data) {
	DlistNode* p = head->name_link; //��� ������ Ž�� ����
	while (p != NULL) {
		if (!strcmp(p->name, data)) return p; //�̸� �� ����
		else if (!strcmp(p->phone, data)) return p; //��ȭ��ȣ �� ����
		p = p->name_link;
	}
	return p; //Ž�� ���� -> NULL ��ȯ
}

int main() {
	//���� ���(���) ����
	DlistNode* head = (DlistNode*)malloc(sizeof(DlistNode));
	head->link = NULL; //���Ḯ��Ʈ �ʱ�ȭ
	head->id_link = NULL; //�й� ���Ḯ��Ʈ, �̸� ���Ḯ��Ʈ �ʱ�ȭ
	head->name_link = NULL; 
	head->id = 0; //��� ���� �� ����
	head->name[0] = NULL;
	head->phone[0] = NULL;
	
	DlistNode* new_node;
	int year;
	int	idnum1, idnum2;
	int	phone1, phone2;
	int i,j;
	
	//1�� ����� ���� ������ ����
	srand(time(NULL));
	for (i = 0;i < MAX_NUM;i++) {
		new_node = (DlistNode*)malloc(sizeof(DlistNode));
		//�й� ������
		year = rand() % 7 + 2013;
		idnum1 = rand() % 1000;
		idnum2 = rand() % 100;
		new_node->id = year * 100000 + idnum1 * 100 + idnum2;
		//�̸� ������
		for (j = 0;j < 10;j++)
			new_node->name[j] = rand() % 26 + 'A';
		new_node->name[j] = NULL;
		//��ȭ��ȣ ������
		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010%04d%04d", phone1, phone2);
		
		//�ߺ� �˻�
		if (search_id(head, new_node->id) != NULL)
			i--;
		else if (search_namephone(head, new_node->name) != NULL)
			i--;
		else if (search_namephone(head, new_node->phone) != NULL)
			i--;
		else
			insert_node(head, new_node); //�ߺ��� ���� ������ �����ϱ�
	 }
	
	int user;
	printf("(1)�й���\n(2)�̸���\n�޴� ����(0: ����) : ");
	scanf("%d", &user);
	while (user != 0) {
		display(head, user);
		printf("\n(1)�й���\n(2)�̸���\n�޴� ����(0: ����) : ");
		scanf("%d", &user);
	}
}