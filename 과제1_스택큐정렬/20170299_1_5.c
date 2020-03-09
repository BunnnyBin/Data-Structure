#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int stdnum[9];
	char name[11]; //10����(�������� �ι���)
	int phone[11];
}Student;

//�й��� ���� ���� ����
void selection_sort_Bystdnum(Student * list[], int n) {
	int i,j,l,least; //least�� ���� ���� �й��� ����ü ������
	Student * temp;
	
	for (i = 0;i < n - 1;i++) { //���ĵ��� ���� ������ ù ����
		least = i;
		for (j = i + 1;j < n;j++) { //least == i�̹Ƿ� i + 1���� ��
			for (l = 0;l < 9;l++) {
				if (list[j]->stdnum[l] < list[least]->stdnum[l]) {
					least = j;
					break; //l�ݺ��� ������(���� ����ü�� �Ѿ��)
				}
				else if(list[least]->stdnum[l] < list[j]->stdnum[l])
					break;  //least����ü�� ������ ������ l�ݺ��� ������(���� ����ü�� �̵�)
			}
		}
		SWAP(list[i], list[least], temp); //����ü ������ �� ��ȯ
	}
}
//�̸��� ���� ���� ����
void selection_sort_Byname(Student * list[], int n) {
	int i, j, l, least;
	Student * temp;

	for (i = 0;i < n - 1;i++) {
		least = i;
		for (j = i + 1;j < n;j++) {
			for (l = 0;l < 9;l++) {
				if (list[j]->name[l] < list[least]->name[l]) {
					least = j;
					break;
				}
				else if (list[least]->name[l] < list[j]->name[l])
					break;
			}
		}
		SWAP(list[i], list[least], temp); //����ü ������ �� ��ȯ
	}
}
//�й��� ���� �� ����**
int partition_Bystdnum(Student * list[], int left, int right) {
	int pivot[9]; //�ǹ� ��
	Student * temp;
	int low, high;  //�ǹ� ���� ���� ���� �ε���, �ǹ����� ū ���� �ε���
	int i;

	low = left;
	high = right + 1;
	
	for (i = 0;i < 9;i++)
		pivot[i] = list[left]->stdnum[i]; //�ǹ��� �迭�� �� ó�� ��

	do {
		do {
			low++;
			for (i = 0;i < 9;i++) {  //low�� �ǹ��� ������ i++(���� ���ڷ� �̵�)
				if (list[low]->stdnum[i] < pivot[i])  //low�� �й��� �ǹ����� �� ���ڶ� ������
					break; //while������
				else if (list[low]->stdnum[i] > pivot[i]) //low�� �й� �� �� ���ڰ� �ǹ����� ũ��
					break;
			}
		} while (low < right && list[low]->stdnum[i] < pivot[i]); //low�� �迭�� �Ѿ�� �ʰ� ����
		do{
			high--;
			for (i = 0;i < 9;i++) {
				if (list[high]->stdnum[i] > pivot[i])
					break;
				else if (list[high]->stdnum[i] < pivot[i])
					break;
			}
		}while (high > left && list[high]->stdnum[i] > pivot[i]);

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp); //���� ������ ���� ������ ��ġ�� �ǹ��� ��ȯ!
	return high; //�ǹ� ��ġ ��ȯ
}
void quick_sort_Bystdnum(Student * list[], int left, int right) {
	if (left < right) {
		int q = partition_Bystdnum(list, left, right); //���� -> �ǹ����� ū��, ���������� ����(�ǹ� ��ġ ��ȯ)
		quick_sort_Bystdnum(list, left, q - 1);
		quick_sort_Bystdnum(list, q + 1, right);
	}
}
//�̸��� ���� �� ����
int partition_Byname(Student * list[], int left, int right) {
	int pivot[10]; //�ǹ� ��
	Student * temp;
	int low, high;
	int i;

	low = left;
	high = right + 1;

	for (i = 0;i < 10;i++)
		pivot[i] = list[left]->name[i];

	do {
		do {
			low++;
			for (i = 0;i < 10;i++) { 
				if (list[low]->name[i] < pivot[i]) 
					break;
				else if (list[low]->name[i] > pivot[i]) 
					break;
			}
		} while (low < right && list[low]->name[i] < pivot[i]);
		do {
			high--;
			for (i = 0;i < 10;i++) {
				if (list[high]->name[i] > pivot[i])
					break;
				else if (list[high]->name[i] < pivot[i])
					break;
			}
		} while (high > left && list[high]->name[i] > pivot[i]);

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp); //���� ������ ���� ������ ��ġ�� �ǹ��� ��ȯ!
	return high; //�ǹ� ��ġ ��ȯ
}
void quick_sort_Byname(Student * list[], int left, int right) {
	if (left < right) {
		int q = partition_Byname(list, left, right);
		quick_sort_Byname(list, left, q - 1);
		quick_sort_Byname(list, q + 1, right);
	}
}
//�й��� ���� �� ����**
void adjust_Bystdnum(Student * a[], int root, int n) {
	int rootkey[9]; //�� ����� ��
	int child = root * 2; //�ڽ� �ε���
	int i,j, check;
	
	for (i = 0;i < 9;i++) 
		rootkey[i] = a[root]->stdnum[i];
	
	while (child <= n) {
		if (child < n) {
			for (i = 0;i < 9;i++)
				if (a[child]->stdnum[i] < a[child + 1]->stdnum[i]) { //������ �ڽİ� ���� �ڽ� ��
					child++;
					break;
				}
				else if (a[child]->stdnum[i] > a[child + 1]->stdnum[i])
					break;
		}
		check = 0;
		for (i = 0;i < 9;i++) {
			if (rootkey[i] > a[child]->stdnum[i]) {
				check = 1;
				break;  //1. �θ� �ڽĺ��� �� ũ�� �ݺ��� ������
			}
			else if(rootkey[i] < a[child]->stdnum[i]){ //2. �׷����ʰ� �ڽ��� �� ũ��
				for (j = 0;j < 9;j++)
					a[child / 2]->stdnum[j] = a[child]->stdnum[j]; //�θ� �ڽ� �� ����
				child *= 2; //�ڽ��� �ڽ����� ��������
				break;
			}
		}
		if (check) // if (rootkey[i] > a[child]->stdnum[i]) -> child *= 2 ������ �迭 ������ ��� a[child]�� �˻��ϱ� ����!!
			break; //1. �� ����� ���� �ڽĺ��� �� ũ�� while�ݺ��� ������
	}
	for(i=0;i<9;i++)
		a[child / 2]->stdnum[i] = rootkey[i]; // 1������ ����: �θ� �� ����� �� �ֱ�
									   	      // 2������ ����: �ڽĿ� �� ����� �� �ֱ�
}
void heapsort_Bystdnum(Student * a[], int n) {
	int i,j;
	Student * temp;

	for (i = n / 2;i > 0;i--)
		adjust_Bystdnum(a, i, n); //initial heap �����

	for (i = n - 1;i > 0; i--) {
		SWAP(a[1], a[i + 1], temp); //���� 1������ ���� �ؿ� �ִ� ���� ��ȯ
		adjust_Bystdnum(a, 1, i); //���� ū ������ ������(i) ����
	}
}
//�̸��� ���� �� ����
void adjust_Byname(Student * a[], int root, int n) {
	char rootkey[11]; //�� ����� ��
	int child = root * 2; //�ڽ� �ε���
	int i, j, check;

	strcpy(rootkey,a[root]->name);

	while (child <= n) {
		if (child < n) {
			for (i = 0;i < 10;i++)
				if (a[child]->name[i] < a[child + 1]->name[i]) { //������ �ڽİ� ���� �ڽ� ��
					child++;
					break;
				}
				else if (a[child]->name[i] > a[child + 1]->name[i])
					break;
		}
		check = 0;
		for (i = 0;i < 10;i++) {
			if (rootkey[i] > a[child]->name[i]) {
				check = 1;
				break;  //1. �θ� �ڽĺ��� �� ũ�� �ݺ��� ������
			}
			else if (rootkey[i] < a[child]->name[i]) { //2. �׷����ʰ� �ڽ��� �� ũ��
				for (j = 0;j < 10;j++)
					a[child / 2]->name[j] = a[child]->name[j]; //�θ� �ڽ� �� ����
				child *= 2; //�ڽ��� �ڽ����� ��������
				break;
			}
		}
		if (check) // if (rootkey[i] > a[child]->stdnum[i]) -> child *= 2 ������ �迭 ������ ��� a[child]�� �˻��ϱ� ����!!
			break; //1. �� ����� ���� �ڽĺ��� �� ũ�� while�ݺ��� ������
	}
	strcpy(a[child / 2]->name, rootkey); // 1������ ����: �θ� �� ����� �� �ֱ�
										 // 2������ ����: �ڽĿ� �� ����� �� �ֱ�
}
void heapsort_Byname(Student * a[], int n) {
	int i, j;
	Student * temp;

	for (i = n / 2;i > 0;i--)
		adjust_Byname(a, i, n); //initial heap �����

	for (i = n - 1;i > 0; i--) {
		SWAP(a[1], a[i + 1], temp); //���� 1������ ���� �ؿ� �ִ� ���� ��ȯ
		adjust_Byname(a, 1, i); //���� ū ������ ������(i) ����
	}
}

