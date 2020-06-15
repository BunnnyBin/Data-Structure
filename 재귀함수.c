#include <stdio.h>
//���丮��
int factorial(int n)
{
	if (n == 0)      
		return 1;    // 0! = 1

	return n * factorial(n - 1);    // n�� factorial �Լ��� n - 1�� �־ ��ȯ�� ���� ����
}

//�Ǻ���ġ
int Fibo(int n) {
	if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else
		return Fibo(n - 1) + Fibo(n - 2);
}

//���� Ž�� �˰���
int BSearchRecur(int ar[], int first, int last, int target) {
	int mid; 

	if (first > last)
		return -1; //ã�� ����� ���� ��
	
	mid = (first + last) / 2;  //ã�� ������ �߾�

	if (ar[mid] == target)  //ã�� ����� �߾ӿ� ���� ��
		return mid;   //Ž���Ϸ�!
	else if (ar[mid] < target) //�߾� ������ ã�� ����� �� Ŭ��
		return BSearchRecur(ar, mid + 1, last, target);
	else  //�߾� ������ ã�� ����� ���� ��
		return BSearchRecur(ar, first, mid - 1, target);
}

int main()
{
	int array[8] = { 1,2,3,4,5,7,8,9 };
	int f = 0, l = 7; //first�� last(���� Ž��)
	int user = 7; //���� Ž�� �� ã�� ���
	int  i = 4;

	printf("%d! = %d\n",i, factorial(i)); //���丮��

	for (i = 0;i < 15;i++) {
		printf("%d ", Fibo(i+1));
	} //�Ǻ���ġ
	printf("\n");

	printf("%d�� %d������ �ִ�.\n", user, BSearchRecur(array, f, l, user)); //���� Ž��
}