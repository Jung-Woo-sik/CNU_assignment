#include <stdio.h>
int binary_search(int* array, int start, int end, int key){
    
	 int mid;
	if(start>end) return 0;
 
   
	mid=(start+end)/2;
 
    if(array[mid]==key) return mid;
    else if(array[mid]>key) return binary_search(array,0,mid-1,key);
    else return binary_search(array,mid+1,end,key);
}
int main (){
	int array[100];
	int key;
    int i;
    for(i=0; i<100; i++){
        array[i]=2*i+1;
    }
	scanf("%d",&key);
	printf("%d",binary_search(array,0,99,key));
}