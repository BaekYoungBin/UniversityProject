#include <stdio.h>
#include <stdlib.h>			// exit()
#include <io.h>				// 디렉토리
#include <errno.h>			// errno
#include <string>
#define MAX_CHAR 100		// 단어 길이 MAX 

typedef struct ListNode{
	char data[MAX_CHAR];
	struct ListNode *link;
	int Cnt ;
}ListNode;														// 구조체 선언,typedef 로 ListNode를 지정해줌.  데이터배열과 링크 그리고 중복된 수 계산을 위한 Cnt 변수포함.

void error(char *message){										// 파일 에러날 경우 
	fprintf(stderr, "%s\n", message);
	exit(1);
}																

int general_read_from_many_files(char word_segmented[][100] );	// 디렉토리를 참조하여 파일 하나씩 읽어들이는 함수, 성공할 경우 1  실패할경우 0 리턴
																//	parameter : (입력받을 char배열(배열주소참조로 인해 실인자에 바로들어온다)) return type : int(자른 단어의 개수)

int wordS(char sentence[], char wordList[][MAX_CHAR]);			// 단어 자르는 함수
																// parameter : (char 문장, 문장을 단어로 잘라서 입력할 char 배열) return type : int(자른 단어의 개수)

bool searchoverlap(ListNode *head, char x[]);					// 중복된 데이터가 있는지 확인해주는 함수
																// parameter : (inked list의 헤드포인터, 넣을 데이터) return type : bool(flag역활을 하는 함수, 중복됬을경우(true)와 안됬을경우(false)를 리턴)

void insert_word(ListNode **phead, char x[]);					// 노드 삽입 함수
																// parameter : (linked list의 헤드포인터의 포인터, 넣을  데이터) return type : void( 삽입하고나서 리턴은 하지않는다)

ListNode *prenodesearch(ListNode *head, char x[]);				// 데이터가 들어갈 위치를 찾아주는 함수, 리턴값은 그 위치를 가리키는 노드,  
																// parameter :  (linked list의 헤드포인터, 넣을 데이터) return type : ListNode*(데이터가 들어갈 위치의 노드를가리키는 포인터)

ListNode *create_node(char data[], ListNode *link);				// 노드 생성 함수
																// parameter : (넣을 데이터, 링크(대개 NULL)) return type : ListNode* (만든 노드의 노드포인터 리턴)

ListNode *search_word(ListNode *head, char x[]);				// 리스트 탐색 함수 
																// parameter : (linked list의 헤드포인터, 찾을 데이터) return type : ListNode* (헤드포인터로 데이터를 찾아서 찾은 노드의 노드포인터를 리턴)

ListNode *delete_all(ListNode *head);							// 동적할당된 노드 회수 함수
																// parameter : (linked list의 헤드포인터) return type : ListNode* (할당 해제한 후 헤드포인터를넘겨줌)

//전역변수 part
char path[] = "articles/*";										// 폴더 경로 저장
int number = 0;											
_finddatai64_t c_file;											// 폴더 내에 파일 찾는 함수. 파일을 찾아서 그 파일의 이름을 c_file 에 저장
intptr_t hFile;													// 포인터 타입과 자료형을 같게 고정해주는 변수. 
FILE *fp;														// 파일포인터
char fpath[30];													// 파일 경로 저장
int filecount = 0;												// 읽어드린 파일의 개수 저장




