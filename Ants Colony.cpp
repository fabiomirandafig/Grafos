#include <iostream>
#include <vector>

using namespace std;

struct aresta {
    long long v,lenght;
};

long long distancia(aresta pai[],long long a, long long b, long long totalVertices){
    long long o = a;
    long long d = b;
    long long total = 0;

	vector<bool> v(totalVertices, false);
    
	v[a] = true;
	while (pai[a].v != -1) {
		v[a] = true;
		a = pai[a].v;
	}

	v[a] = true;
	while (!v[b]){
		b = pai[b].v;
    }

    while(o != b){
        total += pai[o].lenght;
        o = pai[o].v;
    }

    while(d != b) {
        total += pai[d].lenght;
        d = pai[d].v;
    }

	return total;
}

int main() {
    long long N,A,L,Q,S,T;
    cin>>N;

    while(N != 0){
        aresta pai[N];
        pai[0].v = -1;
        pai[0].lenght = 0;

        for(int i = 1; i <= N-1; i++){
            cin>>A>>L;
            pai[i].v = A;
            pai[i].lenght = L;
        }

        cin>>Q;
        for(int i = 0; i < Q; i++){
            cin>>S>>T;
            if(i == Q-1)
                cout<<distancia(pai,S,T,N);
            else    
                cout<<distancia(pai,S,T,N)<<" ";
        }   
        cout<<endl;
        cin>>N;
    }
    return 0;
}