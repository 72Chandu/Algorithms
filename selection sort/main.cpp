#include<iostream>
#include<vector>
using namespace std;
//repeatedly find minimum ele in unsorted array & place it at begining
void selectionSort(vector<int>&v){
    int n=v.size();
    for(int i=0;i<n-1;i++){//finding the minimum ele in unsorted array
        int min_idx=i;
        for(int j=i+1;j<n;j++){
            if(v[j]<v[min_idx]){
                min_idx=j;//updation of min idx
        }
      }
      if(i!=min_idx){//placing min ele at begining
        swap(v[i],v[min_idx]);
    }
  }
}
int main(){
    vector<int>v={20,50,40,10,30};
    cout<<"element before sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
    selectionSort(v);
    cout<<"\nelement after sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
}