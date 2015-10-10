#include <stdio.h>
#include <stdlib.h>			// exit()
#include <io.h>				// ���丮
#include <errno.h>			// errno
#include <string>
#define MAX_CHAR 100		// �ܾ� ���� MAX 

typedef struct ListNode{
	char data[MAX_CHAR];
	struct ListNode *link;
	int Cnt ;
}ListNode;														// ����ü ����,typedef �� ListNode�� ��������.  �����͹迭�� ��ũ �׸��� �ߺ��� �� ����� ���� Cnt ��������.

void error(char *message){										// ���� ������ ��� 
	fprintf(stderr, "%s\n", message);
	exit(1);
}																

int general_read_from_many_files(char word_segmented[][100] );	// ���丮�� �����Ͽ� ���� �ϳ��� �о���̴� �Լ�, ������ ��� 1  �����Ұ�� 0 ����
																//	parameter : (�Է¹��� char�迭(�迭�ּ������� ���� �����ڿ� �ٷε��´�)) return type : int(�ڸ� �ܾ��� ����)

int wordS(char sentence[], char wordList[][MAX_CHAR]);			// �ܾ� �ڸ��� �Լ�
																// parameter : (char ����, ������ �ܾ�� �߶� �Է��� char �迭) return type : int(�ڸ� �ܾ��� ����)

bool searchoverlap(ListNode *head, char x[]);					// �ߺ��� �����Ͱ� �ִ��� Ȯ�����ִ� �Լ�
																// parameter : (inked list�� ���������, ���� ������) return type : bool(flag��Ȱ�� �ϴ� �Լ�, �ߺ��������(true)�� �ȉ������(false)�� ����)

void insert_word(ListNode **phead, char x[]);					// ��� ���� �Լ�
																// parameter : (linked list�� ����������� ������, ����  ������) return type : void( �����ϰ��� ������ �����ʴ´�)

ListNode *prenodesearch(ListNode *head, char x[]);				// �����Ͱ� �� ��ġ�� ã���ִ� �Լ�, ���ϰ��� �� ��ġ�� ����Ű�� ���,  
																// parameter :  (linked list�� ���������, ���� ������) return type : ListNode*(�����Ͱ� �� ��ġ�� ��带����Ű�� ������)

ListNode *create_node(char data[], ListNode *link);				// ��� ���� �Լ�
																// parameter : (���� ������, ��ũ(�밳 NULL)) return type : ListNode* (���� ����� ��������� ����)

ListNode *search_word(ListNode *head, char x[]);				// ����Ʈ Ž�� �Լ� 
																// parameter : (linked list�� ���������, ã�� ������) return type : ListNode* (��������ͷ� �����͸� ã�Ƽ� ã�� ����� ��������͸� ����)

ListNode *delete_all(ListNode *head);							// �����Ҵ�� ��� ȸ�� �Լ�
																// parameter : (linked list�� ���������) return type : ListNode* (�Ҵ� ������ �� ��������͸��Ѱ���)

//�������� part
char path[] = "articles/*";										// ���� ��� ����
int number = 0;											
_finddatai64_t c_file;											// ���� ���� ���� ã�� �Լ�. ������ ã�Ƽ� �� ������ �̸��� c_file �� ����
intptr_t hFile;													// ������ Ÿ�԰� �ڷ����� ���� �������ִ� ����. 
FILE *fp;														// ����������
char fpath[30];													// ���� ��� ����
int filecount = 0;												// �о�帰 ������ ���� ����




