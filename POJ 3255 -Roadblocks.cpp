
/*
 Second shortest path.
 Using modifies dijkstra , we will find second shortest path amongst one or more shortest paths .
 It will give second shortest path which is immediate longer than shortest path.
*/


#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>

using namespace std;

typedef pair<int,int> ipair;

const int mx=1e5+1;

vector<ipair>adj[mx];

vector<int>distfirst(mx);/// it will hold shortest path's weight from particular node
vector<int>distsecond(mx);/// it will hold second shortest path's from particular node

#define inf 1e7

void shortest_path(int src)
{
    priority_queue<ipair,vector<ipair>,greater<ipair> >pq;///minHeap
    pq.push(make_pair(0,src));
    distfirst[src]=0;
    while(!pq.empty())
    {
        int u=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        for(int i=0;i<(int)adj[u].size();i++)
        {
            int v=adj[u][i].first;
            int weight=adj[u][i].second;
            int cost_of_v_from_u=weight+cost;
            if(cost_of_v_from_u<distfirst[v])
            {
                int temp=distfirst[v];
                distfirst[v]=cost_of_v_from_u;
                cost_of_v_from_u=temp;///new cost will be this ,it will be compared to second best
                pq.push(make_pair(distfirst[v],v));
            }
            /// assuming cost_of_v_from_u as distsecond[v] i.e.  cost_of_v_from_u will have to be greater than first shortest path and less than second shortest path
            if(cost_of_v_from_u>distfirst[v] && cost_of_v_from_u<distsecond[v])
            {
                distsecond[v]=cost_of_v_from_u;
                pq.push(make_pair(distsecond[v],v));/// we have to push them into the queue,otherwise we will not get further second shortest path's cost from here
            }
        }
    }
}

int main()

{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    /// initialize as inf
    for(int i=0;i<mx;i++)
    {
        distfirst[i]=inf;
        distsecond[i]=inf;
    }
    int n,r,u,v,cost;
    cin>>n>>r;

    while(r--)
    {
        cin>>u>>v>>cost;
        adj[u].push_back(make_pair(v,cost));
        adj[v].push_back(make_pair(u,cost));
    }
    shortest_path(1);
    cout<<distsecond[n]<<endl;
    return 0;
}
