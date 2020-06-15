#define _CRT_SECURE_NO_WARNINGS
#define swap(x,y,t) ((t)=(x), (x)=(y),(y)=(t))
#include <stdio.h>

//순차 탐색 알고리즘
int Lsearch(int ar[], int len, int target) {
	int i;
	for (i = 0;i < len;i++) {
		if (ar[i] == target) 
			return i; //찾는 대상의 인덱스 값 반환
	}
	return -1; //찾는 대상이 없음을 의미하는 값 반환
}

//이진 탐색 알고리즘(단, 배열이 정렬되어 있어야함)
int Bsearch(int ar[], int len, int target) {
	int first = 0, last = len - 1, mid; //탐색 대상의 시작 인덱스 값, 탐색 대상의 마지막 인덱스 값

	while (first <= last) {
		mid = (first + last) / 2; //탐색 대상의 중앙을 찾는다

		if (ar[mid] == target) {  //중앙에 저장된 것이 타겟이라면
			return mid; //탐색 완료
		}
		else {  //타겟이 아니라면
			if (ar[mid] < target)
				first = mid + 1;
			else
				last = mid - 1;
		}
	}
	return -1;   //타겟을 못 찾을 때
}

//선택 정렬
void selection_sort(int list[], int n) {
	int i, j;
	int least, temp; //정렬되지 않은 구간의 맨 처음 위치
	
	for (i = 0;i < n - 1;i++) { //정렬되지 않은 구간의 처음 인덱스(i)
		least = i;

		for (j = i + 1;j < n;j++) 
			if (list[j] < list[least]) 
				least = j;   //정렬되지 않은 구간에서 가장 작은 값의 인덱스
		swap(list[i], list[least], temp);
	}
}
int main() {
	int array[8] = { 3,8,1,4,9,7,2,5 };
	int num = 8; //배열 길이
	int index; //찾는 대상 인덱스 저장
	int user;  //찾는 대상 값

	printf("찾는 값을 입력하시오.");
	scanf("%d", &user); //찾는 값 입력

	index = Lsearch(array, num, user); //순차 탐색 알고리즘
	printf("(순차 탐색 알고리즘) %d는 %d번지에 있다.\n", user, index);

	selection_sort(array, num);  //배열 정렬
	index = Bsearch(array, num, user); //이진 탐색 알고리즘
	printf("(이진 탐색 알고리즘) %d는 정렬된 배열의 %d번지에 있다.\n", user, index);
}