#include<stdio.h>
void minmax(int a[],int i, int j, int*max, int *min){
    int mid, max1, min1;
    if(i==j) *max=*min=a[i];
    else if(i==j-1){
        if(a[i]<a[j]){
            *max=a[j];
            *min=a[i];
        }else{
            *max=a[i];
            *min=a[j];
        }
    }else{
        mid=(i+j)/2;
        minmax(a,i,mid,max,min);
        minmax(a,mid+1,j,&max1,&min1);
        if(*max<max1) *max=max1;
        if(*min>min1) *min=min1;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int max,min;
    minmax(a,0,n-1,&max,&min);
    printf("max=%d",max);
    printf("min=%d",min);
    return 0;
}