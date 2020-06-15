#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 8
#include <stdio.h>
int sorted[MAX_SIZE]; //�պ� ������ �����

//���� ����
void insertion_sort(int list[], int n) {
	int i, j, key; //key: ������� ��

	for (i = 1;i < n;i++) { //key(1 ~ n-1����)
		key = list[i];
		for (j = i-1;j >= 0;j--) { //���ĵǾ� �ִ� ����
			if (list[j] > key) //���ĵǾ� �ִ� ������ �� ������ key���� ũ��
				list[j + 1] = list[j]; //�� ������ ������ �̵�
			else
				break; //key���� ������ �ݺ��� ������
		}
		list[j + 1] = key; //key���� ���� �� �տ��� key �ֱ�
	}
}
//���� ������ ��������
void Invinsertion_sort(int list[], int n) { 
	int i, j, key; //key: ������� ��

	for (i = 1;i < n;i++) { //key
		key = list[i];
		for (j = i - 1;j >= 0;j--) { //���ĵǾ� �ִ� ����
			if (list[j] < key)  //���ĵǾ� �ִ� ������ �� ������ key���� ������
				list[j + 1] = list[j]; //�� ������ ������ �̵�
			else
				break; //key���� ũ�� �ݺ��� ������
		}
		list[j+1] = key; //key���� ū �� �տ��� key �ֱ�
	}
}
//���� ���� ��������
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for(i=n-1;i>0;i--) //i = �� ������ ����
		for (j = 0;j < i;j++) {
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
}
//���� ���� ��������
void Invbubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1;i>0;i--) //i = �� ������ ����
		for (j = 0;j < i;j++) {
			if (list[j] < list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
}
//���� ����
void selection_sort(int list[], int n) {
	int i, j, least, temp; //least�� ���� ���� ���� ������

	for (i = 0;i < n - 1;i++) { //���ĵ��� ���� ������ ù ����
		least = i;
		for (j = i+1;j < n;j++) { //least�� i���� ���̹Ƿ� i + 1���� ��
			if (list[j] < list[least])
				least = j;
		}
		SWAP(list[least], list[i], temp); //�� ���� �� ������ ���� ���� ��(list[least])�� ���ĵ��� ���� ������ ù ����(i)�� �ű�� -> ���ĵ� ������ ����
	}
}
//�պ� ����
void merge(int list[], int left, int mid, int right) { //�պ�(����)
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	//�� ����� ������ i,j�� �������� ��
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++]; //�� ���� ���� ����迭�� ����
		else
			sorted[k++] = list[j++];
	}
	//��Ұ� �����ִ� �κй迭�� sorted�� ����
	if (i > mid) { // j����� ��������
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else { //i����� ��������
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// �迭 sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[],int left,int right) { //����
	int mid;
	if (left < right) {//�������� ����?
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);

		merge(list, left, mid, right); //������ ������ '����'
	}
}
//�� ����
int partition(int list[], int left, int right) {
	int pivot, temp; //�ǹ� ��
	int low, high;  //�ǹ� ���� ���� ���� �ε���, �ǹ����� ū ���� �ε���

	low = left;
	high = right + 1;
	pivot = list[left]; //�迭�� ���� ó�� ���� �ǹ����� 
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp); //�ǹ����� ���� ������ ���� �� ��ġ�� �ǹ��� ��ȯ!
	return high;
}
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right); //���� -> �ǹ����� ū��, ���������� ����(�ǹ� ��ġ ��ȯ)
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//�� ����
void adjust(int a[], int root, int n) {
	int temp = a[root]; //�� ����� ���� ������ �뵵
	int rootkey = a[root]; //�� ����� ������ ���� �뵵
	int child = root * 2; //�ڽ� �ε���

	while (child <= n) {
		if (child < n && a[child] < a[child + 1])
			child++; //������ �ڽİ� ���� �ڽ� ��
		
		if (rootkey > a[child])
			break;  //1. �� ����� ���� �ڽĺ��� �� ũ�� �ݺ��� ������
		else { //2. �׷����ʰ� �ڽ��� �� ũ��
			a[child / 2] = a[child]; //�θ� �ڽ� �� ����
			child *= 2; //�ڽ��� �ڽ����� ��������
		}
	}
	a[child / 2] = temp; // 1���� ���: �θ� �� ����� �� �ֱ�
	                     // 2���� ���: �ڽĿ� �� ����� �� �ֱ�
}
void heapsort(int a[], int n) {
	int i;
	int temp;

	for (i = n / 2;i > 0;i--)
		adjust(a, i, n); //initial heap �����

	for (i = n - 1;i > 0; i--) {
		SWAP(a[1], a[i + 1], temp); //���� 1������ ���� �ؿ� �ִ� ���� ��ȯ
		adjust(a, 1, i); //i: ���� ū ������ ������ ����
	}
}
int main() {
	int array1[6] = { 5,3,8,1,2,7 };
	int array2[6] = { 5,3,8,1,2,7 };
	int array3[6] = { 5,3,8,1,2,7 };
	int array4[6] = { 5,3,8,1,2,7 };
	int array5[6] = { 5,3,8,1,2,7 };
	int list[8] = { 27,10,12,20,25,13,15,22 };
	int list2[9] = { 5,3,8,4,9,1,6,2,7 };
	int a[11] = { -1,26,5,77,1,61,11,59,15,48,19 };
	int num = 6;
	int i;

	insertion_sort(array1, num);
	printf("���� ���� �������� >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array1[i]);
	printf("\n");

	Invinsertion_sort(array2, num);
	printf("���� ���� �������� >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array2[i]);
	printf("\n");

	bubble_sort(array3, num);
	printf("���� ���� �������� >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array3[i]);
	printf("\n");

	Invbubble_sort(array4, num);
	printf("���� ���� �������� >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array4[i]);
	printf("\n");

	selection_sort(array5, num);
	printf("���� ���� >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array5[i]);
	printf("\n");

	merge_sort(list, 0, 7);
	printf("�պ� ���� >> ");
	for (i = 0;i < 8;i++)
		printf("%d ", list[i]);
	printf("\n");

	quick_sort(list2, 0, 8);
	printf("�� ���� >> ");
	for (i = 0;i < 9;i++)
		printf("%d ", list2[i]);
	printf("\n");

	heapsort(a, 10);
	printf("�� ���� >> ");
	for (i = 1;i < 11;i++)
		printf("%d ", a[i]);
	printf("\n");
}