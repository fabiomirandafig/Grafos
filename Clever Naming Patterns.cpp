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

void solve(int n, vector<vector<string>> &Names,int TotalNomes,int i){
    memset(cap,0,sizeof(cap));
    int numVertices = n + TotalNomes + 28;
    int auxiliar = n + 1;
    int auxiliar2 = n + TotalNomes + 1;
    char temp;
    int temp2,aux3;

    for(int i = 1; i <= n; i++){
        cap[0][i] = 1;
        for(int j = 0; j < Names[i-1].size(); j++){
            cap[i][auxiliar+j] = 1;
            temp = toupper(Names[i-1][j][0]);
            temp2 = (int)temp - 65;
            cap[auxiliar+j][auxiliar2 + temp2] = 1;
            cap[auxiliar2 + temp2][numVertices - 1] = 1;
        }
        auxiliar+=Names[i-1].size();
    }

    fordFulkerson(numVertices,0,numVertices-1);

    auxiliar = n + 1;
    bool quebra = false;
    aux3 = auxiliar;
    cout<<"Case #"<<i<<":"<<endl;
    for(int p = auxiliar2; p < auxiliar2 + 26; p++){
        for(int t = auxiliar; t < auxiliar + TotalNomes; t++){
            if(fnet[t][p]-fnet[p][t] == 1){
                for(int z = 1; z <= n; z++){
                    if(fnet[z][t] - fnet[t][z] == 1){
                        for(int q = 0; q < z-1; q++)
                            aux3+=Names[q].size();
                        Names[z-1][t-aux3][0] = toupper(Names[z-1][t-aux3][0]);
                        cout<<Names[z-1][t-aux3]<<endl;
                        aux3 = auxiliar;
                        quebra = true;
                        break;
                    }
                }
            }
            if(quebra) break;
        }
        quebra = false;
    }
}

int main() {
    int N,n,k,i,count,totalnomes;
    string name;
    vector<vector<string>> names(100);
    count = i = totalnomes = 0;
    
    cin>>N;

    while(N>0){
        cin>>n; i++;
        for(int i = 0; i < n; i++){
            cin>>k;
            for(int j = 0; j < k; j++){
                cin>>name;
                for(int i = 0; i < name.size(); i++)
                    name[i] = tolower(name[i]);
                names[count].push_back(name);
                totalnomes++;
            }
            count++;
        }
        solve(n,names,totalnomes,i);
        names.clear(); names.resize(100);
        count = totalnomes = 0;
        N--;
    }
    return 0;
}