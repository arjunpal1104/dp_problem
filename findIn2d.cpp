#include<bits/stdc++.h>
using namespace std;
class solution{
public:
vector<vector<int>>sortematrix(int n,vector<vector<int>>mat){
    vector<int>res;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
         res.push_back(mat[i][j]);
    
    sort(res.begin(),res.end());
    int k=0;
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      mat[i][j]=res[k++];

      return mat;
 }

};
int main(){
    int n;
    cin>>n;
    vector<vector<int>>v(n,vector<int>(n));

    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      cin>>v[i][j];
    solution obj;
     v=obj.sortematrix(n,v);
     for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
       cout<<v[i][j]<<" ";}
       cout<<"\n";}
 return 0;

}
