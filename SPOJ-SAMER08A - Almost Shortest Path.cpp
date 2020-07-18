
/*
  Finding the second shortest path which will not go from source to destination using any root of shortest path . 
  The root of almost shortest path will be distinct to other one or more shortest paths.
  So , by using first dijkstra ,we will store the roots of all shortest paths .
  Then we will run another dijkstra which will ignore those roots of shortest paths and find almost shortest paths 
*/


#include<bits/stdc++.h>

using namespace std;

const int mx=500;

typedef pair<int,int> pi;
const int inf=1e9;
vector<pi>adj[mx];
vector<pi>rev_adj[mx];
int dist[mx];
int dist2[mx];
int parent[mx];
bool vis[mx];
vector<pi>avoid_edges;
int s,t;

void edge_store(int node,int parent_node)
{
    while(parent_node!=-1)
    {
       // cout<<node<<" "<<parent_node<<" ";
        avoid_edges.push_back(make_pair(parent_node,node));
        node=parent_node;
        parent_node=parent[parent_node];
    }
    //cout<<endl;
}

void djkstra(int src)
{
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    pq.push(make_pair(0,src));
    dist[src]=0;
    parent[src]=-1;
    memset(vis,false,sizeof(vis));
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();
     //   if(vis[u]==false) vis[u]=true;
      //  else continue;
        vector<pi>::iterator it;
        for(it=adj[u].begin();it!=adj[u].end();it++)
        {
            int v=(*it).first;
            int weight=(*it).second;
            if(v==t)
            {
                if(dist[v]==dist[u]+weight)
                {
                        edge_store(t,u);
                        continue;
                }
            }
            if(dist[v]>dist[u]+weight)
            {
                dist[v]=dist[u]+weight;
                parent[v]=u;
                pq.push(make_pair(dist[v],v));
                if(v==t)
                {
                    avoid_edges.clear();
                    edge_store(t,u);
                }
            }
        }
    }
}

void djkstra2(int src)
{
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    pq.push(make_pair(0,src));
    dist2[src]=0;
    memset(vis,false,sizeof(vis));
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();
        if(vis[u]==false) vis[u]=true;
        else continue;
        vector<pi>::iterator it;
        for(it=adj[u].begin();it!=adj[u].end();it++)
        {
            int v=(*it).first;
            int weight=(*it).second;
            if(dist2[v]>dist2[u]+weight && find(avoid_edges.begin(),avoid_edges.end(),make_pair(u,v))==avoid_edges.end())
            {
                dist2[v]=dist2[u]+weight;
                pq.push(make_pair(dist2[v],v));
            }
        }
    }
}

int main()

{

    int tc,n,m,k,a,b,c;
    while(cin>>n>>m && n!=0 && m!=0)
    {
        cin>>s>>t;
        s++,t++;
        for(int i=1;i<=n;i++)
        {
            adj[i].clear();
            dist[i]=inf;
            dist2[i]=inf;
            parent[i]=-1;
            avoid_edges.clear();
        }
        while(m--)
        {
            cin>>a>>b>>c;
            a++;
            b++;
            adj[a].push_back(make_pair(b,c));
        }
        djkstra(s);
        djkstra2(s);
        if(dist2[t]==inf) cout<<"-1"<<endl;
        else
        cout<<dist2[t]<<endl;
    }
    return 0;
}
