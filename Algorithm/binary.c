#include<stdio.h>
#include<stdlib.h>

int binarySearch(int* a, int item, int low, int high)
{
	int mid;
    if (high <= low)
        return (item > a[low])?  (low + 1): low;
 
    mid = (low + high)/2;
 
    if(item == a[mid])
        return mid+1;
 
    if(item > a[mid])
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}
 
void insertionSort(int *a, int n)
{
    int i, loc, j, k, selected;
 
    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];
 
        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);
 
        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
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
	fop = fopen("00_201302481_�����_binary.txt","wt"); //��
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
	
	insertionSort(data,cnt);

	while(p<cnt){
		fprintf(fop,"%d,",data[p]);
		p++;
	}
}