int main() {
	Student * a[1000], * a2[1000]; //����ü�� ����Ű�� '�������� �迭'(�ϳ��� �й� ����, �ٸ� �ϳ��� �̸� ����)
	Student * b[1000], * b2[1000]; //�� ����
	Student * c[1001], * c2[1001]; //�� ����(1�������� ����!)
	char again; //�ߺ� �˻縦 �������� �ؾ��ϴ°�
	clock_t start, finish; //���Ŀ� �ҿ�Ǵ� �ð� ���
	double duration;
	int i, j, x, y;

	for (i = 0;i < 1000;i++) {
		a[i] = malloc(sizeof(Student));
		a2[i] = a[i];
		b[i] = a[i];
		b2[i] = a[i];
		c[i + 1] = a[i];
		c2[i + 1] = a[i];
	}
	srand(time(NULL));
	//1000���� ���� ������ ����
	for (i = 0;i < 1000;i++) {
		again = 1;
		while (again) {  //<�й�>
			a[i]->stdnum[0] = 2; 
			a[i]->stdnum[1] = 0;
			a[i]->stdnum[2] = 1;
			a[i]->stdnum[3] = (rand() % 7) + 3;
			for (j = 4;j < 9;j++)
				a[i]->stdnum[j] = rand() % 10;
			
			again = 0;
			for (x = 0;x < i;x++) { //�ߺ� ������ �˻�
				for (y = 0;y < 9;y++) {
					if (a[x]->stdnum[y] != a[i]->stdnum[y])  //x��° ����ü���� �� ���ڶ� �ٸ���
						break; //y�ݺ��� ������
				}
				if (y == 10) { //x��° ����ü�� ���� ����ü�� ���ٸ�
					again = 1; //�ٽ� �й� ���ϱ�
					break; //x�ݺ����� ������
				} //���� �ٸ��ٸ� ���� ����ü �˻�
			}
		}//�й�
		again = 1;
		a[i]->name[10] = NULL; //���ڿ� �ʱ�ȭ
		while (again) {  //<�̸�>
			for (j = 0;j < 10;j++)
				a[i]->name[j] = (rand() % 26) + 65; //ascii code

			again = 0;
			for (x = 0;x < i;x++) { //'�ߺ� ������ �˻�'
				if (strcmp(a[x]->name, a[i]->name) == 0) { //x��° ����ü �й��� ������ ****
					again = 1; //�ٽ� �й� ���ϱ�
					break; //x�ݺ��� ������
				}
			}
		}//�̸�
		again = 1;
		while (again) {  //<��ȭ��ȣ>
			a[i]->phone[0] = 0;
			a[i]->phone[1] = 1;
			a[i]->phone[2] = 0;
			for (j = 3;j < 11;j++)
				a[i]->phone[j] = rand() % 10;

			again = 0;
			for (x = 0;x < i;x++) { //�ߺ� ������ �˻�
				for (y = 0;y < 11;y++) {
					if (a[x]->phone[y] != a[i]->phone[y])
						break; 
				}
				if (y == 10) { 
					again = 1; 
					break; 
				}
			}
		}//��ȭ��ȣ
	}//���� ������ ����
	
	printf("<���� ����>\n");
	start = clock();
	selection_sort_Bystdnum(a, 1000);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("1. �й��� �������� ����: %f�� �ɸ�\n",duration);

	for (i = 0;i < 1000;i += 25) { //1000���� �ʹ� ���Ƽ� 25�� �� ȭ�鿡 ���
		for (j = 0;j < 9;j++)
			printf("%d", a[i]->stdnum[j]);
		printf(" ");
		printf("%s ", a[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", a[i]->phone[j]);
		printf("\n");
	}

	start = clock();
	selection_sort_Byname(a2, 1000);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("2. �̸��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 0;i < 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", a2[i]->stdnum[j]);
		printf(" ");
		printf("%s ", a2[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", a2[i]->phone[j]);
		printf("\n");
	}

	printf("\n<�� ����>\n");
	start = clock();
	quick_sort_Bystdnum(b, 0, 999);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("1. �й��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 0;i < 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", b[i]->stdnum[j]);
		printf(" ");
		printf("%s ", b[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", b[i]->phone[j]);
		printf("\n");
	}

	start = clock();
	quick_sort_Byname(b2, 0, 999);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("2. �̸��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 0;i < 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", b2[i]->stdnum[j]);
		printf(" ");
		printf("%s ", b2[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", b2[i]->phone[j]);
		printf("\n");
	}

	printf("\n<�� ����>\n");
	start = clock();
	heapsort_Bystdnum(c, 1000);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("1. �й��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 1;i <= 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", c[i]->stdnum[j]);
		printf(" ");
		printf("%s ", c[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", c[i]->phone[j]);
		printf("\n");
	}

	start = clock();
	heapsort_Byname(c2, 1000);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("2. �̸��� �������� ����: %f�� �ɸ�\n", duration);

	for (i = 1;i <= 1000;i += 25) {
		for (j = 0;j < 9;j++)
			printf("%d", c2[i]->stdnum[j]);
		printf(" ");
		printf("%s ", c2[i]->name);
		for (j = 0;j < 11;j++)
			printf("%d", c2[i]->phone[j]);
		printf("\n");
	}
}