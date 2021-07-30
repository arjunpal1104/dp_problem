#include<bits/stdc++.h>
using namespace std;
int FindMaxSum(vector<int>arr,int n){
  int dp[n+1];
  if(n==0)
   return 0;
  if(n==1)
   return arr[0];
    dp[0]=arr[0];
    dp[1]=arr[0]>arr[1]?arr[0]:arr[1];
    
   for(int i=2;i<n;i++){
       dp[i]=max(dp[i-1],arr[i]+dp[i-2]);
   }
   return dp[n-1];
}
int main(){
     vector<int>arr= {5, 5, 10, 100, 10, 5};
    cout<<FindMaxSum(arr,0)<<endl;
    return 0;
}