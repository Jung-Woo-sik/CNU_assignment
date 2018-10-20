#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Point
{
   int  u,v,w;
};

void printArr(int* dist, int n,int src,FILE * fop)
{
	int i;
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < n; ++i){
        printf("%d \t\t %d\n", i, dist[i]);
		fprintf(fop,"%d -> %d (%d)\n",src,i,dist[i]);
	}
}

void BellmanFord(struct Point* data, int src,int V,int E ,FILE * fop)
{
    
    int *dist;
	int i,j;
	dist = (int *)malloc((sizeof(int)) * V);
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for ( i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (i = 1; i <= V-1; i++)
    {
        for ( j = 0; j < E; j++)
        {
            int u = data[j].u;
            int v = data[j].v;
            int weight = data[j].w;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (i = 0; i < E; i++)
    {
        int u = data[i].u;
        int v = data[i].v;
        int weight = data[i].w;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
 
    printArr(dist, V,src,fop);
 
    return;
}

int main(void) {

	FILE* fp; //fp : input file pointer
	FILE* fop; //fop : input file pointer
	//���� �̸��� ��00_201500000_insertion.txt��
	//����� ������ *.c �ҽ����ϰ� ���� ������ �־�� �Ѵ�.
	int i=0;
	int cnt = 0;
	struct Point * data =NULL,data_s;
	int p=0;
	int n;
	double pair;
	int size,start;
	data = &data_s;

	fp = fopen("data11.txt","rt"); //�Է� ���� ����
	fop = fopen("201302481.txt","wt"); //��
	if (fp == NULL) {
		printf("**** Input File open error ****\n");
		exit(1);
	} //���� ���� ��� ����ó���� ���α׷� ����	

	fscanf(fp,"%d",&size);
	fscanf(fp,"%d",&start);
	

	while(!feof(fp)) {
		fscanf(fp,"%d %d %d,",&data->u,&data->v,&data->w);
		cnt++;
	}
	fseek(fp,4,SEEK_SET);
	data = (struct Point*)malloc(sizeof(struct Point)*cnt);
	while(i<cnt-1){
		fscanf(fp,"%d %d %d,",&data[i].u,&data[i].v,&data[i].w);
		
		i++;
	}


	BellmanFord(data,start,size,i,fop);



  return 0;
}