#include<iostream>
#include<vector>

using namespace std;

bool Bipartido(vector<vector<int>> &graph, vector<int> &color, const int vertice, const int cor) {
    if(color[vertice]!=-1){
        if(color[vertice]!=cor)
            return false;
        else    
            return true;
    }
    color[vertice] = cor;

    vector<int>::const_iterator it;
    for(it = graph[vertice].begin(); it !=graph[vertice].end(); it++){
        int corDiferente = 1 - cor;
        bool isBipartido = Bipartido(graph,color,*it,corDiferente);
        if(!isBipartido)
            return false;
    }
    return true;
}

void isClaw(vector<vector<int>> &Graph, int TotalVertices){
    vector<int> colors(TotalVertices,-1);
    for(int i = 0; i<TotalVertices; i++) {
        if(colors[i]!= -1)
            continue;
        if(!Bipartido(Graph,colors,i,0)) {
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}

int main() {
    int V, a, b;
    bool termina = false;
    cin>>V;
    vector<vector<int>> grafo(V);

    while(!termina) {
        cin>> a >> b; a--; b--;
        if(a == -1 && b == -1){
            isClaw(grafo,V);
            cin>>V;
            if(V == 0){
                termina = true;
                break;
            }
            grafo.clear();
            grafo.resize(V);
            continue;
        }
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
	return 0;
}