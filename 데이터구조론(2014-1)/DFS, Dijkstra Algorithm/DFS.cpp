#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<Windows.h>
#include<cstring>

#define Max_vetex 12								// �ִ� ���� ����
typedef struct nodestruc *nodePointer ;
typedef struct nodestruc {
	int no;  // ���� ��ȣ
	float cost;  // �� ������ ��밡��ġ
	nodePointer link ;  // ���Ḯ��Ʈ�� ���� ��忡 ���� ������
} ty_node ;


int Index;		
int arr[20];
nodePointer vertex[Max_vetex];  // ��������Ʈ�� ��� ��� �����͵��� ������ �迭

void Shortest_Path_Print(int s, int t); // �ִܰŸ� �˰��� ����Ʈ
int choose(float distance[], int n, int found[]);	// ������������ ���������� ���� ª�� ������ ã�� �� ������ ��ȣ �����ϴ� �Լ�
void Shortest_path_Dij ( int s,  int t  ) ; // �ִܰŸ� �˰��� ����/
void Read_and_make_graph();	// graph.txt���� �׷��� �о ��������Ʈ�� �ְ� ���
int DFS_path ( int s, int t ); // ����Ž�� �˰���
float get_cost_of_arc(int v, int u);	// ������ ����� �����ִ� �Լ�


float totalcost = 0;		// �� ���
bool visited[Max_vetex];	//�湮�� ������ true �� ǥ���ϴ� flag	
float distance[Max_vetex];	// �ִܰŸ� �˰��򿡼� �Ÿ� �迭
int found[Max_vetex];	//�ִܰŸ����� flag
int a[10];				// �ִܰŸ� �˰��򿡼� �̵� ��� �����ϴ� �迭

int main(){
	char *token = NULL;			
	char *separator = " ,\n";
	int nodenum;
	int start;			// ��������
	int desti;			// ��������
	char sel[10];

	for(int i = 0; i<Max_vetex; i++){
		vertex[i] = (ty_node*)malloc(sizeof(ty_node));		// vertex �����Ҵ�
	}

	Read_and_make_graph(); // ��������Ʈ �׸� ȭ�����
	while(1){
		printf("���ϴ� �۾���( �۾���(d/s), ����������ȣ, ������������ȣ ������ �Է�)?");
		gets(sel);	// �ֿܼ��� ���� �о����

		token = strtok(sel, separator);		// d ���� s ���� ��ū�� �޾ƿ���
		if(token[0] == 'd')					// ����Ž���� ���
		{
			printf("��� : ");
			printf("<");		
			token = strtok(NULL, separator);	// ��ū���� �߶� ��������, ������������ ���� �� DFS_path �Լ��� �ִ´�.
			start = atoi(token);
			token = strtok(NULL, separator);
			desti = atoi(token);
			DFS_path(start, desti);
			totalcost = 0;
			for(int i = 0; i< Max_vetex; i++){	// �ʱ�ȭ
				visited[i] = false;
			}
		}
		else if(token[0] == 's')			// �ִܰŸ� Ž���� ���
		{
			token = strtok(NULL, separator);
			start = atoi(token);
			token = strtok(NULL, separator);
			desti = atoi(token);
			Shortest_path_Dij(start, desti);		// ��ū���� �߶� ��������, ������������ ������ Shortest_path_Dij�Լ��� �ִ´�.
			printf("�ִ� ��� ��� : %f\n", distance[desti]);
		}
		else if(token[0] == 'e')		// e �ϰ�� ����
		{
			exit(0);
		}

	}

}
void Read_and_make_graph(){
	char printarray[100];
	char *token = NULL;			
	nodePointer p;
	nodePointer q;
	char *separator = " ,\n";
	int i= 0;

	FILE *fp;
	fp = fopen("graph.txt", "r");		// ����� ������ �о�´�.
	fgets(printarray, sizeof(printarray), fp);// ������ �о�´�.
	puts(printarray);	// ������ �״�� ����Ѵ�.
	token = strtok(printarray, separator);	// �о�� ������ token������ �������߿� ù��°�� token �� �ִ´�. (���ϳ����� 12)

	while(!feof(fp)){ // ������ ���϶����� �ݺ�
		fgets(printarray, sizeof(printarray), fp);	// ���� ������ �о�´�.
		puts(printarray);		// ������ �״�� ����Ѵ�.
		token = strtok(printarray, separator);	// �о�� ������ token ������ �������߿� ù��°�� token �� �ִ´�.
		p = vertex[i];	//nodepointer �� p �� vertex[i] �� �����Ѵ�.
		p->no = atoi(token);	// p�� �� ������ ��ȣ�� �ִ´�.
		p->cost = 0;	// �ڱ� �ڽ��� ����Ű�� ���� �� 0->0�� ����� 0���� �Ѵ�.

		while(token = strtok(NULL, separator)){
			//	token = strtok(NULL, separator);
			q = (ty_node*)malloc(sizeof(ty_node));// ������带 ���� ������ �����Ҵ����� �����.
			q->no = atoi(token);	// ��ū�� ���� ������ no�� �д�.
			p->link = q;		// p�� ��ũ�� q �� �д�.
			p= p->link;		// p�� p�� ��ũ�� ������ �̵��� �Ѵ�.
			token = strtok(NULL, separator);
			p->cost = atof(token);	// ����� �ִ´�.
		}
		p->link = NULL;
		i++;
	}

} 

