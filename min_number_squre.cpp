#include<bits/stdc++.h>
using namespace std;


int main(){
    int n;
    cin>>n;
    vector<int>dp(n+1,INT_MAX);

    dp[0]=0;
    dp[1]=1;
    dp[2]=2;
    dp[3]=3;

    for(int i=1;i*i<=n;i++){
        for(int j=1;i*i+j<=n;j++){
            dp[i*i+j]=min(dp[i*i+j],1+dp[j]);
        }
    }
    cout<<dp[n]<<endl;
    return 0;

}


// int min_square(int n){
    
//     if(n==0 || n==1 || n==2 || n==3)
//      return n;
//     int ans=INT_MAX;
//     for(int i=1;i*i<=n;i++)
//       ans=min(ans,1+min_square(n-i*i));
    
//  return ans;

// }
// int main(){
//     int n;
//     cin>>n;
//     cout<<min_square(n)<<endl;
//     return 0;
// }

// dp problem