int main(void) {
	char wordList[MAX_CHAR][MAX_CHAR];							// 단어들이 들어갈 배열. strtok함수를 써서 각각 0번째 1번째 ...번째 넣어주기위해 이중배열 선언
	for(int i = 0; i<number; i++){								// 배열 초기화
		for(int j = 0; j<MAX_CHAR; j++)
			wordList[i][j] = ' ';
	}
	bool check = false;											// 읽기 위한 신호를 주는 flag 역할 
	ListNode *Head = NULL;										// 궁극적으로 만들어 질 리스트의 헤드포인터
	ListNode *p;												// search하기위한 리스트노드 포인터
	bool overlap;												// 단어의 중복을 나타내는 flag						
	char c[20];													// search 할 스트링
	int wordcount = 0;											// 중복되지 않은 단어의 개수 저장
	int allwordcount = 0;										// 모든 단어 개수 저장

	if ( (hFile = _findfirsti64(path, &c_file)) == -1L ) {		// 디렉토리의 주소를 가지고있는 path를 c_file 에 넣어준다. 그곳의 주소를 정수포인터 hFile 에 넣어준다.
																// 실패했을경우 출력
		switch (errno) {										// errno inputoutput 정보확인해주는 변수, #include<errno.h> 를 통해 정의되어있다.
		case ENOENT:
			printf(":: 파일이 없음 ::\n");filecount = 0; break;
		case EINVAL:
			fprintf(stderr, "Invalid path name.\n"); exit(1); break;
		case ENOMEM:
			fprintf(stderr, "Not enough memory or file name too long.\n"); exit(1); break;
		default:
			fprintf(stderr, "Unknown error.\n"); exit(1); break;
		}
	}
	else {														// 디렉토리 참조가 성공적으로 됐을시.
		filecount = 1;											// file 1개를 읽었다는 count 1로 초기화
		_findnexti64(hFile, &c_file);							// 디렉토리안의 내용을 읽어보면 처음에  .  .. 과같은 두개의 위치참조가 나오기때문에 건너뛰기위한 _findnexti64함수(다음 파일로 건너뛴다)
		_findnexti64(hFile, &c_file);
		sprintf(fpath,"articles/%s", c_file.name);				// 디렉토리 안의 3번째부터 파일의 이름이 나오고, 그 파일이름은 c_file.name안에 들어있다. fpath에 articles/ap880212 와같이 스트링을 바꿔 넣어준다.
		fp = fopen(fpath, "r");									// 파일포인터로 파일주소에 접근해서 오픈한다.

		while(general_read_from_many_files(wordList)){			// 단어를 읽어오는 함수. 잘읽었을때 1을 리턴해서 while 루프가 돌아가며, 계속 단어를 읽으면서 더이상 못읽을경우 0을 리턴하여 while 루프를 종료한다.
			for(int i = 0; i < number; i++){					// general_read_from_many_files 함수를 실행하면, wordList라는 이중배열에 wordList[0][100], wordList[1][100] ... 문장을 단어로 분리하여 입력되고, 
																// 단어의 개수를 number 라는 전역변수에 넣어준다. 즉. 단어의 개수만큼 for 루프문이 돌고, 
																// wordList[i][100] 이 <TEXT> 인경우, </TEXT> 인경우를 나눠생각하여
																// check라고하는 flag변수를 true / false 해준다.
				if(strcmp(wordList[i], "<TEXT>") == 0){
					check = true;
				}
				if(strcmp(wordList[i], "</TEXT>") == 0){
					check = false;
				}


				if(check == true )								// check 가 true 즉, <TEXT> 를 읽었고, 그밑의 문장들을 단어로 분리하여 리스트에 넣어야 함을 의미함.
				{
					allwordcount ++;							// 단어 하나가 들어올때마다 모든 단어의 count 를 늘려준다.
					overlap = searchoverlap(Head, wordList[i]); // 그 단어가 리스트안에 중복된 단어가 있는지 확인한 후 true false 리턴.
					if(overlap == false){						// 중복되지않았을경우 = false , 리스트에 넣어주는작업
						wordcount ++;							// 중복되지않은 단어 count 를 늘려준다.
						insert_word(&Head, wordList[i]);		// 단어를 list 에 넣어준다.
																// insert_word -> prenodesearch -> createnode -> insert_word -> 입력완료
																// prenodesearch 로 사전순으로 입력될 위치를 찾고, 그 위치의 노드포인터를 리턴,
																// 데이터를 createnode 를 통해 노드로 만들고, insert_word 에서 리스트에 올바른위치에 삽입완료.
					}
				}
			}
		}

	}
	printf("모든 파일 입력 완료");								
	printf("입력된 문서의 개수 : %d\n", filecount);
	printf("리스트 내의 중복되지 않은 단어의 개수 : %d\n", wordcount);
	printf("리스트 내의 총 단어의 개수 : %d\n", allwordcount);

	while(1)													{// 단어 계속 찾기위한 while 루프, $$$를 입력할 경우 종료
		printf(" 찾고자 하는 단어를 쓰세요 ");
		scanf("%s", &c);										// 입력
		if(strcmp(c, "$$$") == 0)								// 종료 하기위해서 $$$를 입력하면 return 0
			return 0;
		else
			p = search_word(Head, c);							// 리스트와, 찾고자하는 단어를 search_word 에 넣어서 그 위치를 리턴받는다.
		if(p == NULL)											// 못찾았을 경우 error 출력
			printf("올바르지 않은 검색입니다.");
		else
			printf("%s의 카운트 : %d", c, p->Cnt);				// 출력

	}
	Head = delete_all(Head);									// 메모리 할당 해제하는 함수. 리스트 할당 해제한 후 헤드포인터넘겨준다.
	free(Head);													// 머리 할당 해제
	Head = NULL;												// 가리키는 값을 NULL포인터로 변경
	return 0;
}

																//디렉토리 읽어내는 함수
