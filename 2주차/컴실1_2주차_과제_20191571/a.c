#include "header.h"
void count(long long int page,long long int *arr){

	long long int temp=0;
	for(long long int i=1;i<=page;i++){
	temp=i;
	while(temp!=0)
	{
		arr[temp%10]++;
		temp=temp/10;
		
	}
	}




}
