#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ** LCS_length(char* data1,char* data2);
int ** Print_LCS(int ** c ,char * data1 ,int i,int j);
char** b;
int ** LCS_length(char* data1,char* data2){
	int m,n,k;
	int **c;
	int i,j;
	m = strlen(data1);
	n = strlen(data2);
	
	b = (char **) malloc ( sizeof(char *) * m);
	for(k=0; k<=m; k++){
		b[k] = (char *) malloc ( sizeof(char) * n );
	}
    printf("%d    %d\n",m,n);
	c = (int **) malloc ( sizeof(int *) * m);
	for(k=0; k<=m; k++){
		c[k] = (int*) malloc ( sizeof(int) * n );
	}
	for(i = 0; i<=m;i++){
		c[i][0] = 0;
	}

	for(j=0;j<=n;j++){
		c[0][j] = 0;
	}

	for(i = 1 ; i <= m ; i++)
	{
		for(j = 1 ; j <= n ; j++)
		{
 			if(data1[i-1]==data2[j-1])
			{
				c[i][j] = c[i-1][j-1] +1;
				b[i][j]='c';
			}
			else if(c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j]; 
				b[i][j] = 'u';
			}
			else
			{
				c[i][j] = c[i][j-1]; 
				b[i][j] = 'l';
			}
		
		}
		
	}
	return c;
}
int * * Print_LCS(int ** c ,char * data1 ,int i,int j){
	if(i==0 || j==0){
		return c;
	}
/*	if(c[i][j]-1 == c[i-1][j-1] && c[i][j]-1 == c[i][j-1] && c[i][j]-1 == c[i-1][j]){
		Print_LCS(c,data1,i-1,j-1);
		printf("%c",data1[i-1]);		
	}
	else if(c[i][j]==c[i][j-1]){
		Print_LCS(c,data1,i,j-1);
	}
	else
		Print_LCS(c,data1,i,j-1);*/
	 if(b[i][j]=='c')
	 {
		 Print_LCS(c,data1,i-1,j-1);
		 printf("%c",data1[i-1]);
     }       
	 else if(b[i][j]=='u')
		 Print_LCS(c,data1,i-1,j);     
	 else
        Print_LCS(c,data1,i,j-1);
}
int main(){

	FILE* fp; //fp : input file pointer
	FILE* fop; //fop : input file pointer
	//파일 이름은 “00_201500000_insertion.txt”
	//입출력 파일은 *.c 소스파일과 같은 폴더에 있어야 한다.
	int i=1;
	char strTemp1[255];
	char strTemp2[255];
	int ** c;
	char* data1 = NULL;
	char* data2 = NULL;
	int num;
	int cnt=0;
		int p=0;
	int key ,o,a;

	fp = fopen("data08_2.txt","rt"); //입력 파일 열기
	fop = fopen("00_201302481_정우식_quick.txt","wt"); //출
	if (fp == NULL) {
		printf("**** Input File open error ****\n");
		exit(1);
	} //파일 없을 경우 예외처리로 프로그램 종료	

	fgets( strTemp1, sizeof(strTemp1), fp );
	strTemp1[strlen(strTemp1)-1] = '\0';
	data1 = strTemp1;
	data2 = fgets( strTemp2, sizeof(strTemp2), fp );
	//printf("%s",data1);
	//printf("%s",data2);
	c = LCS_length(data1,data2);

	Print_LCS(c,data1,strlen(data1),strlen(data2));
}