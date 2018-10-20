#include <stdio.h>
#include <math.h>
#include<stdlib.h>
double SR_slow(double a){
	double approx,better;
	approx = a+1;
	better = (approx + a/approx)+1;
	while (better != approx){
		approx = better;
		better = (approx + a/approx)/2.0;
	}
	return approx;
}
double SR_fast(double a ){
	double approx,better;
	approx = a/2.0;
	better = (approx + a/approx)/2.0;
	while (better != approx){
		approx = better;
		better = (approx + a/approx)/2.0;
	}
	return approx;
}

int main(){
	double input_number;
	double result;
	printf("숫자를 입력하시오 : 제곱근할 숫자\n");
	scanf("%lf",&input_number);
	result=SR_slow(input_number);
	//result=SR_fast(input_number);
	if(input_number<0)
		printf("%lf i",result);
	else
		printf("%lf",result);
}