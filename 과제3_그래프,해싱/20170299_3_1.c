#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#define MAX_VERTEX 20
#define TRUE 1
#define FALSE 0
#define INF 1000 //���Ѵ� �Ÿ�

//���� ��ķ� �׷��� ����
typedef struct {
	int n; //���� ����
	int adj_mat[MAX_VERTEX][MAX_VERTEX];  //���� ���
	char metro[MAX_VERTEX][15];  //������ ��(����ö ��)
	int visited[MAX_VERTEX];     //�湮�� ���� ǥ�� - ���� �켱 Ž��
}GraphType;
//�׷��� �ʱ�ȭ
void InitGraph(GraphType* g) {
	g->n = 0; //���� ���� = 0
	for (int i = 0;i < MAX_VERTEX;i++) {
		g->metro[i][0] = NULL;  //null�� �ʱ�ȭ
		g->visited[i] = FALSE;

		for (int j = 0; j < MAX_VERTEX; j++)
			g->adj_mat[i][j] = 0;  //����Ǿ�� '1'
	}
}

void InsertEdge(GraphType * g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		printf("�߸��� �����Դϴ�.\n");
		exit(-1);
	}
	g->adj_mat[start][end] = 1; //��ũ ����
	g->adj_mat[end][start] = 1;
}

