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
	//파일 이름은 “00_201500000_insertion.txt”
	//입출력 파일은 *.c 소스파일과 같은 폴더에 있어야 한다.
	int i=0;
	int* data = NULL;
	int num;
	int cnt=0;
		int p=0;
	int key ,o,a;

	fp = fopen("data02.txt","rt"); //입력 파일 열기
	fop = fopen("00_201302481_정우식_binary.txt","wt"); //출
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
	
	insertionSort(data,cnt);

	while(p<cnt){
		fprintf(fop,"%d,",data[p]);
		p++;
	}
}