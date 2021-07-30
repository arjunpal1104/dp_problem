#include<bits/stdc++.h>
using namespace std;
int sum(int n){
    if(n==0){
        return 0;
    }
    int presum=sum(n-1);
     return n+presum;
}
int main(){
    int n=5;
    cout<<sum(n);
    return 0;
}