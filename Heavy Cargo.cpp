#include <iostream>
#include <string>
#include <map>

using namespace std;

int mapeia(map<string,int> &M, string &S){
    int ID = -1;
    map<string,int>::iterator iterator;   
    for(iterator = M.begin(); iterator != M.end(); iterator++) {
        if(iterator->first == S){
            ID = iterator->second;
        }
    }
    if(ID == -1) {
        ID = M.size();
        M[S] = ID;
    }
    return ID;
}

int main() {
    int n,r,weight;
    int i = 1;
    string citya,cityb,start,destination;
    cin>>n>>r;

    while(n != 0 && r != 0){
        int matrix[n][n];
        fill(matrix[0],matrix[0] + n * n,0);
        map<string,int> mapa;

        for(int i = 0; i < r; i++){
            cin>>citya>>cityb>>weight;
            int id1 = mapeia(mapa,citya);
            int id2 = mapeia(mapa,cityb);  
            if(weight > matrix[id1][id2]){
                matrix[id1][id2] = weight;         
                matrix[id2][id1] = weight;
            }         
        }

        cin>>start>>destination;
        int origem = mapeia(mapa,start);
        int destino = mapeia(mapa,destination);
       
        for(int k=0; k<n; k++)
			for(int i=0; i<n; i++)
				for(int j=0; j<n; j++)
						matrix[i][j] = max(matrix[i][j], min(matrix[i][k],matrix[k][j]));

		cout<<"Scenario #"<<i<<endl;
		cout<<matrix[origem][destino]<<" tons"<<endl;
        cout<<endl;
        cin>>n>>r; i++;
    }
    return 0;
}