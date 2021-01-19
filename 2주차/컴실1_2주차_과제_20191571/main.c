#include "header.h"

int main(){
long long page;
int t;
long long int arr[10];
scanf("%d",&t);
for(int i=0;i<t;i++){
scanf("%lld",&page);
start(arr);
count(page,arr);
print(arr);
}
return 0;
}
