#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Print_optimal_parent(int** s,int i, int j)   
{
   if(i==j)
      printf("A%d",i);

   else
   {
      printf("(");
	  Print_optimal_parent(s,i,s[i][j]);
	  Print_optimal_parent(s,s[i][j]+1,j);
      printf(")");
   }
}

void Matrix_chain_mul(int** m,int** s,int* p,int n) 
{
   int i;
   int j,k;
   int l;
   int q;
   for(i=1;i<n;i++)
   {
      m[i][i] = 0;
      s[i][i] = i;
   }
   for(l=2;l<n;l++)
   {
      for(i=1;i<n-l+1;i++)
      {
         j = i+l-1;
         m[i][j] = INT_MAX;
         for(k=i;k<j;k++)
         {
            q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
            if(q<m[i][j])
            {
               m[i][j] = q;
               s[i][j] = k;
            }
         }
      }
   }
}

void main()
{
   FILE* fp;
   FILE* fop;
   FILE* fop2;

   int* p;
   int* tmp;
   int** s;
   int** m;
   int i,j;
   int cnt=0;


   fp = fopen("week9.txt","rt");

   if(fp == NULL)
   {
      printf("Input File open error\n");
      exit(1);
   }
   

   p = (int*)malloc(sizeof(int));
   tmp = (int*)malloc(sizeof(int));
   
   while(!feof(fp))
   {
      p = (int*)realloc(p,sizeof(int)*(cnt+1));
      tmp = (int*)realloc(tmp,sizeof(int)*(cnt+1));
      fscanf(fp,"(%d,%d)",&p[cnt],&tmp[cnt]);
      cnt++;
   }
   
   p = (int*)realloc(p,sizeof(int)*(cnt+1));
   p[cnt-1] = tmp[cnt-2];


   s = (int**)malloc(sizeof(int *)*(cnt));
   for(i=0;i<cnt;i++)
   {
      s[i] = (int*)malloc(sizeof(int)*(cnt));
   }

   m = (int**)malloc(sizeof(int *)*(cnt));
   for(i=0;i<cnt;i++)
   {
      m[i] = (int*)malloc(sizeof(int)*(cnt));
   }

  

   Matrix_chain_mul(m,s,p,cnt);
   
   Print_optimal_parent(s,1,4);

   fclose(fp);   
}