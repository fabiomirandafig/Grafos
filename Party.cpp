#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

int MinimumGroups(vector<int> p2) {
    int totalGrupos = 0; 
    int node,aux,totalDeMenosUm,count;
    node = aux = totalDeMenosUm = count = 0;
    bool temFilho = false;

    for (int i = 0; i < p2.size(); i++) {
        if(p2[i] == -1) {
            node = i+1;
            totalDeMenosUm++;
            for(int j = 0; j < p2.size(); j++){
                if(p2[j] == node){
                    aux++;
                    temFilho = true;
                }
            }
            if(temFilho){
                count += aux;
            }
            else if(!temFilho)
                count += 1;
        }
    temFilho = false;
    aux = 0;
    } 

    if(totalDeMenosUm == 1)
        totalGrupos = p2.size();
    else
        totalGrupos = count;

    return totalGrupos;
}

int main() {
    int n, manager;
    vector<int> p;
    cin>>n;

    for(int i = 0; i < n; i++) {
        cin>>manager;
        p.push_back(manager);
    }

    int grupos = MinimumGroups(p);
    cout<<grupos<<endl;

    return 0;
}