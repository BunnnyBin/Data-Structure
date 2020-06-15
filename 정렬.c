#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 8
#include <stdio.h>
int sorted[MAX_SIZE]; //합병 정렬의 결과물

//삽입 정렬
void insertion_sort(int list[], int n) {
	int i, j, key; //key: 끄집어내는 수

	for (i = 1;i < n;i++) { //key(1 ~ n-1번지)
		key = list[i];
		for (j = i-1;j >= 0;j--) { //정렬되어 있는 구간
			if (list[j] > key) //정렬되어 있는 구간의 한 구간이 key보다 크면
				list[j + 1] = list[j]; //그 구간을 앞으로 이동
			else
				break; //key보다 작으면 반복문 나가기
		}
		list[j + 1] = key; //key보다 작은 값 앞에다 key 넣기
	}
}
//삽입 정렬의 내림차순
void Invinsertion_sort(int list[], int n) { 
	int i, j, key; //key: 끄집어내는 수

	for (i = 1;i < n;i++) { //key
		key = list[i];
		for (j = i - 1;j >= 0;j--) { //정렬되어 있는 구간
			if (list[j] < key)  //정렬되어 있는 구간의 한 구간이 key보다 작으면
				list[j + 1] = list[j]; //그 구간을 앞으로 이동
			else
				break; //key보다 크면 반복문 나가기
		}
		list[j+1] = key; //key보다 큰 값 앞에다 key 넣기
	}
}
//버블 정렬 오름차순
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for(i=n-1;i>0;i--) //i = 맨 마지막 번지
		for (j = 0;j < i;j++) {
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
}
//버블 정렬 내림차순
void Invbubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1;i>0;i--) //i = 맨 마지막 번지
		for (j = 0;j < i;j++) {
			if (list[j] < list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
}
//선택 정렬
void selection_sort(int list[], int n) {
	int i, j, least, temp; //least는 제일 작은 수의 번지수

	for (i = 0;i < n - 1;i++) { //정렬되지 않은 구간의 첫 시작
		least = i;
		for (j = i+1;j < n;j++) { //least는 i번지 값이므로 i + 1부터 비교
			if (list[j] < list[least])
				least = j;
		}
		SWAP(list[least], list[i], temp); //한 차례 비교 끝나면 제일 작은 값(list[least])을 정렬되지 않은 구간의 첫 구간(i)에 옮기기 -> 정렬된 구간이 생김
	}
}
//합병 정렬
void merge(int list[], int left, int mid, int right) { //합병(정렬)
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	//각 블록의 시작인 i,j를 기준으로 비교
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++]; //더 작은 수를 결과배열에 저장
		else
			sorted[k++] = list[j++];
	}
	//요소가 남아있는 부분배열을 sorted로 복사
	if (i > mid) { // j블록이 남았으면
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else { //i블록이 남았으면
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// 배열 sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[],int left,int right) { //분할
	int mid;
	if (left < right) {//언제까지 분할?
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);

		merge(list, left, mid, right); //분할이 끝나면 '정렬'
	}
}
//퀵 정렬
int partition(int list[], int left, int right) {
	int pivot, temp; //피벗 값
	int low, high;  //피벗 보다 작은 범위 인덱스, 피벗보다 큰 범위 인덱스

	low = left;
	high = right + 1;
	pivot = list[left]; //배열의 제일 처음 값을 피벗으로 
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
	SWAP(list[left], list[high], temp); //피벗보가 작은 범위의 제일 끝 위치와 피벗과 교환!
	return high;
}
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right); //분할 -> 피벗보다 큰것, 작은것으로 정렬(피벗 위치 반환)
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//힙 정렬
void adjust(int a[], int root, int n) {
	int temp = a[root]; //맨 꼭대기 값을 삽입할 용도
	int rootkey = a[root]; //맨 꼭대기 값으로 비교할 용도
	int child = root * 2; //자식 인덱스

	while (child <= n) {
		if (child < n && a[child] < a[child + 1])
			child++; //오른쪽 자식과 왼쪽 자식 비교
		
		if (rootkey > a[child])
			break;  //1. 맨 꼭대기 값이 자식보다 더 크면 반복문 나가기
		else { //2. 그렇지않고 자식이 더 크면
			a[child / 2] = a[child]; //부모에 자식 값 대입
			child *= 2; //자식의 자식으로 내려가기
		}
	}
	a[child / 2] = temp; // 1번인 경우: 부모에 맨 꼭대기 값 넣기
	                     // 2번인 경우: 자식에 맨 꼭대기 값 넣기
}
void heapsort(int a[], int n) {
	int i;
	int temp;

	for (i = n / 2;i > 0;i--)
		adjust(a, i, n); //initial heap 만들기

	for (i = n - 1;i > 0; i--) {
		SWAP(a[1], a[i + 1], temp); //힙의 1번지와 제일 밑에 있는 수와 교환
		adjust(a, 1, i); //i: 가장 큰 수들을 제외한 갯수
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
	printf("삽입 정렬 오름차순 >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array1[i]);
	printf("\n");

	Invinsertion_sort(array2, num);
	printf("삽입 정렬 내림차순 >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array2[i]);
	printf("\n");

	bubble_sort(array3, num);
	printf("버블 정렬 오름차순 >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array3[i]);
	printf("\n");

	Invbubble_sort(array4, num);
	printf("버블 정렬 내림차순 >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array4[i]);
	printf("\n");

	selection_sort(array5, num);
	printf("선택 정렬 >> ");
	for (i = 0;i < num;i++)
		printf("%d ", array5[i]);
	printf("\n");

	merge_sort(list, 0, 7);
	printf("합병 정렬 >> ");
	for (i = 0;i < 8;i++)
		printf("%d ", list[i]);
	printf("\n");

	quick_sort(list2, 0, 8);
	printf("퀵 정렬 >> ");
	for (i = 0;i < 9;i++)
		printf("%d ", list2[i]);
	printf("\n");

	heapsort(a, 10);
	printf("힙 정렬 >> ");
	for (i = 1;i < 11;i++)
		printf("%d ", a[i]);
	printf("\n");
}