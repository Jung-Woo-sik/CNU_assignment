#include<stdio.h>
#include<stdlib.h>

void merge(int* array, int start, int mid, int end){
	int* tmp=(int*)malloc(sizeof(int)*(end-start+1));
    int tmp_index=0;
    int p=start,q=mid+1;
    int i;
 
    for(i=tmp_index; i<=end-start; i++){
        while(p<=mid && q<=end){
            if(array[p]>array[q]){
                tmp[tmp_index]=array[q];
                q++;
            }else{
                tmp[tmp_index]=array[p];
                p++;
            }
            tmp_index++;
        }
 
        if(p>mid){
            while(q<=end){
                tmp[tmp_index]=array[q];
                q++;
                tmp_index++;
            }
        }
        else{
            while(p<=mid){
                tmp[tmp_index]=array[p];
                p++;
                tmp_index++;
            }
        }
    }//end for
 
    for(i=start; i<=end; i++){
        array[i]=tmp[i-start];
    }
 
    free(tmp);
}
void merge_sort(int* array, int start, int end){
    int mid; 
	if(start>=end) return;   
 
	mid = (start+end)/2;
    merge_sort(array,start,mid);
    merge_sort(array,mid+1,end);
 
    merge(array,start,mid,end);
}
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
	fop = fopen("00_201302481_�����_merge.txt","wt"); //��
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

	merge_sort(data,0,cnt-1);
	while(p<cnt){
		fprintf(fop,"%d,",data[p]);
		p++;
	}
}