#include<iostream>
#include<vector>
#include<climits>
#define INF INT_MAX
using namespace std;

void djik(int source, vector<vector<int>>& edges, int n) {
    
}

void floyd_warsh(vector<vector<int>>& graph, int n) {
//    vector<int> dist(n,INT_MAX);
//    dist[0]=0;
    for(int k=0;k<n;k++) { // intermediate node 
        for(int j=0;j<n;j++) { // end 
            for(int i=0;i<n;i++) { // start can be interchanged but not with k
                if(graph[i][k]!=INF && graph[k][j]!=INF && ((graph[i][k] + graph[k][j]) < graph[i][j]))
                    graph[i][j] = graph[i][k]+graph[k][j];
            }
        }
    }
    
    for(int i=0;i<n;i++) {  
        for(int j=0;j<n;j++) { 
            if(graph[i][j]==INF) cout<<"INF ";
            else cout<<graph[i][j]<<" "; 
        }
        cout<<endl;
    }
}

void bell_ford(int source, vector<vector<int>>& edges, int n) {
    
    vector<int> dist(n,INT_MAX);
    dist[0] = 0;

    for(int i=0;i<n;i++) { // need only n-1 relaxations, if there are n means there's a negative cycle
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if(dist[u] != INT_MAX && dist[u]+w < dist[v]) {
                if(i==n-1) {cout<<"cycle"<<endl;return;}
                dist[v] = dist[u]+w;
            }
        }
    }
    for(int i=1;i<n;i++)
        cout<<source<<"->"<<i<<" : "<<dist[i]<<endl;
}

int main() {
    cout<<"Bellman Ford"<<endl;
    vector<vector<int>> edges = {{1, 3, 2}, {4, 3, -1}, {2, 4, 1}, {1, 2, 1}, {0, 1, 5}};
    bell_ford(0,edges,5);
    cout<<"Floyd warshall"<<endl;
    vector<vector<int>> graph = {{0,5,INF,10},{ INF, 0, 3, INF },{ INF, INF, 0, 1 }, { INF, INF, INF, 0 } };
    floyd_warsh(graph, graph.size());
    return 0;
}
