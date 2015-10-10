#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define DepthBound 30
typedef struct nodestruct *node;
typedef struct nodestruct{
	int node_inform[4][4];
	node pred;
	int f;
	int g;
	int h;
}nodestruct;
typedef struct openstruct *open_ptr;
typedef struct openstruct{
	node node;		// 노드의 정보
	open_ptr link;			// 노드의 링크리스트
}open;
typedef struct closestruct *close_ptr;
typedef struct closestruct{
	node node;
	close_ptr link;
}close;
int search_zero_x(int n[4][4]);
int search_zero_y(int n[4][4]);

void View(node n);
void DoAstar(node n, open **oproot, close **clroot);
void ViewAstar(node n);
bool ArrayCompare(int node[4][4], int node1[4][4]);
int calculate_h(int node[4][4]);
void expand_node_and_push_open(node m, open **root, close **clroot);


int Start_node[4][4];
int Final_node[4][4];
int Open_cnt = 0; 
int Close_cnt = 0;

int main(){

	int sel = 0;
	int get_node;
	int i, j;



	do
	{
		printf("탐색을 원하시나요? (yes = 1/ exit = 0)    ");
		scanf("%d", &sel);
		if(sel ==0)
		{
			printf("Program completed!\n");
		}
		else if(sel !=1)
		{
			printf("잘못된 선택입니다\n");
		}

		else
		{
			printf("시작노드 = ");
			for(i = 0; i<4; i++){
				for(j = 0; j<4; j++)
				{
					scanf("%d", &get_node);
					Start_node[i][j] = get_node;
				}
			}	
			fflush(stdin);
			// 시작노드정보 입력완료

			printf("목표노드 = ");
			for(i = 0; i<4; i++){
				for(j = 0; j<4; j++)
				{
					scanf("%d", &get_node);
					Final_node[i][j] = get_node;
				}
			}	
			fflush(stdin);
			// 목표노드정보 입력완료
			node startnode;
			startnode = (node)malloc(sizeof(nodestruct));	// 노드생성
			for(i = 0; i<4; i++){
				for(j = 0; j<4; j++)
				{
					startnode->node_inform[i][j]= Start_node[i][j];			// 노드정보를 노드에 넣기
				}
			}
			startnode->pred = NULL;
			startnode->g = 0;				
			startnode->h = calculate_h(startnode->node_inform);				// h 계산
			startnode->f = startnode->g+startnode->h;	
			open *open_root = NULL;
			close *close_root = NULL;

			DoAstar(startnode, &open_root, &close_root);
			startnode = NULL;
			
			Open_cnt = 0; 
			Close_cnt = 0;
			fflush(stdin);

		}



	}while(sel != 0);

}
void PushOpen(open **root,	node node){
	open *p, *t;	// p 는 부모노드, t 는 현재노드
	open *n;
	n = (open*)malloc(sizeof(openstruct));
	n->node = node;
	n->link = NULL;

	t = *root;
	p = NULL;

	if(Open_cnt == 0){
		*root = n;
		Open_cnt++;
	}

	else{
		if(n->node->f < t->node->f){
			*root = n;
			n->link = t;
			Open_cnt++;
		}
		else{
			while(n->node->f >= t->node->f){
				p = t;
				t = t->link;
				if(t == NULL)
					break;

			}

			if(t == NULL)
			{
				p->link = n;
				Open_cnt++;
			}
			else
			{
				p = t;
				p->link = n;
				n->link = t;
				Open_cnt ++;
			}

		}
	}

}
open* PopOpen(open **root){

	open *p;
	open *t;
	p = *root;


	if(Open_cnt == 1){
		*root = NULL;
		Open_cnt--;
		return p;
	}
	else if(Open_cnt ==0)
	{
		printf("error");
	}
	else
	{
		*root = p->link;
		Open_cnt--;
		return p;
	}
}
void PushClose(close **root, node node){
	close *p, *t;	// p 는 부모노드, t 는 현재노드
	close *n;
	n = (close*)malloc(sizeof(closestruct));
	n->node = node;
	t = *root;
	p = NULL;

	n->link = t;


	*root = n;

}
close* PopClose(close **root, node n){
	close *p;
	close *t;

	p = NULL;
	t = *root;
	while(!ArrayCompare(t->node->node_inform, n->node_inform)){
		p = t;
		t = t->link;
	}


	p->link = t->link;
	return t;


}
int calculate_h(int node[4][4]){
	int i, j;
	int cnt = 0;
	for(i = 0; i<4; i++)
	{
		for(j = 0; j<4; j++){

			if(node[i][j] == Final_node[i][j]){
				cnt++;
			}

		}
	}
	return 16-cnt;
}

