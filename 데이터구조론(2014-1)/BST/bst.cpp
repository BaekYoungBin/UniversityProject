#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<Windows.h>
#include<cstring>


#define MAX_QUEUE_SIZE 100
typedef struct astr {
	int key;				// 학번
	char name[50];			// 이름
} element ;
typedef struct anod * Ty_Node_Ptr  ;
typedef struct anod {
	element data ;								 // 노드의 데이타 부분
	Ty_Node_Ptr leftChild, rightChild ;			// 노드의 좌측, 우측 자식에 대한 포인터
} Ty_Node ; 

void error(char *message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}


FILE *fp;

void insert_from_file(Ty_Node **root);										// 화일의 내용을 전체 내용을 넣는 함수
void insert_anode(Ty_Node **root, element data);							// 새로운 데이터를 하나 받아서 노드로 만들어 BST에 추가하는 함수
void delete_anode(Ty_Node *root, char name[]);								// BST 를 탐색하여 주어진 이름을 가진 노드를 삭제하는 함수
Ty_Node* search_anode(Ty_Node *root, char a[]);								// BST 를 탐색해서 주어진 이름을 가진 노드를 return 하는 함수
int get_level(Ty_Node *root, char a[]);										// BST 를 탐색해서 주어진 이름을 가진 노드의 높이를 출력하는 함수
void get_sibling(Ty_Node *root, char a[]);									// BST 를 탐색해서 주어진 이름을 가진 노드의 형제노드를 출력하는 함수
int get_height(Ty_Node *root);												// BST 를 탐색해서 전체 높이를 출력하는 함수
void inorder(Ty_Node *root);												// BST 를 중위순회 방식으로 출력하는 함수
int cnt;																	// 중위순회 방식으로 출력 할 때 이해를 돕기 위해 그 노드의 레벨을 출력하기 위해 쓰는 전역변수
int main(){
	Ty_Node *root= NULL;
	Ty_Node *p = NULL;
	char fpath[100];
	char order[100];
	element data;
	char a[100];
	char *token = NULL;
	char *token1 = NULL;
	char *separator = " ,\n";
	int level = 0;
	printf("파일 이름이 뭐인가요?\n");								
	scanf("%s", &fpath);													// 파일이름 입력


	fp = fopen(fpath, "r");	
	if(fp){																	// 파일이름이 존재할 때

		insert_from_file(&root);											// 파일로부터 노드 삽입
		while(1){
			printf("명령어를 입력하세요\n");
			fflush(stdin);													// scanf 버퍼 비우기
			scanf("%[^\n]s", &order);										// scanf 를 마치 gets 처럼 공백 무시하고 \n 까지 읽어들이는 방법
			token = strtok(order, separator);								// token 을 이용해 단어 분할
			switch(token[0]){												// 첫번째 명령어 부분을 switch 에 넣어 사용 case는 아스키코드값으로 

			case 105 :	// i
				token = strtok(NULL, separator);
				strcpy(data.name, token); 
				token = strtok(NULL, separator);
				data.key = atoi(token);
				insert_anode(&root, data);									// 추가정보를 data에 넣어서 노드에 삽입
				break;
			case 112 : 
				// p
				inorder(root);												// 중위순회방식으로 출력
				break;
			case 100 :  // d
				token = strtok(NULL, separator);
				delete_anode(root, token);									// 삭제
				break;
			case 115 :  // s
				token = strtok(NULL, separator);
				p = search_anode(root, token);								// 해당 키값의 노드정보 출력
				if(p !=NULL)
					printf("%s %d\n", p->data.name, p->data.key); 
				else
					printf("%s을 찾을 수 없습니다\n", token);
				break;
			case 118 :  // v
				token = strtok(NULL, separator);
				level = get_level(root, token);								// 해당 키값의 노드 높이 출력
				if(level !=0)
					printf("%s의 높이 : %d\n", token, level);
				else
					printf("%s을 찾을 수 없습니다\n", token);

				break;
			case 98 :  // b
				token = strtok(NULL, separator);
				get_sibling(root, token);									// 해당 키값의 노드 형제 출력
				break;
			case 104 : // h
				level = get_height(root);									// 높이 출력
				if(level !=NULL)
					printf("높이 : %d\n", level);
				break;
			case 101 : exit(0);												// 종료


			}
		}
	}
	else
	{
		printf("file 이름을 찾을 수 없습니다\n");
	}
}