int main(void) {
	char wordList[MAX_CHAR][MAX_CHAR];							// �ܾ���� �� �迭. strtok�Լ��� �Ἥ ���� 0��° 1��° ...��° �־��ֱ����� ���߹迭 ����
	for(int i = 0; i<number; i++){								// �迭 �ʱ�ȭ
		for(int j = 0; j<MAX_CHAR; j++)
			wordList[i][j] = ' ';
	}
	bool check = false;											// �б� ���� ��ȣ�� �ִ� flag ���� 
	ListNode *Head = NULL;										// �ñ������� ����� �� ����Ʈ�� ���������
	ListNode *p;												// search�ϱ����� ����Ʈ��� ������
	bool overlap;												// �ܾ��� �ߺ��� ��Ÿ���� flag						
	char c[20];													// search �� ��Ʈ��
	int wordcount = 0;											// �ߺ����� ���� �ܾ��� ���� ����
	int allwordcount = 0;										// ��� �ܾ� ���� ����

	if ( (hFile = _findfirsti64(path, &c_file)) == -1L ) {		// ���丮�� �ּҸ� �������ִ� path�� c_file �� �־��ش�. �װ��� �ּҸ� ���������� hFile �� �־��ش�.
																// ����������� ���
		switch (errno) {										// errno inputoutput ����Ȯ�����ִ� ����, #include<errno.h> �� ���� ���ǵǾ��ִ�.
		case ENOENT:
			printf(":: ������ ���� ::\n");filecount = 0; break;
		case EINVAL:
			fprintf(stderr, "Invalid path name.\n"); exit(1); break;
		case ENOMEM:
			fprintf(stderr, "Not enough memory or file name too long.\n"); exit(1); break;
		default:
			fprintf(stderr, "Unknown error.\n"); exit(1); break;
		}
	}
	else {														// ���丮 ������ ���������� ������.
		filecount = 1;											// file 1���� �о��ٴ� count 1�� �ʱ�ȭ
		_findnexti64(hFile, &c_file);							// ���丮���� ������ �о�� ó����  .  .. ������ �ΰ��� ��ġ������ �����⶧���� �ǳʶٱ����� _findnexti64�Լ�(���� ���Ϸ� �ǳʶڴ�)
		_findnexti64(hFile, &c_file);
		sprintf(fpath,"articles/%s", c_file.name);				// ���丮 ���� 3��°���� ������ �̸��� ������, �� �����̸��� c_file.name�ȿ� ����ִ�. fpath�� articles/ap880212 �Ͱ��� ��Ʈ���� �ٲ� �־��ش�.
		fp = fopen(fpath, "r");									// ���������ͷ� �����ּҿ� �����ؼ� �����Ѵ�.

		while(general_read_from_many_files(wordList)){			// �ܾ �о���� �Լ�. ���о����� 1�� �����ؼ� while ������ ���ư���, ��� �ܾ �����鼭 ���̻� ��������� 0�� �����Ͽ� while ������ �����Ѵ�.
			for(int i = 0; i < number; i++){					// general_read_from_many_files �Լ��� �����ϸ�, wordList��� ���߹迭�� wordList[0][100], wordList[1][100] ... ������ �ܾ�� �и��Ͽ� �Էµǰ�, 
																// �ܾ��� ������ number ��� ���������� �־��ش�. ��. �ܾ��� ������ŭ for �������� ����, 
																// wordList[i][100] �� <TEXT> �ΰ��, </TEXT> �ΰ�츦 ���������Ͽ�
																// check����ϴ� flag������ true / false ���ش�.
				if(strcmp(wordList[i], "<TEXT>") == 0){
					check = true;
				}
				if(strcmp(wordList[i], "</TEXT>") == 0){
					check = false;
				}


				if(check == true )								// check �� true ��, <TEXT> �� �о���, �׹��� ������� �ܾ�� �и��Ͽ� ����Ʈ�� �־�� ���� �ǹ���.
				{
					allwordcount ++;							// �ܾ� �ϳ��� ���ö����� ��� �ܾ��� count �� �÷��ش�.
					overlap = searchoverlap(Head, wordList[i]); // �� �ܾ ����Ʈ�ȿ� �ߺ��� �ܾ �ִ��� Ȯ���� �� true false ����.
					if(overlap == false){						// �ߺ������ʾ������ = false , ����Ʈ�� �־��ִ��۾�
						wordcount ++;							// �ߺ��������� �ܾ� count �� �÷��ش�.
						insert_word(&Head, wordList[i]);		// �ܾ list �� �־��ش�.
																// insert_word -> prenodesearch -> createnode -> insert_word -> �Է¿Ϸ�
																// prenodesearch �� ���������� �Էµ� ��ġ�� ã��, �� ��ġ�� ��������͸� ����,
																// �����͸� createnode �� ���� ���� �����, insert_word ���� ����Ʈ�� �ùٸ���ġ�� ���ԿϷ�.
					}
				}
			}
		}

	}
	printf("��� ���� �Է� �Ϸ�");								
	printf("�Էµ� ������ ���� : %d\n", filecount);
	printf("����Ʈ ���� �ߺ����� ���� �ܾ��� ���� : %d\n", wordcount);
	printf("����Ʈ ���� �� �ܾ��� ���� : %d\n", allwordcount);

	while(1)													{// �ܾ� ��� ã������ while ����, $$$�� �Է��� ��� ����
		printf(" ã���� �ϴ� �ܾ ������ ");
		scanf("%s", &c);										// �Է�
		if(strcmp(c, "$$$") == 0)								// ���� �ϱ����ؼ� $$$�� �Է��ϸ� return 0
			return 0;
		else
			p = search_word(Head, c);							// ����Ʈ��, ã�����ϴ� �ܾ search_word �� �־ �� ��ġ�� ���Ϲ޴´�.
		if(p == NULL)											// ��ã���� ��� error ���
			printf("�ùٸ��� ���� �˻��Դϴ�.");
		else
			printf("%s�� ī��Ʈ : %d", c, p->Cnt);				// ���

	}
	Head = delete_all(Head);									// �޸� �Ҵ� �����ϴ� �Լ�. ����Ʈ �Ҵ� ������ �� ��������ͳѰ��ش�.
	free(Head);													// �Ӹ� �Ҵ� ����
	Head = NULL;												// ����Ű�� ���� NULL�����ͷ� ����
	return 0;
}

																//���丮 �о�� �Լ�
