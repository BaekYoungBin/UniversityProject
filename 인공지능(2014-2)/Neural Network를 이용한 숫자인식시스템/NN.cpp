#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NLayer 3	// layer�� ��
#define MLayerSize 65	// max layer size(�� layer�� ���� �� �ִ� �ִ� ������ ��)
#define m0 3
#define m1 3
#define m2 3		// ��½�ȣ�� �� m2
#define N 65	// dummy input 1 ����
#define N_tr_examples 600			//600���� �Ʒ� ��
#define N_te_examples 90			// 90���� �Ʒ� ��


int M[NLayer] = {m0, m1, m2};			// ���� M���� ������ ����
double s[NLayer][MLayerSize];
double f[NLayer][MLayerSize];
double delta[NLayer][MLayerSize];
double W[NLayer][MLayerSize][MLayerSize];			// ��, ���й�ȣ, ����ġ��ȣ
double c = 0.1;
double threshold = 0.05;

int TrainData[N_tr_examples][N], d_tr[N_tr_examples][m2];			// main���� ó���� ȭ�Ϸ� �Ʒõ���Ÿ�� �о ä���.
int TestData[N_te_examples][N], d_te[N_te_examples][m2];			// main���� ó���� ȭ�Ϸκ��� �׽�Ʈ ����Ÿ�� �о ä���.
int input[N];		// training data�� �� ���� �о �� ������ ä��
int d[N_tr_examples][m2];			// ���䷹�̺��� ������ ���� D, training data�� �� ���� ù ���ڸ� �̿��Ͽ� �̸� ä��
int Td[N_tr_examples][m2];
void initialization();
void forward_compute(int a);
void backward_compute(int a);
void weight_update(int a);
double avg_sq_error = 0 ;
void t_forward_compute(int a);


int main(){

	int a,b;
	char c;
	int i;
	int j;
	double dif;
	int col = 0;
	double sum_sq_error = 0 ;
	int epoch=0;
	double pre_avg_sq_error = 0;
	double accuracy = 0;
	double max = 0;
	int num_correct= 0, tmp, k;
	//�ʱ�ȭ
	for(i = 0; i<NLayer; i++){
		for(j = 0; j<MLayerSize; j++){
			s[i][j] = 0;
			f[i][j] = 0;
			delta[i][j] = 0;
		}
	}



	initialization();		// ����ġ ������ �ʱ�ȭ


	FILE *fp, *fp1;
	fp = fopen("traindata.txt", "r");fp1 = fopen("testdata.txt", "r");//�Է½�ȣ ��������
	while(!feof(fp)){
		fscanf(fp, "%d", &a);
		for(i = 0; i<m2; i++){
			if(a == i)	
				d[col][i] = 1;
			else	
				d[col][i] = 0;		
		}	
		fscanf(fp, " %c ", &c);		c = '0';	// $������
		for(i = 0; i<N; i++){
			fscanf(fp, "%d", &b);
			TrainData[col][i] = b;
		}
		col ++;
	}
	col = 0;a = 0;b = 0;
	while(!feof(fp1)) {
		fscanf(fp1, "%d", &a);
		for(i=0; i<m2; i++) {
			if(a==i) 
				Td[col][i]=1;
			else 
				Td[col][i]=0;		
		}
		fscanf(fp1, " %c ", &c);	c = '0';	// $������
		for(i=0; i<N; i++) {
			fscanf(fp1, " %d",  &b);
			TestData[col][i]=b;		
		}
		col++;
	}
	//file input


	do{
		pre_avg_sq_error = avg_sq_error;
	//	printf("pre = %lf\n", pre_avg_sq_error);
		avg_sq_error=0, sum_sq_error=0;
		for(int t=0; t<=N_tr_examples-1; t++){		// �� ������ �Ʒð���
			forward_compute(t);
			backward_compute(t);
			weight_update(t);
		}
		epoch++;
		for(int t = 0; t<=N_tr_examples-1; t++){	// �� ���� �� ��� ���� ���
			// t���� �Ʒÿ����� �̿��Ͽ� �ý����� ����� ���� error�� ����
			forward_compute(t);													//  t ��° �Ʒÿ��� �����Ͽ� ����� ����

			for(i = 0; i<=M[NLayer-1]-1 ; i++){									       // �������� ����� �̿��Ͽ� ������ ����.
				sum_sq_error+=pow((d[t][i]-f[NLayer-1][i]),2);					
			}
		}
		avg_sq_error = sum_sq_error/(N_tr_examples*M[NLayer-1]);						//��� �Ʒ� ���� ���Ͽ� ��� square ������ �����
		printf("%d epoch error rate = %lf\n",epoch,avg_sq_error);

		/*        Fail �κ�, �Ӱ�ġ ���Ϸ� �������� �ʹ� ���� ����� ������ ������ �Ͼ���ϴ�.
		dif = pre_avg_sq_error - avg_sq_error;
		if(dif < 0)
			dif = -dif;
		printf("dif = %lf\n", dif);
		*/

	}while(threshold < avg_sq_error) ;
		//&& (threshold < dif));				//avg_sq_error �� �Ӱ�ġ �����̸� ����, 
	//�Ǵ� ���� epoch ������ avg_sq_error �� �̹� epoch �� avg_sq_error  �� ���̰�       �Ӱ�ġ �����̸� ����


	for(int t = 0; t<=N_te_examples-1; t++){
		// TestData[t], d_te[t] �� input,d�� �ִ´�.
		t_forward_compute(t);
		max=0.;
		for(j=0; j<NLayer; j++) {	
			if(max < f[NLayer-1][j]) {
				max = f[NLayer-1][j];
				tmp = j;
			}
		}
		for(k=0; k<NLayer; k++) {
			if(Td[t][k] == 1 && tmp == k)
				num_correct++;
		}
	}
	accuracy =  (double)num_correct/(double)N_te_examples;
	printf("Accuracy = %lf", accuracy);

	fclose(fp);
	fclose(fp1);
}

