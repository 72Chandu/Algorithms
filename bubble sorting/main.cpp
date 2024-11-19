#include<iostream>
#include<vector>
using namespace std;
//repeately swap two adjencent element if in wrong order
void bubblesort(vector<int>&v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(v[j]>v[j+1]){
                swap(v[j],v[j+1]);
            }
        }
    }
}
int main(){
    vector<int>v={20,50,40,10,30};
    cout<<"element before sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
    bubblesort(v);
     cout<<"\nelement after sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
}