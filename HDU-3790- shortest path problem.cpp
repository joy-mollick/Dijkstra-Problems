
/// Dijkstra (double parameters) 

/*
Modified Dijkstra to find out shortest distance of a node depending on two parameters
When ,in the case of equal dist we will take the node with minimum cost.
*/

#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;

const int maxn = 1e5+10;

///it will hold shortest distance,in-case-of equal -> minimum cost will be considered
int dist[maxn],cost[maxn];

vector< pair<int,int> >dist_pair[maxn];
vector< pair<int,int> >cost_pair[maxn];

void init()
{
    for(int i = 0; i < maxn; i++) dist[i] = 1e9,cost[i]=1e9;
    for(int i = 0; i < maxn; i++) dist_pair[i].clear(),cost_pair[i].clear();
}

void Dijkstra(int s)
{
     priority_queue<pi,vector<pi>,greater<pi> >Q; ///minHeap
        Q.push(make_pair(dist[s],s));
        while(!Q.empty())
        {
            int u = Q.top().second;
            Q.pop();
            for(int j=0;j<dist_pair[u].size();j++)
            {
                int v =dist_pair[u][j].first;
                if(dist[v]>dist[u]+dist_pair[u][j].second)
                {
                    dist[v]=dist[u]+dist_pair[u][j].second;
                    cost[v]=cost[u]+cost_pair[u][j].second;
                    Q.push(make_pair(dist[v],v));
                }
                else if(dist[v]==dist[u]+dist_pair[u][j].second && cost[v]>cost[u]+cost_pair[u][j].second)
                    cost[v]=cost[u]+cost_pair[u][j].second;
            }
        }
}

int main()

{
     int n,m;
     while(scanf("%d%d",&n,&m),n||m)
    {
        init();
        int a, b, x, c,s,t;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d%d%d",&a,&b,&x,&c);
            dist_pair[a].push_back(make_pair(b,x));
            dist_pair[b].push_back(make_pair(a,x));
            cost_pair[a].push_back(make_pair(b,c));
            cost_pair[b].push_back(make_pair(a,c));
        }
        scanf("%d %d",&s, &t);
        dist[s] = 0; cost[s] = 0; Dijkstra(s);
        printf("%d %d\n",dist[t], cost[t]);
    }

    return 0;
}
