#include<bits/stdc++.h>
using namespace std;
bool check_sorted_array(int arr[],int n){
    if(n==1){
        return true;
    }
    bool restArray=check_sorted_array(arr+1,n-1);
    return (arr[0]<arr[1] && restArray); 
}
int main(){
    int arr[]={1,2,3,4,5,6};
    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<check_sorted_array(arr,n);
    //return 0;
}