#include<bits/stdc++.h>
using namespace std;
int first_occ(int arr[],int i,int key,int n){
    if(i==n){
        return -1;
    }
    if(arr[i]==key){
         return i;
    }
    return first_occ(arr,i+1,key,n);
    
}
int last_occ(int arr[],int i,int key,int n){
    if(i==n){
        return -1;
    }
    int rest=last_occ(arr,i+1,key,n);
    if(rest!=-1){
        return rest;
    }
    if(arr[i]==key)
      return i;
    return -1;
}

int main(){
    int arr[]={1,4,5,5,6,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<first_occ(arr,0,5,n)<<endl;
    cout<<last_occ(arr,0,5,n);
    return 0;
}