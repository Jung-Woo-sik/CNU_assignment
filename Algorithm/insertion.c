#include<stdio.h>
#include<stdlib.h>

int main(){

	FILE* fp; //fp : input file pointer
	FILE* fop; //fop : input file pointer
	//���� �̸��� ��00_201500000_insertion.txt��
	//����� ������ *.c �ҽ����ϰ� ���� ������ �־�� �Ѵ�.
	int i=0;
	int* data = NULL;
	int num;
	int cnt=0;
		int p=0;
	int key ,o,a;

	fp = fopen("data02.txt","rt"); //�Է� ���� ����
	fop = fopen("00_201302481_insertion.txt","wt"); //��
	if (fp == NULL) {
		printf("**** Input File open error ****\n");
		exit(1);
	} //���� ���� ��� ����ó���� ���α׷� ����	

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