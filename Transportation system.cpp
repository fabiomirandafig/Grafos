#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
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
    aresta(int X, int Y, double peso) : x(X), y(Y), p(peso) { }
	int x,y;
    double p;

    bool operator<(const aresta &a) {
	    return p<a.p;
} };

double distanciaEntreCidades(const array<int,2> &o, const array<int,2> &d){
    int distanciax = (d[0]-o[0]);
    int distanciay = (d[1]-o[1]);
    return sqrt((double) distanciax*distanciax + distanciay*distanciay);
}

int main() {
    int T,n,r,states;
    double extensionRoads, extensionRailRoads;
    int i = 0;
    extensionRoads = extensionRailRoads = 0;
    
    cin>>T;
    while(T>0) {
        states = 1;
        cin>>n>>r; i++;
        vector<array<int,2>> cities(n);
        UF conjuntos; conjuntos.createSet(n);

        vector<aresta> TransportationSystem;
        TransportationSystem.reserve(n*n);

        for(int i = 0; i < n; i++){
            cin>>cities[i][0]>>cities[i][1];
        }

        for(int i = 0; i < n; i++)
            for(int j = i + 1; j<n; j++) {
                TransportationSystem.push_back(aresta(i,j,distanciaEntreCidades(cities[i],cities[j])));
            }

        sort(TransportationSystem.begin(),TransportationSystem.end());

        for(const aresta &a:TransportationSystem) {
            if(!conjuntos.isSameSet(a.x,a.y)) {
                if(r <= a.p){
                    states++;
                    extensionRailRoads += a.p; 
                }
                else
                    extensionRoads += a.p;
                conjuntos.mergeSets(a.x,a.y);
            }
        }
        extensionRoads = round(extensionRoads);
		extensionRailRoads = round(extensionRailRoads);
        
        cout<<"Case #"<<i<<": "<<states<<" "<<extensionRoads<<" "<<extensionRailRoads<<endl;
        TransportationSystem.clear();
        extensionRailRoads = extensionRoads = 0;
        T--;
    }
}