void DoAstar(node n, open **oproot, close **clroot){

	open *p;
	PushOpen(oproot, n);
	while(*oproot != NULL){

		p = PopOpen(oproot);

		if(Open_cnt == 0){

		}
		else if(ArrayCompare(p->node->node_inform, Final_node)){		// Goal 찾을때
			ViewAstar(p->node);									// 경로출력
			return;
		}

		PushClose(clroot, p->node);
		expand_node_and_push_open(p->node, oproot, clroot);

	}

	printf("경로 탐색 불가");






}
void expand_node_and_push_open(node m, open **root, close **clroot){
	open *op;
	op = *root;
	close *cp;
	cp = *clroot;

	int g;
	int up[4][4];
	int left[4][4];
	int down[4][4];
	int right[4][4];
	int tmp;
	int upzero= 0;
	int leftzero = 0;
	int downzero = 0;
	int rightzero = 0;
	int up_f;
	int left_f;
	int down_f;
	int right_f;
	g = m->g;
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			if(m->node_inform[i][j] == 0)
			{
				if(i == 0 && j==0){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = 0;
							left[x][y] = 0;
							down[x][y] = m->node_inform[x][y];
							right[x][y] = m->node_inform[x][y];
						}
					}
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;



				}
				else if(i == 0 && (j ==1 || j == 2)){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = 0;
							left[x][y] = m->node_inform[x][y];
							down[x][y] = m->node_inform[x][y];
							right[x][y] = m->node_inform[x][y];
						}
					}

					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;



				}
				else if(i == 0 && j == 3){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = 0;
							left[x][y] = m->node_inform[x][y];
							down[x][y] = m->node_inform[x][y];
							right[x][y] = 0;
						}
					}
					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;

				}
				else if(j == 0 && (i == 1 || i == 2)){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = 0;
							down[x][y] = m->node_inform[x][y];
							right[x][y] = m->node_inform[x][y];
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;

				}
				else if(j == 3 && (i == 1 || i ==2)){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = m->node_inform[x][y];
							down[x][y] = m->node_inform[x][y];
							right[x][y] = 0;
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;
				}
				else if(i == 3 && j == 0){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = 0;
							down[x][y] = 0;
							right[x][y] = m->node_inform[x][y];
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;
				}
				else if(i == 3 && (j == 1 || j == 2)){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = m->node_inform[x][y];
							down[x][y] = 0;
							right[x][y] = m->node_inform[x][y];
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;
				}
				else if(i == 3 && j == 3){
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = m->node_inform[x][y];
							down[x][y] = 0;
							right[x][y] = 0;
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
				}
				else{
					for(int x = 0; x <4; x++){
						for(int y = 0; y<4; y++){
							up[x][y] = m->node_inform[x][y];
							left[x][y] = m->node_inform[x][y];
							down[x][y] = m->node_inform[x][y];
							right[x][y] = m->node_inform[x][y];
						}
					}
					tmp = up[i-1][j];
					up[i-1][j] = 0;
					up[i][j] = tmp;
					tmp = left[i][j-1];
					left[i][j-1] = 0;
					left[i][j] = tmp;
					tmp = down[i+1][j];
					down[i+1][j] = 0;
					down[i][j] = tmp;
					tmp = right[i][j+1];
					right[i][j+1] = 0;
					right[i][j] = tmp;

				}
			}
		}
	}
	//모든 원소가 0이 아니면 open이랑 close에 비교한후 노드만들어서 넣기
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			if(up[i][j] == 0)
				upzero++;
			if(down[i][j] == 0)
				downzero++;
			if(left[i][j] == 0)
				leftzero++;
			if(right[i][j] == 0)
				rightzero++;
		}
	}
	op = *root;
	if(upzero == 1)
	{
		node upnode;
		upnode = (node)malloc(sizeof(nodestruct));

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++)
			{
				upnode->node_inform[i][j] = up[i][j];	
				upnode->g = m->g+1;
				upnode->h = calculate_h(up);
				upnode->f = (m->g + 1) + calculate_h(up);
				upnode->pred = m;
			}
		}		
		// 노드생성

		if(Open_cnt==0){
			PushOpen(&op, upnode);
			*root = op;
		}
		else{
			while(op !=NULL ){
				if(ArrayCompare(op->node->node_inform, upnode->node_inform))
				{
					if(op->node->f > upnode->f)
					{
						op->node->pred = m;
						op->node->f = upnode->f;
						op->node->g = upnode->g;
						break;
					}
					else
						break;
				}
				else
				{
					op = op->link;
				}
			}
			if(op == NULL){
				while(cp!=NULL)
				{
					if(ArrayCompare(cp->node->node_inform, upnode->node_inform))
					{
						if(cp->node->f > upnode->f){
							PushOpen(root, PopClose(&cp, upnode)->node);
							break;
						}
						else
							break;
					}
					else
					{
						cp = cp->link;
					}
				}
			}
			if(cp == NULL){
				PushOpen(root, upnode);
			}

		}
	}
	op = *root;
	if(leftzero == 1)
	{
		node leftnode;
		leftnode = (node)malloc(sizeof(nodestruct));

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++)
			{
				leftnode->node_inform[i][j] = left[i][j];	
				leftnode->g = m->g+1;
				leftnode->h = calculate_h(left);
				leftnode->f = (m->g + 1) + calculate_h(left);
				leftnode->pred = m;
			}
		}																// 노드생성

		if(Open_cnt==0){
			PushOpen(&op, leftnode);
			*root = op;
		}
		else{
			while(op !=NULL ){
				if(ArrayCompare(op->node->node_inform, leftnode->node_inform))
				{
					if(op->node->f > leftnode->f)
					{
						op->node->pred = m;
						op->node->f = leftnode->f;
						op->node->g = leftnode->g;
						break;
					}
					else
						break;
				}
				else
				{
					op = op->link;
				}
			}
			if(op == NULL){
				while(cp!=NULL)
				{
					if(ArrayCompare(cp->node->node_inform, leftnode->node_inform))
					{
						if(cp->node->f > leftnode->f){
							PushOpen(root, PopClose(&cp, leftnode)->node);
							break;
						}
						else
							break;
					}
					else
					{
						cp = cp->link;
					}
				}
			}
			if(cp == NULL){
				PushOpen(root, leftnode);
			}

		}
	}
	op = *root;
	if(downzero == 1)
	{
		node downnode;
		downnode = (node)malloc(sizeof(nodestruct));

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++)
			{
				downnode->node_inform[i][j] = down[i][j];	
				downnode->g = m->g+1;
				downnode->h = calculate_h(down);
				downnode->f = (m->g + 1) + calculate_h(down);
				downnode->pred = m;
			}
		}		
		//



		// 노드생성

		if(Open_cnt==0){
			PushOpen(&op, downnode);
			*root = op;
		}
		else{
			while(op !=NULL ){
				if(ArrayCompare(op->node->node_inform, downnode->node_inform))
				{
					if(op->node->f> downnode->f)
					{
						op->node->pred = m;
						op->node->f = downnode->f;
						op->node->g = downnode->g;
						break;
					}
					else
						break;
				}
				else
				{
					op = op->link;
				}
			}
			if(op == NULL){
				while(cp!=NULL)
				{
					if(ArrayCompare(cp->node->node_inform, downnode->node_inform))
					{
						if(cp->node->f > downnode->f){
							PushOpen(root, PopClose(&cp, downnode)->node);
							break;
						}
						else
							break;
					}
					else
					{
						cp = cp->link;
					}
				}
			}
			if(cp == NULL){
				PushOpen(root, downnode);
			}

		}
	}



	op = *root;
	if(rightzero == 1)
	{
		node rightnode;
		rightnode = (node)malloc(sizeof(nodestruct));

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++)
			{
				rightnode->node_inform[i][j] = right[i][j];	
				rightnode->g = m->g+1;
				rightnode->h = calculate_h(right);
				rightnode->f = (m->g + 1) + calculate_h(right);
				rightnode->pred = m;
			}
		}																// 노드생성

		if(Open_cnt==0){
			PushOpen(&op, rightnode);
			*root = op;
		}
		else{
			while(op !=NULL ){
				if(ArrayCompare(op->node->node_inform, rightnode->node_inform))
				{
					if(op->node->f> rightnode->f)
					{
						op->node->pred = m;
						op->node->f = rightnode->f;
						op->node->g = rightnode->g;
						break;
					}
				}
				else
				{
					op = op->link;
				}
			}
			if(op == NULL){
				while(cp!=NULL)
				{
					if(ArrayCompare(cp->node->node_inform, rightnode->node_inform))
					{
						if(cp->node->f > rightnode->f){
							PushOpen(root, PopClose(&cp, rightnode)->node);
							break;
						}
					}
					else
					{
						cp = cp->link;
					}
				}
			}
			if(cp == NULL){
				PushOpen(root, rightnode);
			}

		}		
	}




}

