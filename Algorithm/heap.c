#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PARENT(i) (i+1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

void Heap_sort(int *arr,int size);
void build_Max_Heap(int *arr, int n);
void max_Heapify(int *arr,int n);
void insert(int *arr, int x, int size);
int extract_max(int *arr,int size);
void increase_key(int *arr,int x,int k,int size);
int H_max(int *arr, int size);
void H_delete(int *arr, int x, int size);
void complete_Heap_Sort(int *arr,int size);
void swap(int *x,int *y);


void swap(int *x, int *y){
	int tmp;
	tmp=*x;
	*x=*y;
	*y=tmp;
}
void Heap_sort(int *arr,int size){
	int i,temp;									
 
	build_Max_Heap(arr,size);							
 
	for(i=size-1 ; i>0 ; i--)						
	{
		temp = arr[0];							
		arr[0] = arr[i];
		arr[i] = temp;
		max_Heapify(arr,i);						
	}
}
void build_Max_Heap(int *arr, int n)					
{
	int item,i,j,k;								
 
	for(k=1 ; k<n ; k++)						
	{
		item = arr[k];							
		i = k;
		j = (i-1)/2;
 
		while( (i>0) && (item>arr[j]) )			
		{
			arr[i] = arr[j];					
			i = j;
			j = (i-1)/2;
		}
		arr[i] = item;
	}
}
 
 
void max_Heapify(int *arr, int size)					
{
	int item,i=1,j=0;
 
	item = arr[j];
 
	while(i<=size-1)								
	{
		if(i+1 <= size-1)							
			if(arr[i] < arr[i+1])				
				i++;							
		if(item < arr[i])						
		{
			arr[j] = arr[i];					
			j = i;								
			i = 2*j+1;
		}
		else									
			break;
	}
	arr[j] = item;								
}

void insert(int *arr, int x, int size){
	arr = (int*)realloc(arr, sizeof(int)*(size+1));
	arr[size] = x;
	
	build_Max_Heap(arr,size+1);
}

void H_delete(int *arr, int x, int size){

	arr[x-1] =arr[size-1];
	arr[size-1] = NULL;
	arr = (int*)realloc(arr, sizeof(int)*(size-1));
	build_Max_Heap(arr,size-1);
}

int extract_max(int *arr, int size){
	int i,a;
	build_Max_Heap(arr,size);
	printf("build_max_heap Result:\n");
	for(i=0; i<size;i++)
		printf("%d",arr[i]);
	
	a= arr[0];
	H_delete(arr,1,size);

	return a;
}

int H_max(int *arr, int size){
	build_Max_Heap(arr,size);

	return arr[0];
}
void increase_key(int *arr, int x, int k, int size){
	int i;

	if(k>arr[x-1]){
		arr[x-1]=k;
		build_Max_Heap(arr,size);
		printf("\n(increase_max(s) Result:\n");
		for(i=0; i<size;i++){
			printf("%d",arr[i]);
		}
	}
	else{
		printf("Increase_key : k값이 더 작습니다.\n");
	}
}
void complete_Heap_Sort(int *arr,int size){
	int i;
	Heap_sort(arr,size);
   
	for (i=0;i<=size/2;i++){
		swap(&arr[i], &arr[size-i-1]);
   }
}

void main()
{
	FILE *fp = fopen("data03.txt", "rt");		//읽을 파일을 파일포인터에 저장
	FILE *fop = fopen("00_201302481_정우식_heap.txt", "wt");	//쓸 파일을 파일포인터에 저장

	int cnt = 0;								
	int* d = (int*)malloc(sizeof(int));			
	int* c; 
	char str;
	int num,i,tmp;

	while(!feof(fp)) {							
		fscanf(fp,"%c.%d, ",&str,&num);				

		for(cnt=0; num>0;cnt++){
			d = (int*)realloc(d, sizeof(int)*(cnt+1));	
			d[cnt]= num%10;
			num = num/10;
		}
		c = (int*)malloc(sizeof(int)*cnt);		
		
		for(i=0; i<cnt;i++){
			c[i] = d[cnt-i-1];	
		}

		switch(str){
		case 'a':
			
			build_Max_Heap(c,cnt);
			
			printf("Insert\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
			}
			printf("\n");
			
			insert(c,9,cnt);
			
			printf("Insertion Result :\n");
			for(i=0; i<=cnt;i++){
				printf("%d",c[i]);
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			printf("\n\n");

			break;
		case 'b':
			
			tmp = H_max(c,cnt);
			printf("build_max_heap Result:\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
			}
			printf("\n");
			printf("(H_max(s) Result :\n");
			printf("%d\n",tmp);
			printf("\n\n");
			for(i=0; i<cnt;i++){
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			break;
		case 'c':
			tmp = extract_max(c,cnt);
			printf("\n extract_max(s) Result :\n");
			printf("%d",tmp);
			printf("\n\n");
			for(i=0; i<cnt-1;i++){
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			break;
		case 'd':
			build_Max_Heap(c,cnt);
			printf("build_max_heap Result :\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
			}
			printf("\n");
			increase_key(c,1,5,cnt);
			printf("\n\n");
			for(i=0; i<cnt;i++){
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			break;
		case 'e':
			build_Max_Heap(c,cnt);
			printf("build_max_heap Result:\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
			}

			H_delete(c,5,cnt);
			printf("\nH_delete(S,x) Result :\n");
			for(i=0; i<cnt-1;i++){
				printf("%d",c[i]);
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			printf("\n");
			break;
		case 'f':
			build_Max_Heap(c,cnt);
			printf("build_max_heap Result:\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			printf("\n");
			break;
		case 'g':
			complete_Heap_Sort(c,cnt);
			printf("complete_Heap_Sort Result :\n");
			for(i=0; i<cnt;i++){
				printf("%d",c[i]);
				fprintf(fop, "%d", c[i]);
			}
			fprintf(fop, ", ");
			printf("\n\n");
			break;
		}

		

	}
	
	fclose(fp);
	fclose(fop);
}

