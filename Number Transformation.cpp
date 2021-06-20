#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

void bfsNumberTransformation(vector<vector<int>> &adj, vector<bool> &adicionado, vector<int> &ordem, const int origem,const int destino, const int &caso) {
    queue<int> fila;
    int aux = 0;
    bool termina = false;

    if(origem == destino){
        cout<<"Case "<<caso<<": "<<0<<endl;
        return;
    }

	fila.push(origem);
	ordem[origem]=0;
    adicionado[origem] = true;

    int vertice;
	while(!termina) {
        if(fila.empty()){
            cout<<"Case "<<caso<<": "<<"-1"<<endl;
            break;
        }
		vertice = fila.front(); fila.pop();
        vector<int>::const_iterator it;
    	for(it = adj[vertice].begin(); it !=adj[vertice].end(); it++){
            aux = vertice + (*it);
            if(aux > destino)
                continue;
			else if (!adicionado[aux]) {
				adicionado[aux] = true;
				ordem[aux] = ordem[vertice]+1;
				fila.push(aux);	  
                if(aux == destino){
                    cout<<"Case "<<caso<<": "<<ordem[aux]<<endl;
                    termina = true;	 
                    break;
                } 
    		}
		}
	}	
}

int main() {
    int T,s,t;
    int i = 0;

    vector<vector<int>> adj (1001);
    vector<bool> adicionado (1001,false);
    vector<int> ordem (1001,0);

    bool p;
    for(int i = 2; i <= 1000; i++){
        for(int j = 2; j <= i; j++){
            if(i % j == 0) {
                p = true;
                for(int k = 2; k <= sqrt(j); k++){
                    if(j % k == 0){
                        p = false;
                        break;
                    }
                }
                if(p){
                    if(j != i)
                        adj[i].push_back(j);
                }
            }
        }
    }        

    cin>>T;
    while(T>0){
        cin>>s>>t;
        i++;
        bfsNumberTransformation(adj,adicionado,ordem,s,t,i);
        ordem.resize(0);
        ordem.resize(1001,0);
        adicionado.resize(0);
        adicionado.resize(1001,false);
        T--;
    }
    return 0;
}