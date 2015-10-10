#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<Windows.h>
#include<cstring>


#define MAX_QUEUE_SIZE 100
typedef struct astr {
	int key;				// �й�
	char name[50];			// �̸�
} element ;
typedef struct anod * Ty_Node_Ptr  ;
typedef struct anod {
	element data ;								 // ����� ����Ÿ �κ�
	Ty_Node_Ptr leftChild, rightChild ;			// ����� ����, ���� �ڽĿ� ���� ������
} Ty_Node ; 

void error(char *message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}


FILE *fp;

void insert_from_file(Ty_Node **root);										// ȭ���� ������ ��ü ������ �ִ� �Լ�
void insert_anode(Ty_Node **root, element data);							// ���ο� �����͸� �ϳ� �޾Ƽ� ���� ����� BST�� �߰��ϴ� �Լ�
void delete_anode(Ty_Node *root, char name[]);								// BST �� Ž���Ͽ� �־��� �̸��� ���� ��带 �����ϴ� �Լ�
Ty_Node* search_anode(Ty_Node *root, char a[]);								// BST �� Ž���ؼ� �־��� �̸��� ���� ��带 return �ϴ� �Լ�
int get_level(Ty_Node *root, char a[]);										// BST �� Ž���ؼ� �־��� �̸��� ���� ����� ���̸� ����ϴ� �Լ�
void get_sibling(Ty_Node *root, char a[]);									// BST �� Ž���ؼ� �־��� �̸��� ���� ����� ������带 ����ϴ� �Լ�
int get_height(Ty_Node *root);												// BST �� Ž���ؼ� ��ü ���̸� ����ϴ� �Լ�
void inorder(Ty_Node *root);												// BST �� ������ȸ ������� ����ϴ� �Լ�
int cnt;																	// ������ȸ ������� ��� �� �� ���ظ� ���� ���� �� ����� ������ ����ϱ� ���� ���� ��������
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
	printf("���� �̸��� ���ΰ���?\n");								
	scanf("%s", &fpath);													// �����̸� �Է�


	fp = fopen(fpath, "r");	
	if(fp){																	// �����̸��� ������ ��

		insert_from_file(&root);											// ���Ϸκ��� ��� ����
		while(1){
			printf("��ɾ �Է��ϼ���\n");
			fflush(stdin);													// scanf ���� ����
			scanf("%[^\n]s", &order);										// scanf �� ��ġ gets ó�� ���� �����ϰ� \n ���� �о���̴� ���
			token = strtok(order, separator);								// token �� �̿��� �ܾ� ����
			switch(token[0]){												// ù��° ��ɾ� �κ��� switch �� �־� ��� case�� �ƽ�Ű�ڵ尪���� 

			case 105 :	// i
				token = strtok(NULL, separator);
				strcpy(data.name, token); 
				token = strtok(NULL, separator);
				data.key = atoi(token);
				insert_anode(&root, data);									// �߰������� data�� �־ ��忡 ����
				break;
			case 112 : 
				// p
				inorder(root);												// ������ȸ������� ���
				break;
			case 100 :  // d
				token = strtok(NULL, separator);
				delete_anode(root, token);									// ����
				break;
			case 115 :  // s
				token = strtok(NULL, separator);
				p = search_anode(root, token);								// �ش� Ű���� ������� ���
				if(p !=NULL)
					printf("%s %d\n", p->data.name, p->data.key); 
				else
					printf("%s�� ã�� �� �����ϴ�\n", token);
				break;
			case 118 :  // v
				token = strtok(NULL, separator);
				level = get_level(root, token);								// �ش� Ű���� ��� ���� ���
				if(level !=0)
					printf("%s�� ���� : %d\n", token, level);
				else
					printf("%s�� ã�� �� �����ϴ�\n", token);

				break;
			case 98 :  // b
				token = strtok(NULL, separator);
				get_sibling(root, token);									// �ش� Ű���� ��� ���� ���
				break;
			case 104 : // h
				level = get_height(root);									// ���� ���
				if(level !=NULL)
					printf("���� : %d\n", level);
				break;
			case 101 : exit(0);												// ����


			}
		}
	}
	else
	{
		printf("file �̸��� ã�� �� �����ϴ�\n");
	}
}