int DFS_path ( int s, int t ) { 
	nodePointer p;

	visited[s] = true;
	//�湮�� ���� true����
	printf("%d,", s);
	// ���� ���
	for(p = vertex[s]; p; p= p->link){	// p �� null�� ����ų������ ��ũ�� ���󰡸� �ݺ�
		if(!visited[p->no] && p->no != t){	// ���� ����Ž���� �� �� �ִ� �����̶�� Ž���� �ϸ鼭 totalcost �� Ž���� node�� cost�� ���Ѵ�.
			totalcost = totalcost + p->cost;
			if(DFS_path(p->no, t) == 1)	// ���� ����Ž���� �Ϸᰡ �Ǹ� �ְ���� ���� 1�� �����ϴµ� backtracking �ϸ鼭 1�� �����ϸ鼭 �ܰ������� ����Լ��� �����Ѵ�.
				return 1;			
		}		
		if(p->no == t){	// ���� ����Ž���� �Ϸ�� ���
			totalcost = totalcost + p->cost;		// ������ ������ cost���� totalcost �� �߰��Ѵ�.
			printf("%d", p->no);
			printf(">");
			printf("�� ��� : ");
			printf("%f\n", totalcost);			// ���
			return 1;							// �Ϸ� �Ǿ��ٰ� 1�� �����ϸ鼭 �Լ��� �����Ѵ�.
		}	
	}
}
float get_cost_of_arc(int v, int u){		// �� ����� ����� ��������Ʈ�� Ȱ���� �����ִ� �Լ�
	nodePointer w = vertex[v];
	while(w != NULL){
		if(w->no == u)
			return w->cost;				// ������ �������� ��� ����� �����Ѵ�.
		else
			w = w->link;					// ������ �������� �ƴҰ�� ��ũ�� Ÿ����.
	}
	return 10000;						// ������ ��������Ʈ�� ���� ��� ū �� 10000�� �����Ѵ�.
}
void Shortest_path_Dij ( int s,  int t  ) {		// �ִܰ�� Ž��
	int i, u, w;
	int cnt = 0;
	for(i = 0; i<12; i++)
	{
		distance[i] = get_cost_of_arc(s, i);		// distance�� ��������Ʈ�� Ȱ���� �ִ´�.
		found[i] = FALSE;							// found �ʱ�ȭ
		if(distance[i]<10000)						
			a[i] = s;								// �ϴ� ���� ������ distance�� ��� a[i] �� �ִ´�.
	}

	found[s] = TRUE;	
	distance[s] = 0;
	a[cnt] = s;		// ù��° ���� ������ ����Ž���迭�� �ִ´�.
	cnt ++;			// index ����

	for(i = 0; i<11; i++){
		u = choose(distance, 12, found);	// u �� �� �������� ���尡��� ������ ã�� �ִ´�.
		found[u] = TRUE;					// �� u�� ���������� TRUE �� �����Ѵ�.

		for(w = 0; w<12; w++){
			if(!found[w])					// ���� Ž���� �ȵ� �������� ��� ���������� w������ �Ÿ��� ���������� ������������Ÿ� + ����������� w������ �Ÿ��� ���� �� �ٲ۴�.
				if(distance[u] + get_cost_of_arc(u, w) < distance[w]){
					distance[w] = distance[u] + get_cost_of_arc(u, w);		
					a[w] = u;	// ���� Ž���迭�� ������ �ִ´�.
				}		
		}
	}
	printf("<");
	Shortest_Path_Print(s, t);		// ����Ž�� ���
	printf(">");

	/*
	printf("<");
	for(int i = 0; i<=cnt; i++)
	{
	printf("%d ",a[i]); 
	}
	printf(">\n");
	*/
}
void Shortest_Path_Print(int s, int t) // ���� Ž�� ����ϴ� �Լ�
{
	if(s != t){		// s�� �������� �ƴҰ��
		Shortest_Path_Print(s, a[t]); // ��������� �Լ� ȣ��
		printf("%d ", t);
		arr[Index] = t;
		Index++;
	}
	else{			// s�� �������ϰ��
		printf("%d ", t);
		arr[Index] = t;
		Index++;
	}
}
int choose(float distance[], int n, int found[]){	// å�� ���� �ڵ�
	int i, min, minpos;		
	min = 100000;		
	minpos = -1;
	for(i = 0; i<n; i++)
		if(distance[i] <min&& !found[i]){	// ���� ���� distance�� ã�� index�����Ѵ�.
			min = distance[i];
			minpos = i;
		}
		return minpos;
}