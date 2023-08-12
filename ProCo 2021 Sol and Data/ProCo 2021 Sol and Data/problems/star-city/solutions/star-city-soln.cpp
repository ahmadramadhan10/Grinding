#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int N=100005;
vector<int> G[N];
ll val[N];
int top[N], bot[N], level[N];
bool active[N];

int unite(int x, int y){
    //unites the segments which have x and y as endpoints, returns the new top
    pii seg1={top[x],bot[x]},seg2={top[y],bot[y]};
    if (level[seg1.first]>level[seg2.first]) swap(seg1,seg2);
    bot[seg1.first]=seg2.second;
    top[seg2.second]=seg1.first;
    return seg1.first;
}
int main(){
    int n; cin>>n;
    for (int i=1;i<=n;i++) cin>>val[i];
    for (int i=1;i<=n-1;i++){
        int a,b; cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int root=1;
    for (int i=1;i<=n;i++) if (G[i].size()>2) root=i;

    memset(level,-1,sizeof level);
    queue<int> q;
    q.push(root); level[root]=0;
    while (q.size()){
        int now=q.front(); q.pop();
        for (int nex:G[now]) if (level[nex]==-1){
            level[nex]=level[now]+1;
            q.push(nex);
        }
    }

    vector<pair<ll,int>> asd;
    for (int i=1;i<=n;i++){
        asd.push_back({-val[i],i});
        top[i]=i; bot[i]=i;
    }
    sort(asd.begin(),asd.end());
    ll ans=0;
    pii soln;
    pii longestLeg={0,-root},secondLongestLeg={0,-root}; //longestLeg = the further node you can reach from the root, secondLeg = the second furthest node
    for (auto p:asd){
        int toAdd=p.second;
        active[toAdd]=1;
        if (toAdd!=root){
            int curr=toAdd;
            for (int x:G[toAdd]) if ((x!=root)&&(active[x])) curr=unite(x,toAdd);
            //solution type 1, a segment only on the leg
            ll currAns=level[bot[curr]]-level[curr]+1;
            currAns*=val[toAdd];
            pii currSoln={min(curr,bot[curr]),max(curr,bot[curr])};
            if (currAns>ans){
                ans=currAns;
                soln=currSoln;
            }
            if ((currAns==ans)&&(currSoln<soln)){
                ans=currAns;
                soln=currSoln;
            }

            if (level[curr]==1){ //we have lengthened a leg connected to the root
                pii currLeg={level[bot[curr]],-bot[curr]};
                //maybe we lengthened one of the legs!
                if (top[-longestLeg.second]==curr){
                    longestLeg=currLeg;
                }
                else if (top[-secondLongestLeg.second]==curr){
                    secondLongestLeg=currLeg;
                    if (secondLongestLeg>longestLeg) swap(longestLeg,secondLongestLeg);
                }
                else{
                    if (currLeg>longestLeg){
                        secondLongestLeg=longestLeg;
                        longestLeg=currLeg;
                    }
                    else if (currLeg>secondLongestLeg){
                            secondLongestLeg=currLeg;
                    }
                }
            }
        }
        if (active[root]){
            ll currAns=longestLeg.first+secondLongestLeg.first+1;
            currAns*=val[toAdd];
            pii currSoln={min(-longestLeg.second,-secondLongestLeg.second),max(-longestLeg.second,-secondLongestLeg.second)};
            if (currAns>ans){
                ans=currAns;
                soln=currSoln;
            }
            if ((currAns==ans)&&(currSoln<soln)){
                ans=currAns;
                soln=currSoln;
            }
        }
        /*
        for (int i=1;i<=n;i++) cerr<<top[i]<<" "; cerr<<endl;
        for (int i=1;i<=n;i++) cerr<<bot[i]<<" "; cerr<<endl;
        cerr<<longestLeg.first<<" "<<longestLeg.second<<endl;
        cerr<<secondLongestLeg.first<<" "<<secondLongestLeg.second<<endl;
        */
    }
    cout<<ans<<endl;
    cout<<soln.first<<" "<<soln.second<<endl;
    return 0;
}