bool ArrayCompare(int node[4][4], int node1[4][4]){
	int i, j;
	for(i = 0; i<4; i++){
		for(j = 0; j<4; j++)
		{
			if(node[i][j] != node1[i][j])
			{
				return false;
			}			
		}
	}
	return true;

}
node swap(node n){

	node p = NULL;
	node q;
	node r;
	node newroot = NULL;
	while(1){

		q = p;
		p = n;
		if(n == NULL)
			return q;
		n = n->pred;
		p->pred = q;

	}

}
void ViewAstar(node n){
	FILE* fp;
	fp = fopen("output.txt","w");
	int i, j;
	int pre_i, pre_j;
	int cur_i, cur_j;
	int Final_i, Final_j;
	int cnt = 0;
	node p = swap(n);

	for(i = 0; i<4; i++){
		for(j = 0; j<4; j++){
			if(Final_node[i][j] == 0)
			{
				Final_i = i;
				Final_j = j;
			}
		}
	}



	while(p !=NULL){
		if(cnt ==0){
			printf("[%d] This is the start state\n", cnt);
			fprintf(fp, "[%d] This is the start state\n", cnt);
		}
		else{
			printf("[%d]\n", cnt);
			fprintf(fp, "[%d]\n", cnt);
		}
		cnt ++;
		for(i = 0; i<4; i++){
			for(j = 0; j<4; j++){

				if(p->node_inform[i][j] == 0){
					printf("%2c", ' ');
					fprintf(fp, "%2c", ' ');
						cur_i = i;
						cur_j = j;
						if(p->pred !=NULL){
						pre_i = search_zero_x(p->pred->node_inform);
						pre_j = search_zero_y(p->pred->node_inform);
						}
					
				}
				else{
					printf("%2d", p->node_inform[i][j]);
					fprintf(fp, "%2d", p->node_inform[i][j]);
				}
				printf(" ");
				fprintf(fp, " ");
			}
			printf("\n");
			fprintf(fp, "\n");
		}
		
		if(cur_i == Final_i && cur_j == Final_j){
			printf("This is goal! Success!\n");
			fprintf(fp, "This is goal! Success!\n");
		}
		else
		{
			if(cur_i-pre_i == 0 && cur_j - pre_j == -1){
				printf("==>move right\n");
				fprintf(fp, "==>move right\n");
			}
			else if(cur_i - pre_i == -1 && cur_j-pre_j == 0){
				printf("==>move down\n");
				fprintf(fp, "==>move down\n");
			}
			else if(cur_i - pre_i == 1 && cur_j-pre_j == 0){
				printf("==>move up\n");
				fprintf(fp, "==>move up\n");
			}
			else if(cur_i - pre_i == 0 && cur_j-pre_j == 1){
				printf("==>move left\n");
				fprintf(fp, "==>move left\n");
			}
		}
		p = p->pred;

	}
	printf("Number of moves required = %d\n", cnt-1);
	fprintf(fp,"Number of moves required = %d\n", cnt-1);
	fclose(fp);
}
int search_zero_x(int n[4][4]){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			if(n[i][j] == 0){
				return i;
			}
		}
	}

}
int search_zero_y(int n[4][4]){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			if(n[i][j] == 0){
				return j;
			}
		}
	}
}

