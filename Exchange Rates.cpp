#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;

struct vizinho {
    int v,numerador,denominador;
};

int procura(map<string,int> &m, string &s){
    int codigo = -1;
    map<string,int>::iterator it;   
    for(it = m.begin(); it != m.end(); it++ ) {
        if(it->first == s){
            codigo = it->second;
        }
    }
    if(codigo == -1) {
        codigo = m.size();
        m[s] = codigo;
    }
    return codigo;
}

void dfs(vector<vector<vizinho>> &adjacencia, vector<bool>&visit, int o){
    vizinho aux;
    visit[o] = true;

    vector<vizinho>::const_iterator it;
    for(it = adjacencia[o].begin(); it !=adjacencia[o].end(); it++){
        aux = *it;
        if(!visit[aux.v])
            dfs(adjacencia,visit,aux.v);
    }
}

vizinho multiplica(vector<vector<vizinho>> &adjacencia, vizinho aux, vizinho total){
    total.numerador = total.numerador * aux.numerador;
    total.denominador = total.denominador * aux.denominador;
    int mdc = __gcd(total.numerador,total.denominador);
    total.numerador = total.numerador / mdc;
    total.denominador = total.denominador / mdc;

    return total;
}

void taxadecambio(vector<vector<vizinho>> &adjacencia, vector<bool>&visit, int o, int d, const vizinho total,string &Pa, string &Pb){
    vizinho auxiliar;
    visit[o] = true;
    if(o == d){
        cout<<total.numerador<<" "<<Pa<<" = "<<total.denominador<<" "<<Pb<<endl;
        return;
    }

    vector<vizinho>::const_iterator it;
    for(it = adjacencia[o].begin(); it !=adjacencia[o].end(); it++){
        auxiliar = *it;
        if(!visit[auxiliar.v]){
            taxadecambio(adjacencia,visit,auxiliar.v,d,multiplica(adjacencia,auxiliar,total),Pa,Pb);
        }
    }
}

int main() {
    int na,nb,c1,c2,origem,destino;
    char primeiro,igual;
    string pa,pb;
    vizinho a,b,resultado;
    resultado.numerador = resultado.denominador = 1;
    int i = 0;

    vector<vector<vizinho>> adj(61);
    vector<bool> visitados;
    map<string,int> mapa;

    cin>>primeiro;
    while(primeiro != '.'){
        if(primeiro == '!') {
            cin>>na>>pa>>igual>>nb>>pb;
            a.numerador = b.denominador = na;
            a.denominador = b.numerador = nb;
            c1 = procura(mapa,pa);
            c2 = procura(mapa,pb);
            a.v = c2;
            b.v = c1;
            adj[c1].push_back(a);
            adj[c2].push_back(b);
        }

        if(primeiro == '?') {
            cin>>pa>>igual>>pb;
            origem = procura(mapa,pa);
            destino = procura(mapa,pb);
            if(origem == -1 || destino == -1)
                cout<<"? "<<pa<<" "<<igual<<" "<<"? "<<pb<<endl;
            else {
                visitados.resize(0);
                visitados.resize(adj.size(),false);
                dfs(adj,visitados,origem);
                    if(visitados[destino]){
                        visitados.resize(0);
                        visitados.resize(adj.size(),false);
                        taxadecambio(adj,visitados,origem,destino,resultado,pa,pb);
                    }
                    else {
                        cout<<"? "<<pa<<" "<<igual<<" "<<"? "<<pb<<endl;
                    }
            }
        }
        resultado.denominador = resultado.numerador = 1;
        cin>>primeiro;
    }
 return 0;
}