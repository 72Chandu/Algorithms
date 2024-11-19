#include<iostream>
#include<vector>
using namespace std;
//repeatedly take ele from unsorted subarray & insert in sorted subarray
void insertionSort(vector<int>&v){
    int n=v.size();
    for(int i=1;i<n;i++){
        int curr_ele=v[i];
        int j=i-1;
        while(j>=0 and v[j]>curr_ele){
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=curr_ele;
    }
}
int main(){
    vector<int>v={11,8,15,9,4};//start (i->8 j->11)
    cout<<"element before sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
    insertionSort(v);
    cout<<"\nelement after sorting:";
    for(auto i:v){
        cout<<i<<" ";
    }
}
