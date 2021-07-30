#include<bits/stdc++.h>
using namespace std;
int dp[500];
int maximum_sum(int arr[],int n){
    
    if(n==0){
        return 0;
    }
    if(n==1)
     return arr[0];
    if(n==2)
     return arr[0]+arr[1];
    
    if(dp[n]!=-1)
     return dp[n];

    return dp[n]=max((arr[n]+maximum_sum(arr,n-2),maximum_sum(arr,n-1)),arr[n]+arr[n-1]+maximum_sum(arr,n-3));
       
      
}
int main(){
   
    memset(dp,-1,sizeof(dp));
    int arr[]={3000, 2000, 1000, 3, 10};
    int n=sizeof(arr)/sizeof(arr[0]);
    
    cout<<maximum_sum(arr,n)<<endl;
    return 0;
}