void insert_from_file(Ty_Node **root){
	char sentence[100];
	element data;
	while(!feof(fp)){														// ������ ������ �ݺ�
		fgets(sentence, sizeof(sentence), fp);								// sentence�� ������ �Է¹���
		char *token = NULL;													
		char *separator = " ,\n";
		token = strtok(sentence, separator);								// strtok �� ���� ������ �ܾ�� ����
		data.key = atoi(token);											
		token = strtok(NULL, separator);									
		strcpy(data.name, token);											// element �ڷ����� ����Ÿ�� key �� name �� token �� ���� �и��� ������ �־��ش�.
		insert_anode(root, data);											// data�� ��忡 ����
	}
}
void insert_anode(Ty_Node **root, element data){							
	Ty_Node *p, *t;	// p�� �θ���, t�� ������
	Ty_Node *n;	// n�� ���ο� ���
	n = (Ty_Node*)malloc(sizeof(Ty_Node));									// �����Ҵ�

	if(n == NULL)
		return;

	n->data.key =data.key; 

	strcpy(n->data.name, data.name);
	n->leftChild = NULL;
	n->rightChild = NULL;													// ���ο� ��� ����

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

	}																		 // ������ ��ġ Ž���ϴ� �۾�

	if(p != NULL)
		if(strcmp(n->data.name, p->data.name) < 0)							// �����ϴ� �۾�
			p->leftChild = n;
		else
			p->rightChild = n;
	else																	// p�� NULL �� ���� ���� ù��°���� ��/ ��带 root �� �����
		*root = n;

}
void delete_anode(Ty_Node *root, char name[])				
{
	Ty_Node *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = root;
	while( t != NULL && (strcmp(t->data.name, name) !=0 )){
		p = t;
		t = ( strcmp(name, t->data.name) == -1 ) ? t->leftChild : t->rightChild;
	}
	if( t == NULL ) { 														// Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}
																			// �ܸ������ ���
	if( (t->leftChild==NULL) && (t->rightChild==NULL) ){ 
		if( p->leftChild == t ) 
			p->leftChild = NULL;
		else   p->rightChild = NULL;
	}
																			// �ϳ��� �ڽĸ� ������ ���
	else if((t->leftChild==NULL)||(t->rightChild==NULL)){
		child = (t->leftChild != NULL) ? t->leftChild : t->rightChild;
		if( p->leftChild == t ) 
			p->leftChild = child;
		else p->rightChild = child;
	}
	else{																	// �ΰ��� �ڽ��� ������ ��� 
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
	free(t);																// ��� ����
}

Ty_Node* search_anode(Ty_Node* root, char a[]){								// �־��� key ���� ��� ���� ���
	Ty_Node *p = root;

	while(p !=NULL){
		if(strcmp(a, p->data.name) == 0)
			return p;													// ��带 ã���� �� �� ��� ��ȯ
		else if(strcmp(a, p->data.name) == -1 )
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	return p;															// ��尡 ������ NULL�� ���� p ��ȯ
}
int get_level(Ty_Node *root, char a[]){									// �־��� key ���� ��� ���� ���
	Ty_Node *p = root;	
	int count = 1;														// �������� cnt
	while(p !=NULL){
		if(strcmp(a, p->data.name) == 0)
			return count;													// ��带 ã���� �� �� ����� cnt ��ȯ
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
int get_height(Ty_Node* root){											// ����� ���� ���
	Ty_Node *p = root;
	int height = 0;
	if(p != NULL)
	{
		height = 1 + max(get_height(p->leftChild), get_height(p->rightChild));	// recursive ���� ���� recursive ������ ���ϴ� ����� ���̺��� 1�� ���ؼ� �ֻ�� ��忡�� �� �ڽ��� height ���� �������� �ڽ��� 1�� ���ؼ� ���
	}
	return height;
}
void get_sibling(Ty_Node *root, char a[]){								// ������� ���
	Ty_Node *p = root;
	Ty_Node *q = NULL;
																		// p �� �ڽĳ�� q�� �θ����� ����
	while(p != NULL){
		if(strcmp(a, p->data.name) == 0)
			break;
		else if(strcmp(a, p->data.name) == -1){
			q = p;														// q�� �θ���� ����� p�� �ڽĳ��� ����
			p = p->leftChild;

		}
		else{																// q�� �θ���� ����� p�� �ڽĳ��� ����
			q = p;
			p = p->rightChild;

		}
	}

	if(p == NULL)
		printf("%s�� ã�� �� �����ϴ�\n", a);
	else if(q == NULL)
		printf("Root �Դϴ�.\n", a);
	else if(q->leftChild == p){												//p�� q�� �����ڽ��ϰ�� q �� ������ �ڽ��� ����Ѵ�.
		if(q->rightChild == NULL)
		{
			printf("������ �����ϴ�.\n");
		}
		else{																
			printf("%d %s\n",q->rightChild->data.key, q->rightChild->data.name); 
		
		}
	}
	else																	//p�� q�� �������ڽ��� ��� q�� �����ڽ��� ����Ѵ�.
	{
		if(q->leftChild == NULL)
		{
			printf("������ �����ϴ�.\n");
		}
		else
			printf("%d %s\n",q->leftChild->data.key, q->leftChild->data.name); 

	}
}
void inorder(Ty_Node *root){												// ������ȸ�� ���
	if(root){
		inorder(root->leftChild);											// ���ʸ��� recursive�� ����
		printf("%d %s\n", root->data.key, root->data.name);					
		inorder(root->rightChild);											// ���������� ������ recursive�� ����
	}
}