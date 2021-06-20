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

struct aresta{
    aresta(double X, double Y, double peso) : x(X), y(Y), p(peso) { }
	double x,y,p;

    bool operator<(const aresta &a) {
	    return p<a.p;
} };

double distanciaEntreFreckles(const array<double,2> &o, const array<double,2> &d){
    double distanciax = (d[0]-o[0]);
    double distanciay = (d[1]-o[1]);
    return sqrt(distanciax*distanciax + distanciay*distanciay);
}

int main() {
    int N,n;
    double total;
    cin>>N;

    while(N>0){
        total = 0.0;
        cin>>n;
        vector<array<double,2>> freckles(n);
        UF uf; uf.createSet(n);
        vector<aresta> distancia;
        distancia.reserve(n*n);

        for(int i = 0; i < n; i++){
            cin>>freckles[i][0]>>freckles[i][1];
        }

        for(int i = 0; i < n; i++)
            for(int j = i + 1; j<n; j++) {
            distancia.push_back(aresta(i,j,distanciaEntreFreckles(freckles[i],freckles[j])));
        }
        sort(distancia.begin(),distancia.end());
       
        for(const aresta &a:distancia) {
            if(!uf.isSameSet(a.x,a.y)) {
                total += a.p;
                uf.mergeSets(a.x,a.y);
            }
        }

        cout<<fixed<<setprecision(2);
        cout<<total<<endl;
        if(N>1)cout<<endl;

        N--;
    }
}