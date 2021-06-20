#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<cassert>
#include<string.h>
using namespace std;

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, Prev[NN];

int fordFulkerson( int n, int s, int t ) {
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( Prev, -1, sizeof( Prev ) );
        qf = qb = 0;
        Prev[q[qb++] = s] = -2;
        while( qb > qf && Prev[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( Prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    Prev[q[qb++] = v] = u;

        // see if we're done
        if( Prev[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = Prev[v]; u >= 0; v = u, u = Prev[v] )
            bot = min(bot,cap[u][v] - fnet[u][v] + fnet[v][u]);

        // update the flow network
        for( int v = t, u = Prev[v]; u >= 0; v = u, u = Prev[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

void solve(vector<pair<char,int>> &appPlusUsers, vector<vector<int>> &Computers){
    memset(cap,0,sizeof(cap));
    int numVertices = appPlusUsers.size() + 12;
    int auxiliar = appPlusUsers.size() + 1;
    int totalOfApps = 0;
    
    for(int i = 1; i <= appPlusUsers.size(); i++){
        cap[0][i] = appPlusUsers[i-1].second;
        totalOfApps += appPlusUsers[i-1].second;
        for(int j = 0; j < Computers[i-1].size(); j++){
            cap[i][Computers[i-1][j]+auxiliar] = 1;
            cap[Computers[i-1][j]+auxiliar][numVertices-1] = 1;
        }
    }

    int fluxo = fordFulkerson(numVertices,0,numVertices-1);

    bool r = false;
    if(totalOfApps != fluxo)
        cout<<"!"<<endl;
    else {
        for(int i = 0; i < 10; i++){
            for(int j = 1; j <= appPlusUsers.size(); j++){
                if(fnet[j][auxiliar+i] - fnet[auxiliar+i][j] == 1){
                    cout<<appPlusUsers[j-1].first;
                    r = true;
                    break;
                }
            }
            if(!r) cout<<"_";
            r = false;
        }
        cout<<endl;
    }
}

int main() {
    vector<pair<char,int>> applicationPlusUsers;
    vector<vector<int>> computers(100);
    string temp, aux;
    int count = 0;

    while(getline(cin,temp)){
        if(!temp.size()){
            solve(applicationPlusUsers,computers);
            applicationPlusUsers.resize(0); applicationPlusUsers.clear();
            computers.clear(); computers.resize(100);
            count = 0;
            continue;
        } 
        aux = temp[1];
        applicationPlusUsers.push_back(make_pair(temp[0],stoi(aux)));            
        for(int i = 3; i < temp.size()-1; i++){
            aux = temp[i];
            computers[count].push_back(stoi(aux));
        }
        count++;
    }
    solve(applicationPlusUsers,computers);
    return 0;
}