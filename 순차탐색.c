#define _CRT_SECURE_NO_WARNINGS
#define swap(x,y,t) ((t)=(x), (x)=(y),(y)=(t))
#include <stdio.h>

//���� Ž�� �˰���
int Lsearch(int ar[], int len, int target) {
	int i;
	for (i = 0;i < len;i++) {
		if (ar[i] == target) 
			return i; //ã�� ����� �ε��� �� ��ȯ
	}
	return -1; //ã�� ����� ������ �ǹ��ϴ� �� ��ȯ
}

//���� Ž�� �˰���(��, �迭�� ���ĵǾ� �־����)
int Bsearch(int ar[], int len, int target) {
	int first = 0, last = len - 1, mid; //Ž�� ����� ���� �ε��� ��, Ž�� ����� ������ �ε��� ��

	while (first <= last) {
		mid = (first + last) / 2; //Ž�� ����� �߾��� ã�´�

		if (ar[mid] == target) {  //�߾ӿ� ����� ���� Ÿ���̶��
			return mid; //Ž�� �Ϸ�
		}
		else {  //Ÿ���� �ƴ϶��
			if (ar[mid] < target)
				first = mid + 1;
			else
				last = mid - 1;
		}
	}
	return -1;   //Ÿ���� �� ã�� ��
}

//���� ����
void selection_sort(int list[], int n) {
	int i, j;
	int least, temp; //���ĵ��� ���� ������ �� ó�� ��ġ
	
	for (i = 0;i < n - 1;i++) { //���ĵ��� ���� ������ ó�� �ε���(i)
		least = i;

		for (j = i + 1;j < n;j++) 
			if (list[j] < list[least]) 
				least = j;   //���ĵ��� ���� �������� ���� ���� ���� �ε���
		swap(list[i], list[least], temp);
	}
}
int main() {
	int array[8] = { 3,8,1,4,9,7,2,5 };
	int num = 8; //�迭 ����
	int index; //ã�� ��� �ε��� ����
	int user;  //ã�� ��� ��

	printf("ã�� ���� �Է��Ͻÿ�.");
	scanf("%d", &user); //ã�� �� �Է�

	index = Lsearch(array, num, user); //���� Ž�� �˰���
	printf("(���� Ž�� �˰���) %d�� %d������ �ִ�.\n", user, index);

	selection_sort(array, num);  //�迭 ����
	index = Bsearch(array, num, user); //���� Ž�� �˰���
	printf("(���� Ž�� �˰���) %d�� ���ĵ� �迭�� %d������ �ִ�.\n", user, index);
}