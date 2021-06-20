#include <iostream>
#include <vector>

using namespace std;

struct aresta {
	int v1,v2,weight;
};

bool BellmanFord(vector<aresta> &Graph, int &vertices) {
    vector<int> custo(vertices,10000000);
    custo[0] = 0;
    bool temciclonegativo = false;

    for(int i = 0; i <vertices-1; i++){
        for(int j = 0; j < Graph.size(); j++){
            if(custo[Graph[j].v1] + Graph[j].weight < custo[Graph[j].v2]){
                custo[Graph[j].v2] = custo[Graph[j].v1] + Graph[j].weight;
            }
        }
    }

    for(int i = 0; i < Graph.size(); i++){
        if(custo[Graph[i].v1] + Graph[i].weight < custo[Graph[i].v2]){
            temciclonegativo = true;
            break;
        }
    }
    return temciclonegativo;
}

int main(){
    int c,n,m,x,y,t;
    cin>>c;

    while(c>0){
        vector<aresta>edges;
        cin>>n>>m;

        for (int i = 0; i < m; i++){
            cin>>x>>y>>t;
            aresta a = {x,y,t};
            edges.push_back(a);
        }

        bool CiclosNegativos = BellmanFord(edges,n);
        if(CiclosNegativos) cout<<"possible"<<endl;
        else cout<<"not possible"<<endl;

        c--;
    }
    return 0;
}