#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t)) 
int Partition(int * arr , int left,int right);
void QuickSort(int * arr,int left ,int right);
void Random_QuickSort(int * arr,int left ,int right);
int Randomized_Partition(int * arr , int left,int right);
void Random_QuickSort(int * arr,int left ,int right){
	if(left<right)
	{
		int q = Randomized_Partition(arr,left,right);
		Random_QuickSort(arr,left,q-1);
		Random_QuickSort(arr,q+1,right);
	}
}
int Randomized_Partition(int * arr , int left,int right){
	int i,temp;
	i = left + rand()%(right-left);
	SWAP(arr[right],arr[i],temp);
	return Partition(arr,left,right);
}
void QuickSort(int * arr,int left ,int right){
	if(left<right)
	{
		int q = Partition(arr,left,right);
		QuickSort(arr,left,q-1);
		QuickSort(arr,q+1,right);
	}
}
int Partition(int * arr , int left,int right){
	int pivot,temp;
	int low,high;

	low = left;
	high = right+1;
	pivot = arr[left];
	do{
		do
			low++;
		while(arr[low]<pivot);

		do
			high--;
		while(arr[high]>pivot);

		if(low<high) SWAP(arr[low],arr[high],temp);
	}while(low<high);

	SWAP(arr[left],arr[high],temp);
	return high;
}
int main(){
	clock_t start_time, end_time;  

	FILE* fp; //fp : input file pointer
	FILE* fop; //fop : input file pointer
	//파일 이름은 “00_201500000_insertion.txt”
	//입출력 파일은 *.c 소스파일과 같은 폴더에 있어야 한다.
	int i=0;
	int* data = NULL;
	int num;
	int cnt=0;
		int p=0;
	int key ,o,a;
	start_time = clock(); 

	fp = fopen("data04.txt","rt"); //입력 파일 열기
	fop = fopen("00_201302481_정우식_quick.txt","wt"); //출
	if (fp == NULL) {
		printf("**** Input File open error ****\n");
		exit(1);
	} //파일 없을 경우 예외처리로 프로그램 종료	

	while(!feof(fp)) {
		fscanf(fp,"%d,",&data);
		cnt++;
	}
	fseek(fp,0,SEEK_SET);
	data = (int*)malloc(sizeof(int)*cnt);
	while(i<cnt){
		fscanf(fp,"%d,",&data[i]);
		i++;
	}
	QuickSort(data,0,cnt-1);
	//Random_QuickSort(data,0,cnt-1);
	while(p<cnt){
		fprintf(fop,"%d,",data[p]);
		p++;
	}
	end_time = clock();
	 printf("Time : %f\n", ((double)(end_time-start_time)) / CLOCKS_PER_SEC);  
}