int general_read_from_many_files(char word_segmented[][100] ){

	char sentence[MAX_CHAR];									// 한줄입력받는 변수


																// 파일의 끝에 도달했을때 다음파일로 fp 를 옮김,
	if(feof(fp)){												// 파일의 끝일경우
		if(_findnexti64(hFile, &c_file)!=0)						// 파일의 다음파일을 c_file에 넣어준다.
		{
			_findclose(hFile);									// 파일이 마지막파일일경우 파일 종료한 후 
			return 0;											// 끝났다고하는 return 0
		}
		sprintf(fpath,"articles/%s", c_file.name);				// fpath 에 다음파일의 이름을 디렉토리주소/c_file.name 을 통해서 복사한다. 
		filecount++;											// 새로운 파일이 열렸기때문에 filecount를 올려준다.
		fp = fopen(fpath, "r");									// 파일포인터를 새로운 파일에 위치시킨다.
	}
	else{														// 파일의 끝이 아닌 파일 처음, 중간일경우
		fgets(sentence, sizeof(sentence), fp);					// 파일 포인터의 위치에 있는 문장을 읽어온다. 				
		int len;
		bool space_flag=true;									// 한 문장을 입력받았는데 그 문장이 공백인지 아닌지 판별하는 flag
		len=strlen(sentence);									// 문장의 길이를 넣어준다.

		for(int k=0; k<len ; k++) {								// 문장의 길이만큼 한캐릭터씩 검사해서 공백엔터(' ',\n') 즉, 빈줄일 경우는 false 로 끝나게되고, 공백엔터경우가 아닌경우에 계속실행. 
			if(sentence[k] != ' ' && sentence[k] != 10){		//
				space_flag=false;								
			}
		}
		if(space_flag==false) {									// 공백플래그 false 일경우
			number = wordS(sentence, word_segmented);			// 단어로 분할한후 그	단어의 개수 값을 number에 리턴한다.
		}
		return 1;												// 성공적으로 단어받아들였다고하는 return 1
	}
}

int wordS(char sentence[], char wordList[][MAX_CHAR]){			// 문장을 입력받아 단어로 자르는 함수.

	char *token = NULL;											// 토큰변수
	int i = 1;													// index변수
	int cnt = 1;												// 단어개수 저장
	char *separator = " ,\n";									// 토큰으로 자를 구분자

	token = strtok(sentence, separator);						// token 에 문장에서 자른 첫번째 단어를 넣어준다.
	strcpy(wordList[0], token);									// 잘린 문장을 넣어준다.

	while((token = strtok(NULL, separator)) !=NULL)				// 문장을 계속 단어단위로 끊도록 하는 루프
	{
		strcpy(wordList[i], token);								// wordList에 넣어준다.
		i ++;													// 인덱스값을 올려준다.
		cnt ++;													// 단어개수 cnt ++
	}

	return cnt;
}

bool searchoverlap(ListNode *head, char x[]){					// 중복된 값이 있는지 보는 함수
	ListNode *p;												// 노드 포인터
	p = head;													// 헤드포인터를 가르킨다.

	while(p!=NULL){												// 노드가 빈노드가 아닐경우
		if(strcmp(p->data, x) == 0)								// 포인터가 가르키는 노드속의 데이터가 입력데이터 x와 같을경우 
		{
			p->Cnt += 1;											// 그 노드의 개수를 올려준다.
			return true;										// 중복되었다고 표시하는 true 리턴
		}
		p = p->link;												// 같지 않을경우 노드포인터를 그 링크인 노드로 옮긴다.
	}

	return false;												// 최종적으로 데이터와 같은값을갖는 노드가 없을경우 false 리턴한다.
}


