#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>


struct Point
{
   double x, y;
};
int compareX(const void* a, const void* b)
{
    struct Point *p1,*p2 ;
	p1 = (struct Point *)a;
	p2 = (struct Point *)b;
    return (p1->x - p2->x);
}
int compareY(const void* a, const void* b)
{
    struct Point *p1,*p2 ;
	p1 = (struct Point *)a;
	p2 = (struct Point *)b;
    return (p1->y - p2->y);
}
double dist(struct Point p1,struct Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +(p1.y - p2.y)*(p1.y - p2.y));
}
double bruteForce(struct Point* P, int n)
{
	int i,j;
    double min = DBL_MAX;
    for (i = 0; i < n; ++i)
        for (j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}
double min_d(double x, double y)
{
   if(x>y)
	   return y;
   else
	   return x;
}
double stripClosest(struct Point *strip, int size, double d)
{
    double min = d;  
	int i,j;
    qsort(strip, size, sizeof(struct Point), compareY); 
 
    for ( i = 0; i < size; ++i)
        for (j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
 
    return min;
}
double closestUtil(struct Point* P, int n)
{
	
    int mid = n/2;
	int j,i;
	double dl,dr,d;
	struct Point* strip;
    struct Point midPoint = P[mid];
	if(n<3)
	return bruteForce(P,n);
	dl = closestUtil(P, mid),dr = closestUtil(P + mid, n-mid);
    d = min_d(dl,dr);

	strip = (struct Point*)malloc(sizeof(struct Point)*n);
    j = 0;
    for (i = 0; i < n; i++){
        if (abs(P[i].x - midPoint.x) < d){
            strip[j] = P[i]; 
			j++;
		}
	}
    return min_d(d, stripClosest(strip, j, d) );
}
double closest(struct Point * P, int n)
{
    qsort(P, n, sizeof(struct Point), compareX);
	
    return closestUtil(P, n);
}
int main(){

	FILE* fp; //fp : input file pointer
	FILE* fop; //fop : input file pointer
	//파일 이름은 “00_201500000_insertion.txt”
	//입출력 파일은 *.c 소스파일과 같은 폴더에 있어야 한다.
	int i=0;
	int cnt = 0;
	struct Point * data =NULL,data_s;
	int p=0;
	int n;
	double pair;
	data = &data_s;

	fp = fopen("data05.txt","rt"); //입력 파일 열기
	fop = fopen("00_201302481_정우식_Closest.txt","wt"); //출
	if (fp == NULL) {
		printf("**** Input File open error ****\n");
		exit(1);
	} //파일 없을 경우 예외처리로 프로그램 종료	

	while(!feof(fp)) {
		fscanf(fp,"%lf %lf,",&data->x,&data->y);
		cnt++;
	}
	fseek(fp,0,SEEK_SET);
	data = (struct Point*)malloc(sizeof(struct Point)*cnt);
	while(i<cnt){
		fscanf(fp,"%lf %lf,",&data[i].x,&data[i].y);
		i++;
	}
	pair = closest(data,cnt);
	printf("%lf",pair);
	
}