int general_read_from_many_files(char word_segmented[][100] ){

	char sentence[MAX_CHAR];									// �����Է¹޴� ����


																// ������ ���� ���������� �������Ϸ� fp �� �ű�,
	if(feof(fp)){												// ������ ���ϰ��
		if(_findnexti64(hFile, &c_file)!=0)						// ������ ���������� c_file�� �־��ش�.
		{
			_findclose(hFile);									// ������ �����������ϰ�� ���� ������ �� 
			return 0;											// �����ٰ��ϴ� return 0
		}
		sprintf(fpath,"articles/%s", c_file.name);				// fpath �� ���������� �̸��� ���丮�ּ�/c_file.name �� ���ؼ� �����Ѵ�. 
		filecount++;											// ���ο� ������ ���ȱ⶧���� filecount�� �÷��ش�.
		fp = fopen(fpath, "r");									// ���������͸� ���ο� ���Ͽ� ��ġ��Ų��.
	}
	else{														// ������ ���� �ƴ� ���� ó��, �߰��ϰ��
		fgets(sentence, sizeof(sentence), fp);					// ���� �������� ��ġ�� �ִ� ������ �о�´�. 				
		int len;
		bool space_flag=true;									// �� ������ �Է¹޾Ҵµ� �� ������ �������� �ƴ��� �Ǻ��ϴ� flag
		len=strlen(sentence);									// ������ ���̸� �־��ش�.

		for(int k=0; k<len ; k++) {								// ������ ���̸�ŭ ��ĳ���;� �˻��ؼ� ���鿣��(' ',\n') ��, ������ ���� false �� �����Եǰ�, ���鿣�Ͱ�찡 �ƴѰ�쿡 ��ӽ���. 
			if(sentence[k] != ' ' && sentence[k] != 10){		//
				space_flag=false;								
			}
		}
		if(space_flag==false) {									// �����÷��� false �ϰ��
			number = wordS(sentence, word_segmented);			// �ܾ�� �������� ��	�ܾ��� ���� ���� number�� �����Ѵ�.
		}
		return 1;												// ���������� �ܾ�޾Ƶ鿴�ٰ��ϴ� return 1
	}
}

int wordS(char sentence[], char wordList[][MAX_CHAR]){			// ������ �Է¹޾� �ܾ�� �ڸ��� �Լ�.

	char *token = NULL;											// ��ū����
	int i = 1;													// index����
	int cnt = 1;												// �ܾ�� ����
	char *separator = " ,\n";									// ��ū���� �ڸ� ������

	token = strtok(sentence, separator);						// token �� ���忡�� �ڸ� ù��° �ܾ �־��ش�.
	strcpy(wordList[0], token);									// �߸� ������ �־��ش�.

	while((token = strtok(NULL, separator)) !=NULL)				// ������ ��� �ܾ������ ������ �ϴ� ����
	{
		strcpy(wordList[i], token);								// wordList�� �־��ش�.
		i ++;													// �ε������� �÷��ش�.
		cnt ++;													// �ܾ�� cnt ++
	}

	return cnt;
}