void initialization(){	//��� ����ġ W  ���͸� random number �� �ʱ�ȭ ��, PPT�ڵ� �ο�
	int i,j,k;
	int pre_layer;
	double r;

	srand((unsigned)time(NULL));

	for(i=0; i<NLayer; i++){
		for(j=0; j<M[i]; j++){		
			if(i==0)					// i�� ������ ������ ���� ������.
				pre_layer = 64;
			else
				pre_layer = M[i-1];
			for(k=0; k<pre_layer; k++){
				r = double(rand());
				W[i][j][k] = r/double(RAND_MAX);
			}
		}
	}
}
void forward_compute(int a){		// Forward ���, ppt�ڵ� �ο�
	int i, j, L;
	for(i=0; i<NLayer; i++)				// �ʱ�ȭ
	{
		for(j=0; j<N; j++){
			s[i][j] = 0;
			f[i][j] = 0;				
			delta[i][j]=0;
		}
	}
	for(i=0; i<=M[0]-1; i++){				// �� 0���� ��� , ���⼭ s�� ��꿡�� �Էº��ʹ� TrainData�� ��
		for(j=0; j<=N-1; j++){
			s[0][i] += (double)TrainData[a][j]*W[0][i][j];
		}
		f[0][i]=1/(1+exp(-1*s[0][i]));
	}
	for(L=1; L<NLayer; L++) {			// �� 1,2�� ���� s�� f�� ���
		for(i=0; i<=M[L]-1; i++) {			// �� L���� ���� i�� ���Ͽ�
			for(j=0; j<M[L-1]+1; j++) {
				if(j == M[L-1])			// s�� ���
					s[L][i] += 1*W[L][i][j];	// ���� �Է�ó��
				else s[L][i] += f[L-1][j]*W[L][i][j];
			}
			f[L][i]=1/(1+exp(-s[L][i]));		// f�� ���
		}
	}
}
void backward_compute(int a){		//Backward���, ppt�ڵ� �ο�
	int i,j,k,L;
	double tsum=0;
	k=NLayer-1;				// ������ ��ȣ


	for(i=0; i<=M[k]-1; i++){		// �������� �� ���� i�� ���Ͽ�
		delta[k][i]=(d[a][i]-f[k][i])*f[k][i]*(1-f[k][i]);
	}
	for(L=NLayer-2; L>=0; L--){
		for(i=0; i<=M[L]-1; i++){
			for(j=0; j<M[L+1]; j++){
				tsum += delta[L+1][j]*W[L+1][j][i];
			}
			delta[L][i] = f[L][i]*(1-f[L][i])*tsum;
		}
	}
}
void weight_update(int a)		// ����ġ �����۾�, ppt�ڵ� �ο�
{
	int i,j,L;
	for(L=1; L<=NLayer-1; L++){		// L>0�� ���鿡 ���� ó��
		for(i=0; i<M[L]; i++){
			for(j=0; j<M[L-1]+1; j++){
				W[L][i][j] += c*delta[L][i]*f[L-1][j];
			}
		}
	}
	for(i=0; i<=M[0]-1; i++){			// L=0�ΰ�� �� ��0�� ���п� ���� ó��
		for(j=0; j<N; j++){
			W[0][i][j] += c*delta[0][i]*TrainData[a][j];
		}
	}
}
void t_forward_compute(int a)	// forward_compute ��������
{
	int i, j, L;
	for(i=0; i<NLayer; i++) {
		for(j=0; j<=N-1; j++) {
			s[i][j] = 0; 
			f[i][j] = 0;
			delta[i][j]=0;
		}
	}
	for(i=0; i<=M[0]-1; i++){
		for(j=0; j<=N-1; j++){
			s[0][i] += (double)TestData[a][j]*W[0][i][j];
		}

		f[0][i]=1./(1+exp(-1*s[0][i]));
	}
	for(L=1; L<NLayer; L++) {
		for(i=0; i<=M[L]-1; i++) {
			for(j=0; j<M[L-1]+1; j++) {
				if(j == M[L-1])
					s[L][i] += 1*W[L][i][j];	
				else s[L][i] += f[L-1][j]*W[L][i][j];
			}
			f[L][i]=1/(1+exp(-s[L][i]));
		}
	}
}
