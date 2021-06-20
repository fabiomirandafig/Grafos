//UTILIZANDO ARRAY

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <array>
using namespace std;

typedef double tipoPeso;

class UnionFind {
	private:
		vector<int> representante;
	public:
		void createSet(int tam) {
			representante.resize(tam);
			for(int i=0;i<tam;i++)
				representante[i] = i;
		}
		//Retorna o representante do conjunto que contem
		//o elemento "elemento"
		int findSet(int elemento) {
			if (representante[elemento]==elemento) 
				return elemento;
			//Compressao do caminho...
			representante[elemento] = findSet(representante[elemento]);
			return representante[elemento];
		}
		void mergeSets(int i,int j) {
			representante[ findSet(i) ] = findSet(j);
		}
		bool isSameSet(int i,int j) {
			return (findSet(i)==findSet(j));
		}

};

struct Edge {
    Edge(int u0, int v0,double peso0) : u(u0), v(v0), peso(peso0) { }
	int u, v;
	double peso;

    bool operator<(const Edge &other) {
	    return peso<other.peso;
}
};

double distancia(const array<int,2> &a, const array<int,2> &b){
    int dx = (b[0]-a[0]);
    int dy = (b[1]-a[1]);
    //return sqrt(dx*dx + dy*dy);
    return ((double) dx*dx + dy*dy);
}

int main() {
    int n;
    cin >> n;
    vector < array<int,2> > cidades(n);
    for (int i = 0; i < n; i++)
        cin>>cidades[i][0] >> cidades[i][1];

    vector < Edge> arestas;
     arestas.reserve(n*n);

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j<n; j++) {
            arestas.push_back(Edge(i,j,distancia(cidades[i],cidades[j])));
        }
    sort(arestas.begin(),arestas.end());

    //Kruskal:
    //crie vetor de arestas
    //ordene vetor por peso
    //adicione as arestas desde que nao forme ciclos...

    UnionFind uf;
    uf.createSet(n);
    int m;
    cin>>m;
    for(int i = 0; i < m; i++){
        int u,v;
        cin>>u>>v; u--; v--;
        uf.mergeSets(u,v); //ja começa a union find com essas estradas...
    }

    for(const Edge &e:arestas) {
        //se nao forma ciclo --> adicione ao resultado..
        if(!uf.isSameSet(e.u,e.v)) {
            //adicione (u,v) a AGM
            cout<<(e.u+1)<<" "<<(e.v+1)<<"\n";
            uf.mergeSets(e.u,e.v);//informe que u e v estão no mesmo CC
        }
    }
}

//UTILIZANDO VECTOR

// #include <iostream>
// #include <string>
// #include <algorithm>
// #include <fstream>
// #include <vector>
// #include <list>
// #include <cmath>
// #include <sstream>
// #include <queue>
// #include <cstdlib>
// #include <array>
// using namespace std;

// class UnionFind {
// 	private:
// 		vector<int> representante;
// 	public:
// 		void createSet(int tam) {
// 			representante.resize(tam);
// 			for(int i=0;i<tam;i++)
// 				representante[i] = i;
// 		}
// 		//Retorna o representante do conjunto que contem
// 		//o elemento "elemento"
// 		int findSet(int elemento) {
// 			if (representante[elemento]==elemento) 
// 				return elemento;
// 			//Compressao do caminho...
// 			representante[elemento] = findSet(representante[elemento]);
// 			return representante[elemento];
// 		}
// 		void mergeSets(int i,int j) {
// 			representante[ findSet(i) ] = findSet(j);
// 		}
// 		bool isSameSet(int i,int j) {
// 			return (findSet(i)==findSet(j));
// 		}

// };

// struct Edge {
//     Edge(int u0, int v0,double peso0) : u(u0), v(v0), peso(peso0) { }
// 	int u, v;
// 	double peso;

//     bool operator<(const Edge &other) {
// 	    return peso<other.peso;
// }
// };

// double distancia(const vector<int> &a, const vector<int> &b){
//     int dx = (b[0]-a[0]);
//     int dy = (b[1]-a[1]);
//     //return sqrt((double)dx*dx + dy*dy);
//     return ((double)dx*dx + dy*dy);
// }

// int main() {
//     int n;
//     cin >> n;
//     vector < vector<int> > cidades(n,vector<int>(2));
//     for (int i = 0; i < n; i++)
//         cin>>cidades[i][0] >> cidades[i][1];

//     vector < Edge> arestas;
//     arestas.reserve(n*n);

//     for(int i = 0; i < n; i++)
//         for(int j = i + 1; j<n; j++) {
//             arestas.push_back(Edge(i,j,distancia(cidades[i],cidades[j])));
//         }
//     sort(arestas.begin(),arestas.end());

//     //Kruskal:
//     //crie vetor de arestas
//     //ordene vetor por peso
//     //adicione as arestas desde que nao forme ciclos...

//     UnionFind uf;
//     uf.createSet(n);
//     int m;
//     cin>>m;
//     for(int i = 0; i < m; i++){
//         int u,v;
//         cin>>u>>v; u--; v--;
//         uf.mergeSets(u,v); //ja começa a union find com essas estradas...
//     }

//     for(int i = 0; i < arestas.size(); i++) {
//         const Edge &e = arestas[i];
//         //se nao forma ciclo --> adicione ao resultado..
//         if(!uf.isSameSet(e.u,e.v)) {
//             //adicione (u,v) a AGM
//             cout<<(e.u+1)<<" "<<(e.v+1)<<"\n";
//             uf.mergeSets(e.u,e.v);//informe que u e v estão no mesmo CC
//         }
//     }
// }