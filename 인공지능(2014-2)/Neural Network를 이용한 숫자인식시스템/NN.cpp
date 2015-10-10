#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NLayer 3	// layer의 수
#define MLayerSize 65	// max layer size(즉 layer가 가질 수 있는 최대 뉴론의 수)
#define m0 3
#define m1 3
#define m2 3		// 출력신호의 수 m2
#define N 65	// dummy input 1 포함
#define N_tr_examples 600			//600개의 훈련 예
#define N_te_examples 90			// 90개의 훈련 예


int M[NLayer] = {m0, m1, m2};			// 변수 M에도 가지고 있음
double s[NLayer][MLayerSize];
double f[NLayer][MLayerSize];
double delta[NLayer][MLayerSize];
double W[NLayer][MLayerSize][MLayerSize];			// 층, 뉴론번호, 가중치번호
double c = 0.1;
double threshold = 0.05;

int TrainData[N_tr_examples][N], d_tr[N_tr_examples][m2];			// main에서 처음에 화일로 훈련데이타를 읽어서 채운다.
int TestData[N_te_examples][N], d_te[N_te_examples][m2];			// main에서 처음에 화일로부터 테스트 데이타를 읽어서 채운다.
int input[N];		// training data의 한 줄을 읽어서 이 변수를 채움
int d[N_tr_examples][m2];			// 정답레이블을 가지는 변수 D, training data의 각 줄의 첫 숫자를 이용하여 이를 채움
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
	//초기화
	for(i = 0; i<NLayer; i++){
		for(j = 0; j<MLayerSize; j++){
			s[i][j] = 0;
			f[i][j] = 0;
			delta[i][j] = 0;
		}
	}



	initialization();		// 가중치 벡터의 초기화


	FILE *fp, *fp1;
	fp = fopen("traindata.txt", "r");fp1 = fopen("testdata.txt", "r");//입력신호 가져오기
	while(!feof(fp)){
		fscanf(fp, "%d", &a);
		for(i = 0; i<m2; i++){
			if(a == i)	
				d[col][i] = 1;
			else	
				d[col][i] = 0;		
		}	
		fscanf(fp, " %c ", &c);		c = '0';	// $버리기
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
		fscanf(fp1, " %c ", &c);	c = '0';	// $버리기
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
		for(int t=0; t<=N_tr_examples-1; t++){		// 한 에폭의 훈련과정
			forward_compute(t);
			backward_compute(t);
			weight_update(t);
		}
		epoch++;
		for(int t = 0; t<=N_tr_examples-1; t++){	// 한 에폭 후 평균 에러 계산
			// t번쨰 훈련예제를 이용하여 시스템의 출력을 구해 error를 구함
			forward_compute(t);													//  t 번째 훈련예를 투입하여 출력을 구함

			for(i = 0; i<=M[NLayer-1]-1 ; i++){									       // 최종층의 출력을 이용하여 에러를 구함.
				sum_sq_error+=pow((d[t][i]-f[NLayer-1][i]),2);					
			}
		}
		avg_sq_error = sum_sq_error/(N_tr_examples*M[NLayer-1]);						//모든 훈련 예에 대하여 평균 square 에러를 계산함
		printf("%d epoch error rate = %lf\n",epoch,avg_sq_error);

		/*        Fail 부분, 임계치 이하로 떨어지면 너무 쉽게 결과가 나오는 현상이 일어났습니다.
		dif = pre_avg_sq_error - avg_sq_error;
		if(dif < 0)
			dif = -dif;
		printf("dif = %lf\n", dif);
		*/

	}while(threshold < avg_sq_error) ;
		//&& (threshold < dif));				//avg_sq_error 가 임계치 이하이면 종료, 
	//또는 이전 epoch 에서의 avg_sq_error 와 이번 epoch 의 avg_sq_error  의 차이가       임계치 이하이면 종료


	for(int t = 0; t<=N_te_examples-1; t++){
		// TestData[t], d_te[t] 를 input,d에 넣는다.
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

void initialization(){	//모든 가중치 W  벡터를 random number 로 초기화 함, PPT코드 인용
	int i,j,k;
	int pre_layer;
	double r;

	srand((unsigned)time(NULL));

	for(i=0; i<NLayer; i++){
		for(j=0; j<M[i]; j++){		
			if(i==0)					// i층 앞층의 뉴론의 수를 가져옴.
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
void forward_compute(int a){		// Forward 계산, ppt코드 인용
	int i, j, L;
	for(i=0; i<NLayer; i++)				// 초기화
	{
		for(j=0; j<N; j++){
			s[i][j] = 0;
			f[i][j] = 0;				
			delta[i][j]=0;
		}
	}
	for(i=0; i<=M[0]-1; i++){				// 층 0층의 계산 , 여기서 s의 계산에서 입력벡터는 TrainData가 됨
		for(j=0; j<=N-1; j++){
			s[0][i] += (double)TrainData[a][j]*W[0][i][j];
		}
		f[0][i]=1/(1+exp(-1*s[0][i]));
	}
	for(L=1; L<NLayer; L++) {			// 층 1,2에 대한 s및 f의 계산
		for(i=0; i<=M[L]-1; i++) {			// 이 L층의 뉴론 i에 대하여
			for(j=0; j<M[L-1]+1; j++) {
				if(j == M[L-1])			// s의 계산
					s[L][i] += 1*W[L][i][j];	// 더미 입력처리
				else s[L][i] += f[L-1][j]*W[L][i][j];
			}
			f[L][i]=1/(1+exp(-s[L][i]));		// f의 계산
		}
	}
}
void backward_compute(int a){		//Backward계산, ppt코드 인용
	int i,j,k,L;
	double tsum=0;
	k=NLayer-1;				// 최종층 번호


	for(i=0; i<=M[k]-1; i++){		// 최종층의 각 뉴론 i에 대하여
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
void weight_update(int a)		// 가중치 갱신작업, ppt코드 인용
{
	int i,j,L;
	for(L=1; L<=NLayer-1; L++){		// L>0인 층들에 대한 처리
		for(i=0; i<M[L]; i++){
			for(j=0; j<M[L-1]+1; j++){
				W[L][i][j] += c*delta[L][i]*f[L-1][j];
			}
		}
	}
	for(i=0; i<=M[0]-1; i++){			// L=0인경우 즉 층0의 뉴론에 대한 처리
		for(j=0; j<N; j++){
			W[0][i][j] += c*delta[0][i]*TrainData[a][j];
		}
	}
}
void t_forward_compute(int a)	// forward_compute 변형버전
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