bool searchoverlap(ListNode *head, char x[]){					// �ߺ��� ���� �ִ��� ���� �Լ�
	ListNode *p;												// ��� ������
	p = head;													// ��������͸� ����Ų��.

	while(p!=NULL){												// ��尡 ���尡 �ƴҰ��
		if(strcmp(p->data, x) == 0)								// �����Ͱ� ����Ű�� ������ �����Ͱ� �Էµ����� x�� ������� 
		{
			p->Cnt += 1;											// �� ����� ������ �÷��ش�.
			return true;										// �ߺ��Ǿ��ٰ� ǥ���ϴ� true ����
		}
		p = p->link;												// ���� ������� ��������͸� �� ��ũ�� ���� �ű��.
	}

	return false;												// ���������� �����Ϳ� ������������ ��尡 ������� false �����Ѵ�.
}


void insert_word(ListNode **phead, char x[]){					// �ܾ� �����Լ�
	ListNode *p;												// ���������
	ListNode *new_node;											
	p = prenodesearch(*phead, x);								// ���������� ���Ե� ������ġ�� ���Ϲ޾� p �� ����
	new_node = create_node(x, NULL);							// �����͸� ���� �����

	if( *phead == NULL )										// ��������Ͱ� ��������, �� ù��° ����
	{
		new_node->link = NULL;									// ���θ��� ����� ��ũ�� NULL �� ����.
		*phead = new_node;										// ��������͸� ���� ������� ����.
	}
	else if( p == NULL )										// ���Ե� ��ġ�� NULL, �� �� ���ϰ��
	{
		new_node->link = *phead;									// phead�� ����Ű�� ��带 ���θ������� ��ũ�� ����
		*phead = new_node;										// phead�� newnode ����Ű����.
	}
	else{														// �׿��� ����, ������ġ�� �������
		new_node->link = p->link;								// ������ġ�� ��ũ�� ���λ����� ����� ��ũ�� ����
		p->link = new_node;										// �������� ��ũ�� ���λ����� ���� ����
	}

	printf("%s\n", x);											// ���Ե� �ܾ� ���

}

ListNode *prenodesearch(ListNode *head, char x[])				// ���������� ������ġ�� ã�� �Լ�.
{
	ListNode *p;
	ListNode *q;
	q = NULL;													// ������ ����
	p = head;													// ��忡������ ���ʴ�� ��ġ ã�ư��� ������

	while(p!=NULL){												// ��尡 ���̾ƴϴ�, �� ����� ���� 1�� �̻��ϰ��
		if(strcmp(p->data, x) == 1)								// �Էµ����� ���� ���� ��庸�� �� �������
			return q;											// �� ����� �����带 ������.
		q = p;													// �׿��� ���鿡 q�� ������� �����
		p = p->link;												// p�� �� �ڽ��� ��ũ�� ���� ��
	}

	return q;													// �ǳ��ϰ�� �� ���� ������ ����.
}

ListNode *create_node(char data[], ListNode *link){				// ��� �����Լ�
	ListNode *new_node;											// ��� ������ �ϳ������
	new_node = (ListNode *)malloc(sizeof(ListNode));			// ��� �����޸� �Ҵ�
	if( new_node == NULL) error("�޸� �Ҵ� ����");			// �Ҵ��̾ȵɰ�� �������
	strcpy(new_node->data,data);								    // ������ ����
	new_node->link = link;										// ����� ��ũ ����.
	new_node->Cnt = 1;											// ī��Ʈ ����
	return (new_node);											// new_node�����͸� �����Ѵ�.
}
// ��� ����.



//�ܾ� ã�� �Լ�
ListNode *search_word(ListNode *head, char x[])					// �ܾ� ã�� �Լ�
{
	ListNode *p;												// ��������� ����
	p = head;													// ��������� ���� ����

	while(p!=NULL){												// ��尡 1�����������
		if(strcmp(p->data, x) == 0)											// ã�� �����Ϳ� ��ġ�Ұ��
			return p;											// �� ����� �����͸� ����
		p = p->link;												// ��ã������� ��ũ�� ���󰣴�.
	}

	return p;													// ���������� ��ã���� NULL ����
}

ListNode *delete_all(ListNode *head){							// �޸� �Ҵ� ���� �Լ�
	ListNode *p = head->link;									// ��尡 ����Ű�� ������ ����
	ListNode *q = NULL;											// �η� �ʱ�ȭ
	while(p->link != NULL){										// ��ũ�� ����Ʈ�� �������϶����� ���� ����
		q = p;													// q�� p �� �ٲٱ�
		p = p->link;												// p �� p��ũ�� �ٲٱ�
		free(q);												// q �Ҵ�����
	}
	head->link = p;												// head�� ����Ű�°� NULL
	return head;												// head ����.

}