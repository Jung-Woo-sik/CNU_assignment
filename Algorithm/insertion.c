#include<stdio.h>
#include<stdlib.h>

int main(){

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

	fp = fopen("data02.txt","rt"); //입력 파일 열기
	fop = fopen("00_201302481_insertion.txt","wt"); //출
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
	
	for(o = 1; o<cnt; o++)
	{
		key = data[o];
		a = o - 1; 
		while(a>=0 && data[a]>key)
		{ 
			data[a+1] = data[a];
			a = a - 1;
		} 
		data[a+1] = key; 
	}

	while(p<cnt){
		fprintf(fop,"%d,",data[p]);
		p++;
	}
}