/*
Divide: Choose a pivot element from the array. This element is used to partition the array into two subarrays:

Elements less than the pivot.
Elements greater than or equal to the pivot.
Conquer: Recursively apply Quick Sort on the two subarrays.

Combine: Combine the sorted subarrays with the pivot to form the final sorted array.
*/
#include<iostream>
#include<vector>
using namespace std;
int partition(vector<int>&v, int first, int last){
    int pivot=v[last];
    int i=first-1; // jo pivot se chota hoga us ko is position pe rakhna hai
    for(int j=first;j<last;j++){ // Traverse arr[;ow..high] and move all smaller  elements on left side. Elements from low to  i are smaller after every iteration
        if(v[j]<pivot){
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1], v[last]); // Move pivot after smaller elements and return its position
    return i+1;
}
void quickShort(vector<int>&v , int first, int last){
    if(first<last){
        int part=partition(v,first,last);//return index of pivot
        quickShort(v,first,part-1);
        quickShort(v,part+1,last);
    }
} 
int main(){
    vector<int>v={10, 7, 8, 9, 1, 5};
    int n=v.size();
    quickShort(v,0,n-1);
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    return 0;
}
/*
pivot 
   -> to place pivot such that the element to the right of pivot >v[pivot]
   ->element left of pivot element<v[pivot]
  
                            {10 , 80, 30, 90 , 70}  -> pivot=70
            {10,30,40,50}->p=50               {90,80}->p=80
      {10,30,40}->p=40  {}                     {}    {90}
  {10,30}->p=30  {}
  {10} {}
  
The logic is simple, we start from the leftmost element and keep track of the index of smaller (or equal) elements as i .
While traversing, if we find a smaller element, we swap the current element with arr[i]. Otherwise, we ignore the current element.

10, 80, 30, 90, 40}.-> p=40
i
10<pivot   swap 10 with 10

10, 80, 30, 90, 40}.-> p=40
    i
80>pivot   hence no swap move to 30

10, 80, 30, 90, 40}.-> p=40
         i
30<pivot   swap 80 with 30

10, 30, 80, 90, 40}.-> p=40
            i
90>pivot   hence no swap

10, 30, 40, 90, 80}.-> p=40
            
90>pivot   hence no swap

10,30 ----partion around pivot 30 ---->10, 30
90,80 ----partion around pivot 30 ---->80, 90
*/