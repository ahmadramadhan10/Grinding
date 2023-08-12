#include <bits/stdc++.h>
using namespace std;
 
const int N=200005;
vector<int> Gf[N],Gb[N];
int inDeg[N],outDeg[N];
int ans[N];
int main(){
    int n,m; cin>>n>>m;
    while (m--){
        int a,b; cin>>a>>b;
        Gf[a].push_back(b);
        Gb[b].push_back(a);
        outDeg[a]++; inDeg[b]++;
    }
    //run Toposort on Gf
    int rem=n;
    queue<int> q;
    for (int i=1;i<=n;i++) if (outDeg[i]==0) q.push(i);
    while (q.size()){
        if (q.size()==1){
            ans[q.front()]+=rem;
        }
        int x=q.front(); q.pop();
        for (int y:Gb[x]){
            outDeg[y]--;
            if (outDeg[y]==0) q.push(y);
        }
        rem--;
    }
    //run toposort on Gb
    rem=n;
    for (int i=1;i<=n;i++) if (inDeg[i]==0) q.push(i);
    while (rem){
        if (q.size()==1){
            ans[q.front()]+=rem;
        }
        int x=q.front(); q.pop();
        for (int y:Gf[x]){
            inDeg[y]--;
            if (inDeg[y]==0) q.push(y);
        }
        rem--;
    }
    int cnt=0;
    for (int i=1;i<=n;i++) if (ans[i]==n+1) cnt++;
    cout<<cnt<<endl;
}