float weight[MAX_VERTEX][MAX_VERTEX] = {
{0,1.1,1.2,1.3,1.4,INF,INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
{1.1,0,INF, INF, INF, 1.5,1.6,INF,1.7,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF },
{1.2,INF, 0,INF, INF, INF, INF, INF, 1.8,INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
{1.3,INF, INF, 0,1.9,INF, INF, INF, INF, 2.1,INF, INF, INF, 2.2,INF, INF, INF, INF, INF, INF},
{1.4,INF, INF, 1.9,0, INF, INF, INF, INF, INF, 1.66,2.0,INF, INF, INF, INF, INF, INF, INF, INF},
{ INF, 1.5,INF, INF, INF, 0,INF, 1.23,INF, INF, INF, INF, 1.55,INF, INF, INF, INF, 1.98,INF, INF},
{ INF, 1.6,INF, INF, INF, INF, 0,INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.12,INF, INF},
{ INF, INF, INF, INF, INF, 1.23,INF, 0,INF, INF, INF, INF, 1.69,INF, INF, INF, INF, INF, INF, INF},
{ INF, 1.7,1.8,INF, INF, INF, INF, INF, 0,INF, INF, INF, INF, 2.23,INF, INF, INF, INF, INF, INF},
{ INF, INF, INF, 2.1,INF, INF, INF, INF, INF, 0,1.72,INF, INF, INF, 2.3,INF, INF, INF, INF, INF},
{ INF, INF, INF, INF, 1.66,INF, INF, INF, INF, 1.72,0,2.34,INF, INF, INF, 2.4,INF, INF, INF, INF},
{ INF, INF, INF, INF, 2.0,INF, INF, INF, INF, INF, 2.34,0,INF, INF, INF, INF, 2.5,INF, INF, INF},
{ INF, INF, INF, INF, INF, 1.55,INF, 1.69,INF, INF, INF, INF, 0,1.67,INF, INF, INF, 1.37,INF, INF},
{ INF, INF, INF, 2.2,INF, INF, INF, INF, 2.23,INF, INF, INF, 1.67,0,2.8,INF, INF, INF, 1.85,INF},
{ INF, INF, INF, INF, INF, INF, INF, INF, INF, 2.3,INF, INF, INF, 2.8,0,INF, INF, INF, 2.9,2.7},
{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2.4,INF, INF, INF, INF, 0,2.6,INF, INF, INF},
{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2.5,INF, INF, INF, 2.6,0,INF, INF, INF},
{ INF, INF, INF, INF, 1.98,1.12,INF, INF, INF, INF, INF, 1.37,INF, INF, INF, INF, 0,1.44,INF},
{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.85,2.9,INF, INF, 1.44,0,1.99},
{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2.7,INF, INF, INF, 1.99,0} };

float distance[MAX_VERTEX][2]; //�ִܰ��, ����� ������ ����
int found[MAX_VERTEX];    //�湮�� ������

//�ִܰ�� �˰����� �ִ� �Ÿ� �Լ�
int choose(float distance[][2], int n, int found[]) {
	int i, minpos;
	float min;
	min = INT_MAX;
	minpos = -1;
	for (i = 0;i < n;i++) {
		if (distance[i][0] < min && !found[i]) {
			min = distance[i][0];
			minpos = i;
		}
	}
	return minpos;
}
//�ִ� ��� ã�� �˰���
void shortest_path(int start, int n) {
	int i, u, w;
	for (i = 0;i < n;i++) { //�ʱ�ȭ
		distance[i][0] = weight[start][i];
		if(distance[i][0] != INF)
			distance[i][1] = start;
		found[i] = FALSE;
	}
	found[start] = TRUE; //������ �湮 ǥ��
	distance[start][0] = 0;

	for (i = 0;i < n - 2;i++) {
		u = choose(distance, n, found); //�湮���� ���� �� �� �ִ� �Ÿ��� ����u
		found[u] = TRUE;  //����u�� S���տ� ����
		for (w = 0;w < n;w++) //distance ������Ʈ
			if (!found[w])
				if (distance[u][0] + weight[u][w] < distance[w][0]) { // start���� ����ؼ� w�� �����ϴ� ���ڽ�(distance[w][0])�� �� ���
					distance[w][0] = distance[u][0] + weight[u][w];   //u�� �����ؼ� w�� �����ϴ� �Ÿ��� ������Ʈ!
					distance[w][1] = u;   //�������� ����
				}
	}
}
//���� �켱 Ž�� - ����ö �� ��ü Ž��(v�� ������)
void dif_mat(GraphType* g, int v) {
	int w;
	g->visited[v] = TRUE;
	printf("%s\n", g->metro[v]);   //�ش� ������ ����ö �� ���
	for (w = 0;w < g->n;w++) {
		if (g->adj_mat[v][w] && !g->visited[w])
			dif_mat(g, w);
	}
}

int main() {
	GraphType * g;
	char s_metro[15], d_metro[15];  //����� �Է��� �����, ������
	int start = -1, depart = -1; //��� ����, ���� ����
	int i;

	g = (GraphType*)malloc(sizeof(GraphType));
	InitGraph(g); //�׷��� �ʱ�ȭ
	//�� ������ ����ö ���̸� �Ҵ�
	strcpy(g->metro[0], "�뷮��");
	strcpy(g->metro[1], "���￪");
	strcpy(g->metro[2], "����");
	strcpy(g->metro[3], "���ǵ�");
	strcpy(g->metro[4], "�ű�");
	strcpy(g->metro[5], "���빮�������");
	strcpy(g->metro[6], "���");
	strcpy(g->metro[7], "���빮");
	strcpy(g->metro[8], "�ﰢ��");
	strcpy(g->metro[9], "���");
	strcpy(g->metro[10], "��������û");
	strcpy(g->metro[11], "�ŵ���");
	strcpy(g->metro[12], "����3��");
	strcpy(g->metro[13], "����");
	strcpy(g->metro[14], "����");
	strcpy(g->metro[15], "����");
	strcpy(g->metro[16], "��ġ��");
	strcpy(g->metro[17], "��û");
	strcpy(g->metro[18], "ȫ���Ա�");
	strcpy(g->metro[19], "�����н�Ƽ");
	g->n = 20;   //����ö �� 20��

	//���� �����ϱ�
	InsertEdge(g, 0, 1);
	InsertEdge(g, 0, 2);
	InsertEdge(g, 0, 3);
	InsertEdge(g, 0, 4);
	InsertEdge(g, 1, 5);
	InsertEdge(g, 1, 6);
	InsertEdge(g, 1, 8);
	InsertEdge(g, 2, 8);
	InsertEdge(g, 3, 9);
	InsertEdge(g, 3, 13);
	InsertEdge(g, 3, 4);
	InsertEdge(g, 4, 10);
	InsertEdge(g, 4, 11);
	InsertEdge(g, 5, 12);
	InsertEdge(g, 5, 7);
	InsertEdge(g, 5, 17);
	InsertEdge(g, 6, 17);
	InsertEdge(g, 7, 12);
	InsertEdge(g, 8, 13);
	InsertEdge(g, 9, 14);
	InsertEdge(g, 9, 10);
	InsertEdge(g, 10, 11);
	InsertEdge(g, 10, 15);
	InsertEdge(g, 11, 16);
	InsertEdge(g, 12, 13);
	InsertEdge(g, 12, 17);
	InsertEdge(g, 13, 14);
	InsertEdge(g, 13, 18);
	InsertEdge(g, 14, 18);
	InsertEdge(g, 14, 19);
	InsertEdge(g, 15, 16);
	InsertEdge(g, 17, 18);
	InsertEdge(g, 18, 19);

	printf("<<��� ���� ǥ���Ѵ�>> \n");
	dif_mat(g, 0);

	printf("\n��߿�: ");
	gets(s_metro);
	printf("������: ");
	gets(d_metro);
	for (i = 0;i < MAX_VERTEX;i++) 
		if (!strcmp(g->metro[i], s_metro)) {
			start = i;
			break;
		}
	for (i = 0;i < MAX_VERTEX;i++) 
		if (!strcmp(g->metro[i], d_metro)) {
			depart = i;
			break;
		}
	if (start == -1 || depart == -1) {
		printf("�� �̸� �߸� �Է��Ͽ����ϴ�.\n");
		exit(-1);
	}
	
	int path[MAX_VERTEX]; //��� - �Ųٷ���������
	for (i = 0;i < MAX_VERTEX;i++)
		path[i] = -1;  //�ʱ�ȭ
	shortest_path(start, g->n); //�ִܰ�� ���ϱ�

	path[0] = depart;
	path[1] = distance[depart][1];  //start -> depart���� ������ üũ
	i = 1;
	while (path[i] != start) {
		path[i + 1] = distance[path[i]][1];
		i++;
	} //�ݺ��� ������ path[i] == start
	while (i > 0)
		printf("%s - ", g->metro[path[i--]]);
	printf("%s (%.2f km)\n\n", g->metro[path[0]],distance[depart][0]);
}