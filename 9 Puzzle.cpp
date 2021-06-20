#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

string origem = "123456789";
string matriz[3][3] = {};

string movimentoHorizontal(string a, int linha){
	string rotacionadoH;
	int c = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			matriz[i][j]= a[c];
			c++;
		}
	}
	matriz[linha][0] = a[3*linha + 1];
	matriz[linha][1] = a[3*linha + 2];
	matriz[linha][2] = a[3*linha];

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			rotacionadoH += matriz[i][j];

	return rotacionadoH;
}

string movimentoVertical(string a, int coluna) {
	string rotacionadoV;
	int c = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			matriz[i][j]= a[c];
			c++;
		}
	}
	matriz[0][coluna] = a[3*2 + coluna];
	matriz[1][coluna] = a[coluna];
	matriz[2][coluna] = a[3+coluna];

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			rotacionadoV += matriz[i][j];

	return rotacionadoV;
}

void Caminho(string estado,map<string,string> &pai,map<string,string> &caminho) {
    if (estado == origem) 
		return;
    else {
       	cout<<caminho[estado].c_str();
        Caminho(pai[estado],pai,caminho);
    }
}

void MinimoMovimentos(map<string,int> &ordem,map<string,string> &pai,map<string,string> &caminho) {
	string vertice,auxlinha,auxcoluna,str,str2;
	queue<string> fila;
	fila.push(origem);
	ordem.insert(pair<string,int>(origem,0));

	while(!fila.empty()) {
		vertice = fila.front(); 
		fila.pop();		
		for(int linha = 0; linha < 3; linha++) {
			auxlinha = movimentoHorizontal(vertice,linha);
			if(ordem.count(auxlinha) == false){
				str = to_string(linha+1);
				pai.insert(pair<string,string>(auxlinha,vertice));
				caminho.insert(pair<string,string>(auxlinha,'H'+ str));
				ordem.insert(pair<string,int>(auxlinha, ordem[vertice] + 1));
				fila.push(auxlinha);
			}
		}
		for(int coluna = 0; coluna < 3; coluna++) {
			auxcoluna = movimentoVertical(vertice,coluna);
			if(ordem.count(auxcoluna) == false){
				str2 = to_string(coluna+1);
				pai.insert(pair<string,string>(auxcoluna,vertice));
				caminho.insert(pair<string,string>(auxcoluna,'V'+ str2));
				ordem.insert(pair<string,int>(auxcoluna, ordem[vertice] + 1));
				fila.push(auxcoluna);
			}
		}
	}
}	

int main() {
	int count = 0;
	vector<string> input;
    string temporaria, aux;
	map<string,int> ordem;
	map<string,string> caminho,pai;

    while(getline(cin,temporaria)){
		for(int i = 0; i < 5; i = i+2)
			aux += temporaria[i];
		count++;
		if(count == 3){
			input.push_back(aux);
			count = 0;
			aux.erase();
		}
        if(temporaria[0] == '0') break;
    }

	MinimoMovimentos(ordem,pai,caminho);
	
	for(int i = 0; i < input.size(); i++){
		if(origem == input[i])
			cout<<"0"<<endl;
		else if(ordem.count(input[i])==true){
			cout<<ordem[input[i]]<<" ";
			Caminho(input[i],pai,caminho);
			cout<<endl;
		}
		else
			cout<<"Not solvable"<<endl;
	}	
	return 0;
}