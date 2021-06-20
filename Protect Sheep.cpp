#include<iostream>
#include<vector>
#include<string>
using namespace std;

void function(vector<string> &pasto, int linhas, int colunas){
    bool resposta = true;
    for(int l = 1; l <= linhas; l++){
        for(int c = 1; c <= colunas; c++){
            if(pasto[l][c] == 'S'){
                if(pasto[l][c-1] == 'W' || pasto[l][c+1] == 'W' || pasto[l-1][c] == 'W' || pasto[l+1][c] == 'W'){
                    resposta = false;
                    break;
                }
            }
        }
    }

    if(resposta) {
        cout<<"Yes"<<endl;
        for(int l = 1; l <= linhas; l++){
            for(int c = 1; c <= colunas; c++){
                if(pasto[l][c] == '.') {
                    pasto[l][c] = 'D';
                }   
            }
        }
        for(int l = 1; l <= linhas; l++){
            for(int c = 1; c <= colunas; c++){
                cout<<pasto[l][c]; 
            }
            cout<<endl;
        }
    }
    else
        cout<<"No"<<endl;
}

int main() {
    int R,C;
    cin>>R>>C;
    cin.ignore();
    vector<string> pasto;
    string temporaria,aux,extra;

    for(int i = 0; i < C+2; i++)
        aux.push_back('.');
    extra = '.';

    pasto.push_back(aux);
    for(int i = 0; i < R; i++){
        getline(cin,temporaria);
        extra = extra + temporaria + extra;
        pasto.push_back(extra);
        extra = '.';
    }
    pasto.push_back(aux);

    function(pasto,R,C);
    return 0;
}