void insert_word(ListNode **phead, char x[]){					// 단어 삽입함수
	ListNode *p;												// 노드포인터
	ListNode *new_node;											
	p = prenodesearch(*phead, x);								// 사전순으로 삽입될 선행위치를 리턴받아 p 에 저장
	new_node = create_node(x, NULL);							// 데이터를 노드로 만들기

	if( *phead == NULL )										// 헤드포인터가 비었을경우, 즉 첫번째 삽입
	{
		new_node->link = NULL;									// 새로만든 노드의 링크를 NULL 로 지정.
		*phead = new_node;										// 헤드포인터를 새로 만든노드로 지정.
	}
	else if( p == NULL )										// 삽입될 위치가 NULL, 즉 맨 앞일경우
	{
		new_node->link = *phead;									// phead가 가르키는 노드를 새로만든노드의 링크에 지정
		*phead = new_node;										// phead가 newnode 가리키게함.
	}
	else{														// 그외의 경우들, 선행위치가 있을경우
		new_node->link = p->link;								// 선행위치의 링크를 새로삽입할 노드의 링크에 지정
		p->link = new_node;										// 선행노드의 링크를 새로삽입할 노드로 지정
	}

	printf("%s\n", x);											// 삽입된 단어 출력

}

ListNode *prenodesearch(ListNode *head, char x[])				// 사전순으로 선행위치를 찾는 함수.
{
	ListNode *p;
	ListNode *q;
	q = NULL;													// 선행노드 역할
	p = head;													// 헤드에서부터 차례대로 위치 찾아가는 포인터

	while(p!=NULL){												// 헤드가 널이아니다, 즉 노드의 값이 1개 이상일경우
		if(strcmp(p->data, x) == 1)								// 입력데이터 값이 비교할 노드보다 더 작을경우
			return q;											// 그 노드의 선행노드를 리턴함.
		q = p;													// 그외의 경우들에 q를 선행노드로 만들고
		p = p->link;												// p는 그 자신의 링크를 따라서 감
	}

	return q;													// 맨끝일경우 그 앞의 선행노드 리턴.
}

ListNode *create_node(char data[], ListNode *link){				// 노드 생성함수
	ListNode *new_node;											// 노드 포인터 하나만든다
	new_node = (ListNode *)malloc(sizeof(ListNode));			// 노드 동적메모리 할당
	if( new_node == NULL) error("메모리 할당 에러");			// 할당이안될경우 에러출력
	strcpy(new_node->data,data);								    // 데이터 복사
	new_node->link = link;										// 노드의 링크 지정.
	new_node->Cnt = 1;											// 카운트 증가
	return (new_node);											// new_node포인터를 리턴한다.
}
// 노드 생성.



//단어 찾는 함수
ListNode *search_word(ListNode *head, char x[])					// 단어 찾는 함수
{
	ListNode *p;												// 노드포인터 생성
	p = head;													// 노드포인터 헤드로 지정

	while(p!=NULL){												// 노드가 1개라도있을경우
		if(strcmp(p->data, x) == 0)											// 찾을 데이터와 일치할경우
			return p;											// 그 노드의 포인터를 리턴
		p = p->link;												// 못찾았을경우 링크를 따라간다.
	}

	return p;													// 최종적으로 못찾으면 NULL 리턴
}

ListNode *delete_all(ListNode *head){							// 메모리 할당 해제 함수
	ListNode *p = head->link;									// 헤드가 가르키는 것으로 지정
	ListNode *q = NULL;											// 널로 초기화
	while(p->link != NULL){										// 링크가 리스트의 마지막일때까지 루프 수행
		q = p;													// q는 p 로 바꾸기
		p = p->link;												// p 는 p링크로 바꾸기
		free(q);												// q 할당해제
	}
	head->link = p;												// head가 가르키는값 NULL
	return head;												// head 리턴.

}