void insert_from_file(Ty_Node **root){
	char sentence[100];
	element data;
	while(!feof(fp)){														// 파일의 끝까지 반복
		fgets(sentence, sizeof(sentence), fp);								// sentence에 한줄을 입력받음
		char *token = NULL;													
		char *separator = " ,\n";
		token = strtok(sentence, separator);								// strtok 를 통해 한줄을 단어로 분할
		data.key = atoi(token);											
		token = strtok(NULL, separator);									
		strcpy(data.name, token);											// element 자료형의 데이타에 key 와 name 을 token 을 통해 분리된 정보를 넣어준다.
		insert_anode(root, data);											// data를 노드에 삽입
	}
}
void insert_anode(Ty_Node **root, element data){							
	Ty_Node *p, *t;	// p는 부모노드, t는 현재노드
	Ty_Node *n;	// n은 새로운 노드
	n = (Ty_Node*)malloc(sizeof(Ty_Node));									// 동적할당

	if(n == NULL)
		return;

	n->data.key =data.key; 

	strcpy(n->data.name, data.name);
	n->leftChild = NULL;
	n->rightChild = NULL;													// 새로운 노드 생성

	t = *root;
	p = NULL;

	while(t != NULL)
	{
		if(strcmp(n->data.name, t->data.name) == 0) 
			return ;
		p = t;
		if(strcmp(n->data.name, p->data.name) < 0)
			t = p->leftChild;
		else
			t = p->rightChild;

	}																		 // 적당한 위치 탐색하는 작업

	if(p != NULL)
		if(strcmp(n->data.name, p->data.name) < 0)							// 삽입하는 작업
			p->leftChild = n;
		else
			p->rightChild = n;
	else																	// p가 NULL 일 경우는 가장 첫번째경우로 새/ 노드를 root 로 만든다
		*root = n;

}
void delete_anode(Ty_Node *root, char name[])				
{
	Ty_Node *p, *child, *succ, *succ_p, *t;

	// key를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = root;
	while( t != NULL && (strcmp(t->data.name, name) !=0 )){
		p = t;
		t = ( strcmp(name, t->data.name) == -1 ) ? t->leftChild : t->rightChild;
	}
	if( t == NULL ) { 														// 탐색트리에 없는 키
		printf("key is not in the tree");
		return;
	}
																			// 단말노드인 경우
	if( (t->leftChild==NULL) && (t->rightChild==NULL) ){ 
		if( p->leftChild == t ) 
			p->leftChild = NULL;
		else   p->rightChild = NULL;
	}
																			// 하나의 자식만 가지는 경우
	else if((t->leftChild==NULL)||(t->rightChild==NULL)){
		child = (t->leftChild != NULL) ? t->leftChild : t->rightChild;
		if( p->leftChild == t ) 
			p->leftChild = child;
		else p->rightChild = child;
	}
	else{																	// 두개의 자식을 가지는 경우 
		succ = t->rightChild;
		while(succ->leftChild != NULL){
			succ_p = succ;
			succ = succ->leftChild;
		}
		if( succ_p->leftChild == succ )
			succ_p->leftChild = succ->rightChild;
		else 
			succ_p->rightChild = succ->rightChild;
		strcpy(t->data.name , succ->data.name);
		t->data.key = succ->data.key;
		t = succ;
	}
	free(t);																// 노드 삭제
}

Ty_Node* search_anode(Ty_Node* root, char a[]){								// 주어진 key 값의 노드 정보 출력
	Ty_Node *p = root;

	while(p !=NULL){
		if(strcmp(a, p->data.name) == 0)
			return p;													// 노드를 찾았을 시 그 노드 반환
		else if(strcmp(a, p->data.name) == -1 )
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	return p;															// 노드가 없을시 NULL을 가진 p 반환
}
int get_level(Ty_Node *root, char a[]){									// 주어진 key 값의 노드 레벨 출력
	Ty_Node *p = root;	
	int count = 1;														// 지역변수 cnt
	while(p !=NULL){
		if(strcmp(a, p->data.name) == 0)
			return count;													// 노드를 찾았을 시 그 노드의 cnt 반환
		else if(strcmp(a, p->data.name) == -1 ){
			p = p->leftChild;
			count = count+1;
		}
		else
		{
			p = p->rightChild;
			count = count+1;
		}
	}
	return 0;
}
int get_height(Ty_Node* root){											// 노드의 높이 출력
	Ty_Node *p = root;
	int height = 0;
	if(p != NULL)
	{
		height = 1 + max(get_height(p->leftChild), get_height(p->rightChild));	// recursive 적인 접근 recursive 적으로 최하단 노드의 높이부터 1씩 더해서 최상단 노드에서 두 자식의 height 값중 높은값에 자신인 1을 더해서 출력
	}
	return height;
}
void get_sibling(Ty_Node *root, char a[]){								// 형제노드 출력
	Ty_Node *p = root;
	Ty_Node *q = NULL;
																		// p 는 자식노드 q는 부모노드라는 설정
	while(p != NULL){
		if(strcmp(a, p->data.name) == 0)
			break;
		else if(strcmp(a, p->data.name) == -1){
			q = p;														// q가 부모노드로 만들고 p를 자식노드로 접근
			p = p->leftChild;

		}
		else{																// q가 부모노드로 만들고 p를 자식노드로 접근
			q = p;
			p = p->rightChild;

		}
	}

	if(p == NULL)
		printf("%s을 찾을 수 없습니다\n", a);
	else if(q == NULL)
		printf("Root 입니다.\n", a);
	else if(q->leftChild == p){												//p가 q의 왼쪽자식일경우 q 의 오른쪽 자식을 출력한다.
		if(q->rightChild == NULL)
		{
			printf("형제가 없습니다.\n");
		}
		else{																
			printf("%d %s\n",q->rightChild->data.key, q->rightChild->data.name); 
		
		}
	}
	else																	//p가 q의 오른쪽자식일 경우 q의 왼쪽자식을 출력한다.
	{
		if(q->leftChild == NULL)
		{
			printf("형제가 없습니다.\n");
		}
		else
			printf("%d %s\n",q->leftChild->data.key, q->leftChild->data.name); 

	}
}
void inorder(Ty_Node *root){												// 중위순회로 출력
	if(root){
		inorder(root->leftChild);											// 왼쪽먼저 recursive로 접근
		printf("%d %s\n", root->data.key, root->data.name);					
		inorder(root->rightChild);											// 마지막으로 오른쪽 recursive로 접근
	}
}