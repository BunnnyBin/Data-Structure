#include <stdio.h>
//팩토리얼
int factorial(int n)
{
	if (n == 0)      
		return 1;    // 0! = 1

	return n * factorial(n - 1);    // n과 factorial 함수에 n - 1을 넣어서 반환된 값을 곱함
}

//피보나치
int Fibo(int n) {
	if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else
		return Fibo(n - 1) + Fibo(n - 2);
}

//이진 탐색 알고리즘
int BSearchRecur(int ar[], int first, int last, int target) {
	int mid; 

	if (first > last)
		return -1; //찾는 대상이 없을 때
	
	mid = (first + last) / 2;  //찾는 구간의 중앙

	if (ar[mid] == target)  //찾는 대상이 중앙에 있을 때
		return mid;   //탐색완료!
	else if (ar[mid] < target) //중앙 값보다 찾는 대상이 더 클때
		return BSearchRecur(ar, mid + 1, last, target);
	else  //중앙 값보다 찾는 대상이 작을 때
		return BSearchRecur(ar, first, mid - 1, target);
}

int main()
{
	int array[8] = { 1,2,3,4,5,7,8,9 };
	int f = 0, l = 7; //first와 last(이진 탐색)
	int user = 7; //이진 탐색 때 찾는 대상
	int  i = 4;

	printf("%d! = %d\n",i, factorial(i)); //팩토리얼

	for (i = 0;i < 15;i++) {
		printf("%d ", Fibo(i+1));
	} //피보나치
	printf("\n");

	printf("%d는 %d번지에 있다.\n", user, BSearchRecur(array, f, l, user)); //이진 탐색
}