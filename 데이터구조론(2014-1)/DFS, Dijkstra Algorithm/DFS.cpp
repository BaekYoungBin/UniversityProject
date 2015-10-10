#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<Windows.h>
#include<cstring>

#define Max_vetex 12								// 최대 정점 정의
typedef struct nodestruc *nodePointer ;
typedef struct nodestruc {
	int no;  // 정점 번호
	float cost;  // 이 간선의 비용가중치
	nodePointer link ;  // 연결리스트의 다음 노드에 대한 포인터
} ty_node ;


int Index;		
int arr[20];
nodePointer vertex[Max_vetex];  // 인접리스트의 헤더 노드 포인터들을 가지는 배열

void Shortest_Path_Print(int s, int t); // 최단거리 알고리즘 프린트
int choose(float distance[], int n, int found[]);	// 기존정점에서 다음정점중 가장 짧은 정점을 찾아 그 정점의 번호 리턴하는 함수
void Shortest_path_Dij ( int s,  int t  ) ; // 최단거리 알고리즘 실행/
void Read_and_make_graph();	// graph.txt에서 그래프 읽어서 인접리스트에 넣고 출력
int DFS_path ( int s, int t ); // 깊이탐색 알고리즘
float get_cost_of_arc(int v, int u);	// 간선의 비용을 구해주는 함수


float totalcost = 0;		// 총 비용
bool visited[Max_vetex];	//방문된 정점은 true 로 표시하는 flag	
float distance[Max_vetex];	// 최단거리 알고리즘에서 거리 배열
int found[Max_vetex];	//최단거리에서 flag
int a[10];				// 최단거리 알고리즘에서 이동 경로 저장하는 배열

