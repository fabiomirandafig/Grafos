#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;

class UF {
	private:
		vector<int> p;
	public:
		void createSet(int t) {
			p.resize(t);
			for(int i=0;i<t;i++)
				p[i] = i;
		}
		int findSet(int e) {
			if (p[e]==e) return e;
			p[e] = findSet(p[e]);
			return p[e];
		}
		void mergeSets(int a,int b) {
			p[findSet(a)] = findSet(b);
		}
		bool isSameSet(int a,int b) {
			return (findSet(a)==findSet(b));
		}

};

struct aresta {
    aresta(int origem, int destino,int peso) : u(origem), v(destino), c(peso) {}
	int u,v,c;

    bool operator<(const aresta &a) {
	    return c<a.c;
}};

int main() {
    int N,n,m,u,v,c,aux,i;
    aux = i = 0;
    vector<aresta> roads;
    cin>>N;

    while(N>0){
        cin>>n>>m; i++;
        UF conjuntos;
        conjuntos.createSet(n);
        roads.reserve(m*m);
         
        for(int i = 0; i < m; i++){
            cin>>u>>v>>c;
            if(u == v)
                continue;
            roads.push_back(aresta(u,v,-c));
        }

        sort(roads.begin(),roads.end());
        aux = roads[0].c;

        for(const aresta &e:roads) {
            if(!conjuntos.isSameSet(e.u,e.v)) {
                if(e.c > aux)
                     aux = e.c;
                conjuntos.mergeSets(e.u,e.v);
             }
        }

        cout<<"Case #"<<i<<": "<<aux*-1<<endl;
        roads.clear();
        N--;
    }
    return 0;
}