#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
//definition of pointers to the input files
FILE * fp_A;FILE * fp_B;FILE * fp_R;FILE * fp_O;
//definitions of clock variables
int C_2=1;int C_6=0;int C_75=0;int C_13=0;int C_77=0;int C_26=0;int C_79=0;int C_86=0;int C_92=0;int C_84=0;int C_82=0;
//definition of parameters

//definition of input variables
int A;int B;int R;
//definition of output variables
int O;
//definition of intermediate variables
int c_A_r_R;int c_B_r_R;int c_af_R;int c_A_R;int c_B_R;int nR;int nO;int c_A_received;int c_B_received;int c_after_R_until_O;int c_A;int c_B;int c_R;int A_received;int B_received;int from_R_before_O;int Adelay;int Bdelay;int AR;int BR;int RR;int ABR;int Arr;int after_R_until_O;int AT;int BT;int RT;int Re;
int open_r_A(){
	fp_A=fopen("A.txt","r");
	if(fp_A==NULL){
		return 0;
	}
	return 1;
}
int read_A(){
	for(int i=0;i<100;i++){
	printf("section A+%d,threadid=%d\n",i,omp_get_thread_num());
	}
	return (fscanf(fp_A,"%d",&A));
}
int open_r_B(){
	fp_B=fopen("B.txt","r");
	if(fp_B==NULL){
		return 0;
	}

	return 1;
}
int read_B(){
	for(int i = 0; i< 100;i++){
		printf("section B+%d,threadid=%d\n",i,omp_get_thread_num());
	}
	return (fscanf(fp_B,"%d",&B));
}
int open_r_R(){
	fp_R=fopen("R.txt","r");
	if(fp_R==NULL){
		return 0;
	}
	return 1;
}
int read_R(){
	for(int i = 0; i< 100;i++){
		printf("section C+%d,threadid=%d\n",i,omp_get_thread_num());
	}
	return (fscanf(fp_R,"%d",&R));
}
int open_w_O(){
	fp_O=fopen("O.txt","w");
	if(fp_O==NULL){
		return 0;
	}
	return 1;
}
void write_O(){
	fprintf(fp_O,"%d ",O);
}
int initialIO(){
	if(open_r_A()==0){
		return 0;
	}
	if(open_r_B()==0){
		return 0;
	}
	if(open_r_R()==0){
		return 0;
	}
	if(open_w_O()==0){
		return 0;
	}
	return 1;
}
void closeIO(){
	if(fp_A!=NULL){
		fclose(fp_A);
	}
	if(fp_B!=NULL){
		fclose(fp_B);
	}
	if(fp_R!=NULL){
		fclose(fp_R);
	}
	if(fp_O!=NULL){
		fclose(fp_O);
	}
}
void initialState(){
	Adelay=0;
	Bdelay=0;
	after_R_until_O=1;
}
void initialStep(){
}
int core(){
	int mark=0;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			c_after_R_until_O=after_R_until_O==after_R_until_O;
		}
		#pragma omp section
		{
			if(read_A()==EOF)
				mark=1;
				//printf("section 0,threadid=%d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			if(read_B()==EOF)
				mark=1;
				//printf("section 0,threadid=%d\n",omp_get_thread_num());
		}
		#pragma omp section
		{
			if(read_R()==EOF)
				mark=1;
		}
	}
	if(mark==1)
		return 0;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			C_13=C_2&&A;
		}
		#pragma omp section
		{
			C_26=C_2&&B;
		}
		#pragma omp section
		{
			C_6=C_2&&R;
		}
	}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			c_A=A==A;
		}
		#pragma omp section
		{
			c_B=B==B;
		}
		#pragma omp section
		{
			c_R=R==R;
		}
		#pragma omp section
		{
			nR=!R;
		}
		#pragma omp section
		{
			if(C_13!=0){
				AT=A;
			}
		}
		#pragma omp section
		{
			if(C_26!=0){
				BT=B;
			}
		}
		#pragma omp section
		{
			if(C_6!=0){
				Re=R;
			}
		}
		#pragma omp section
		{
			C_77=C_2&& !C_13;
		}
		#pragma omp section
		{
			C_79=C_2&& !C_26;
		}
		#pragma omp section
		{
			C_75=C_2&& !C_6;
		}
	}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			c_af_R=c_after_R_until_O==c_R;
		}
		#pragma omp section
		{
			c_A_R=c_A==c_R;
		}
		#pragma omp section
		{
			c_B_R=c_B==c_R;
		}
		#pragma omp section
		{
			if(C_6!=0){
				RT=nR;
			}
		}
		#pragma omp section
		{
			if(C_13!=0){
				AR=AT;
			}
		}
		#pragma omp section
		{
			if(C_77!=0){
				AR=Adelay;
			}
		}
		#pragma omp section
		{
			if(C_26!=0){
				BR=BT;
			}
		}
		#pragma omp section
		{
			if(C_79!=0){
				BR=Bdelay;
			}
		}
		#pragma omp section
		{
			if(C_6!=0){
				RR=Re;
			}
		}
		#pragma omp section
		{
			if(C_75!=0){
				RR=after_R_until_O;
			}
		}
	}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			if(C_6!=0){
				A_received=RT;
			}
		}
		#pragma omp section
		{
			if(C_75!=0){
				A_received=AR;
			}
		}
		#pragma omp section
		{
			if(C_6!=0){
				B_received=RT;
			}
		}
		#pragma omp section
		{
			if(C_75!=0){
				B_received=BR;
			}
		}
		#pragma omp section
		{
			C_82=C_2&&after_R_until_O;
		}
	}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			c_A_received=A_received==A_received;
		}
		#pragma omp section
		{
			c_B_received=B_received==B_received;
		}
		#pragma omp section
		{
			if(C_82!=0){
				Arr=B_received;
			}
		}
	}
	C_84=C_82&&Arr;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			c_A_r_R=c_A_received==c_R;
		}
		#pragma omp section
		{
			c_B_r_R=c_B_received==c_R;
		}
		#pragma omp section
		{
			if(C_84!=0){
				ABR=A_received;
			}
		}
	}
	C_86=C_84&&ABR;

			if(C_86!=0){
				O=1;
				write_O();
			}else{
				O=0;
				write_O();
			}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			if(C_86!=0){
				nO=!O;
			}
		}
		#pragma omp section
		{
			C_92=C_2&& !C_86;
		}
	}
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			if(C_86!=0){
				from_R_before_O=nO;
			}
		}
		#pragma omp section
		{
			if(C_92!=0){
				from_R_before_O=RR;
			}
		}
	}
	return 1;
}
void finalStep(){
	Adelay=A_received;
	Bdelay=B_received;
	after_R_until_O=from_R_before_O;
	C_6=0;
	C_75=0;
	C_13=0;
	C_77=0;
	C_26=0;
	C_79=0;
	C_86=0;
	C_92=0;
	C_84=0;
	C_82=0;
}
void iteration(){
	initialState();
	while(1){
		initialStep();
		if(core()==0)
			break;
		finalStep();
	}
}
int main(){
	clock_t start,end;
	start=clock();



	if(initialIO()==0){
		printf("files not found");
		exit(1);
	}
	//for(int i=1;i<1000;i++){
	iteration();
	closeIO();
//	}
	end=clock();
	printf("The time is %f ms",difftime(end,start));
	return 0;
}
