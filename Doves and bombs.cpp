#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void findPigeonValue(int u, const vector<vector<int>> &adj, vector<int> &dfsParent, vector<int> &dfsNum, vector<int> &dfsLow, vector<int> &Articulacoes, int &dfsCount, int &rootChildren, int dfsRoot) {
	dfsNum[u] = dfsLow[u] = ++dfsCount;
	for(int v:adj[u]) {
		if (dfsNum[v] == 0) { 
			dfsParent[v] = u; 
			if (u == dfsRoot) 
				rootChildren++; 

			findPigeonValue(v,adj,dfsParent,dfsNum,dfsLow,Articulacoes,dfsCount,rootChildren,dfsRoot);

			if (dfsLow[v] >= dfsNum[u])
				Articulacoes[u]++;
			dfsLow[u] = min(dfsLow[u], dfsLow[v]);
		}
		else if (v != dfsParent[u])
			dfsLow[u] = min(dfsLow[u], dfsNum[v]); 
	}
}

void func(const vector<vector<int>> &adj, vector<int> &Articulacoes) {
	int nv = adj.size();
    int dfsCount = 0;
    vector<int> dfsParent(nv,-1);
	vector<int> dfsNum(nv,0);	
    vector<int> dfsLow(nv,0);
    
	Articulacoes.resize(0);
	Articulacoes.resize(nv,1);

	for(int i=0;i<nv;i++) {
		if(dfsNum[i]==0) {
			int filhos = 0; 
			findPigeonValue(i,adj,dfsParent,dfsNum,dfsLow,Articulacoes,dfsCount,filhos,i);
			if(filhos<=1)
                Articulacoes[i] = 1;
            else   
                Articulacoes[i] -=1;
		}
	}
}

bool func2(pair<int,int>& a, pair<int,int> &b) {
    if(a.first<b.first)
        return false;
	else if(a.first>b.first)
        return true;
	else {
		if(b.second<a.second)
            return false;
		else if(a.second<b.second)
            return true;
		else 
            return 0;
	}
}

void BestCandidate(vector<vector<int>> &Graph, int N, int M){
    vector<int> Articulacoes;
    vector<pair<int,int>> PigeonValues;    
    
    func(Graph,Articulacoes);

    for(int i = 0; i < N; i++)
        PigeonValues.push_back(make_pair(Articulacoes[i],i));

    sort(PigeonValues.begin(),PigeonValues.end(),func2);

    for(int i=0; i<M; i++)
        cout<<PigeonValues[i].second<<" "<<PigeonValues[i].first<<endl;
    cout<<endl;
}

int main() {
	int n,m,u,v;
    bool termina = false;
    
    cin>>n>>m;
    vector<vector<int>> adj(n);

	while(!termina) {		
        cin>>u>>v;
        if(u == -1 && v == -1){
            BestCandidate(adj,n,m);
            cin>>n>>m;
            if(n == 0 && m == 0){
                termina = true;
                break; 
            }
            adj.clear();
            adj.resize(n);
            continue;
        }
        adj[u].push_back(v);	
        adj[v].push_back(u);	
	}

    return 0;
}