int main(){
	char *token = NULL;			
	char *separator = " ,\n";
	int nodenum;
	int start;			// 시작정점
	int desti;			// 도착정점
	char sel[10];

	for(int i = 0; i<Max_vetex; i++){
		vertex[i] = (ty_node*)malloc(sizeof(ty_node));		// vertex 동적할당
	}

	Read_and_make_graph(); // 인접리스트 네모 화면출력
	while(1){
		printf("원하는 작업은( 작업명(d/s), 시작정점번호, 목적지정점번호 순으로 입력)?");
		gets(sel);	// 콘솔에서 한줄 읽어오기

		token = strtok(sel, separator);		// d 인지 s 인지 토큰에 받아오기
		if(token[0] == 'd')					// 깊이탐색의 경우
		{
			printf("경로 : ");
			printf("<");		
			token = strtok(NULL, separator);	// 토큰으로 잘라서 시작정점, 도착정점으로 나눈 후 DFS_path 함수에 넣는다.
			start = atoi(token);
			token = strtok(NULL, separator);
			desti = atoi(token);
			DFS_path(start, desti);
			totalcost = 0;
			for(int i = 0; i< Max_vetex; i++){	// 초기화
				visited[i] = false;
			}
		}
		else if(token[0] == 's')			// 최단거리 탐색의 경우
		{
			token = strtok(NULL, separator);
			start = atoi(token);
			token = strtok(NULL, separator);
			desti = atoi(token);
			Shortest_path_Dij(start, desti);		// 토큰으로 잘라서 시작정점, 도착정점으로 나눈후 Shortest_path_Dij함수에 넣는다.
			printf("최단 경로 비용 : %f\n", distance[desti]);
		}
		else if(token[0] == 'e')		// e 일경우 종료
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
	fp = fopen("graph.txt", "r");		// 경로의 파일을 읽어온다.
	fgets(printarray, sizeof(printarray), fp);// 한줄을 읽어온다.
	puts(printarray);	// 한줄을 그대로 출력한다.
	token = strtok(printarray, separator);	// 읽어온 한줄을 token단위로 나눈것중에 첫번째를 token 에 넣는다. (파일내용중 12)

	while(!feof(fp)){ // 파일의 끝일때까지 반복
		fgets(printarray, sizeof(printarray), fp);	// 다음 한줄을 읽어온다.
		puts(printarray);		// 한줄을 그대로 출력한다.
		token = strtok(printarray, separator);	// 읽어온 한줄을 token 단위로 나눈것중에 첫번째를 token 에 넣는다.
		p = vertex[i];	//nodepointer 인 p 에 vertex[i] 를 복사한다.
		p->no = atoi(token);	// p에 이 정점의 번호를 넣는다.
		p->cost = 0;	// 자기 자신을 가리키는 정점 즉 0->0의 비용은 0으로 한다.

		while(token = strtok(NULL, separator)){
			//	token = strtok(NULL, separator);
			q = (ty_node*)malloc(sizeof(ty_node));// 다음노드를 넣을 공간을 동적할당으로 만든다.
			q->no = atoi(token);	// 토큰의 다음 내용을 no로 둔다.
			p->link = q;		// p의 링크를 q 로 둔다.
			p= p->link;		// p를 p의 링크로 포인터 이동을 한다.
			token = strtok(NULL, separator);
			p->cost = atof(token);	// 비용을 넣는다.
		}
		p->link = NULL;
		i++;
	}

} 

int DFS_path ( int s, int t ) { 
	nodePointer p;

	visited[s] = true;
	//방문한 정점 true설정
	printf("%d,", s);
	// 정점 출력
	for(p = vertex[s]; p; p= p->link){	// p 가 null을 가리킬때까지 링크를 따라가며 반복
		if(!visited[p->no] && p->no != t){	// 만약 깊이탐색을 할 수 있는 조건이라면 탐색을 하면서 totalcost 에 탐색한 node의 cost를 더한다.
			totalcost = totalcost + p->cost;
			if(DFS_path(p->no, t) == 1)	// 만약 깊이탐색이 완료가 되면 최고깊이 노드는 1을 리턴하는데 backtracking 하면서 1을 리턴하면서 단계적으로 재귀함수를 종료한다.
				return 1;			
		}		
		if(p->no == t){	// 만약 깊이탐색이 완료된 경우
			totalcost = totalcost + p->cost;		// 마지막 정점의 cost까지 totalcost 에 추가한다.
			printf("%d", p->no);
			printf(">");
			printf("총 비용 : ");
			printf("%f\n", totalcost);			// 출력
			return 1;							// 완료 되었다고 1을 리턴하면서 함수를 종료한다.
		}	
	}
}
float get_cost_of_arc(int v, int u){		// 두 노드의 비용을 인접리스트를 활용해 구해주는 함수
	nodePointer w = vertex[v];
	while(w != NULL){
		if(w->no == u)
			return w->cost;				// 정점이 목적지일 경우 비용을 리턴한다.
		else
			w = w->link;					// 정점이 목적지가 아닐경우 링크를 타고간다.
	}
	return 10000;						// 정점이 인접리스트에 없을 경우 큰 수 10000을 리턴한다.
}
void Shortest_path_Dij ( int s,  int t  ) {		// 최단경로 탐색
	int i, u, w;
	int cnt = 0;
	for(i = 0; i<12; i++)
	{
		distance[i] = get_cost_of_arc(s, i);		// distance를 인접리스트를 활용해 넣는다.
		found[i] = FALSE;							// found 초기화
		if(distance[i]<10000)						
			a[i] = s;								// 일단 접근 가능한 distance인 경우 a[i] 에 넣는다.
	}

	found[s] = TRUE;	
	distance[s] = 0;
	a[cnt] = s;		// 첫번째 시작 정점을 정점탐색배열에 넣는다.
	cnt ++;			// index 증가

	for(i = 0; i<11; i++){
		u = choose(distance, 12, found);	// u 에 그 다음으로 가장가까운 정점을 찾아 넣는다.
		found[u] = TRUE;					// 그 u를 접근점으로 TRUE 를 설정한다.

		for(w = 0; w<12; w++){
			if(!found[w])					// 아직 탐색이 안된 정점들일 경우 기존점에서 w까지의 거리와 기존점에서 가까운점에서거리 + 가까운점에서 w까지의 거리를 비교한 후 바꾼다.
				if(distance[u] + get_cost_of_arc(u, w) < distance[w]){
					distance[w] = distance[u] + get_cost_of_arc(u, w);		
					a[w] = u;	// 정점 탐색배열에 정점을 넣는다.
				}		
		}
	}
	printf("<");
	Shortest_Path_Print(s, t);		// 정점탐색 출력
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
void Shortest_Path_Print(int s, int t) // 정점 탐색 출력하는 함수
{
	if(s != t){		// s가 도착점이 아닐경우
		Shortest_Path_Print(s, a[t]); // 재귀적으로 함수 호출
		printf("%d ", t);
		arr[Index] = t;
		Index++;
	}
	else{			// s가 도착점일경우
		printf("%d ", t);
		arr[Index] = t;
		Index++;
	}
}
int choose(float distance[], int n, int found[]){	// 책에 나온 코드
	int i, min, minpos;		
	min = 100000;		
	minpos = -1;
	for(i = 0; i<n; i++)
		if(distance[i] <min&& !found[i]){	// 가장 작은 distance를 찾아 index리턴한다.
			min = distance[i];
			minpos = i;
		}
		return minpos;
}