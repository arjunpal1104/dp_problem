#include<bits/stdc++.h>
using namespace std;
string removeduplicate(string str){
    if(str.length()==0){
        return "";
    }
    char ch=str[0];
     string ans=removeduplicate(str.substr(1));
    if(ch==ans[0]){
        return ans;
    }else{
        return ch+ans;
    }

}
int main(){
    string str="aaaabcde";
   // string ans="";
    cout<<removeduplicate(str);
}