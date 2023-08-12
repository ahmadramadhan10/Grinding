#include <bits/stdc++.h>
using namespace std;

int sz[1001];
int main(){
    int n,inc,decr; cin>>n>>inc>>decr;
    if ((inc+decr-1 <= n)&&(n<=inc*decr)){
        sz[0]=decr;
        for (int i=1;i<inc;i++) sz[i]=1;
        int rem=n-decr-(inc-1);
        for (int i=1;i<inc;i++){
            if (rem>decr-1){
                sz[i]+=decr-1;
                rem-=(decr-1);
            }
            else{
                sz[i]+=rem;
                break;
            }
        }
        int last=0;
        for (int i=0;i<inc;i++){
            for (int j=sz[i];j>=1;j--){
                cout<<last+j<<" ";
            }
            last+=sz[i];
        }
        cout<<endl;
    }
    else{
        cout<<-1<<endl;
    }
}
