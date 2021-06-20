#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<stack>
#include<list>

using namespace std;

void visitaVertice(vector<list<int>> &b,const int v) {
	cout << "Visitando vertice: "<< v+1 << endl;
}

void dfsRecursivo(vector<list<int>> &a,int visi[],int v) {	
	visi[v] = true;
	visitaVertice(a,v);	

    //     for (list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {

    for (list<int>::iterator it = a[v].begin(); it != a[v].end(); it++) {	
		if (!visi [*it]) 
			dfsRecursivo(a,visi,it); //Visita o vertice adjacente a v que ainda não foi descoberto...	
	}
}

int main() {
    int tnodes, tedges;
    int a,b;
    cin>>tnodes>>tedges;

    vector<list<int>> arvore(tnodes+1);

   for(int i = 0; i < tedges; i++){
        cin>>a>>b;
        arvore[a].push_back(b);
        arvore[b].push_back(a);
   }

    int *visitado = new int[tnodes];
	for(int i=0; i<tnodes; i++)
		visitado[i] = false;
    
    dfsRecursivo(arvore, visitado, 2);


    for(int i = 0.; i < arvore.size(); i++){
        for (list<int>::iterator it = arvore[i].begin(); it != arvore[i].end(); it++) {
            cout << *it <<" "; 
        } 
        cout<<endl;
    }

    // for (vector<int>::iterator it = tto.begin(); it != tto.end(); it++) {
    //     cout << *it <<" "; 
    // } 
    // cout<<endl;

	delete []visitado;
	return 0;

}