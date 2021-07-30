#include<bits/stdc++.h>
using namespace std;
void  inc(int n){
    if(n==0){
         return;
    }
    inc(n-1);
    cout<<n<<" ";
}
 void dec(int n){
     if(n==0){
         return; 
     }
     cout<<n<<" ";
     dec(n-1);
 }
int main(){
    int n=10;
    inc(10);
    cout<<endl;
    dec(10);
    return 0;
}