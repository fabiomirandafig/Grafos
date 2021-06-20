#include <iostream>
#include <vector>

using namespace std;

void Joe(vector<vector<char>> &Maze, vector<pair<int,int>> &jAux, int R,int C, char caracter, bool &Escape, int l,int c) {
	if (l<0 || c<0 || c>=C || l>=R || Maze[l][c]!=caracter) return;

    Maze[l][c] = 'J';
    jAux.resize(jAux.size()+1);
    jAux[jAux.size()-1].first = l;
    jAux[jAux.size()-1].second = c;
	
    if(l==0 || c==0 || l == (R-1) || c == (C -1)) Escape = true;
}

void Fire(vector<vector<char>> &Maze, vector<pair<int,int>> &fAux, int R, int C, char caracter, int l, int c) {
	if (l<0 || c<0 || c>=C || l>=R || Maze[l][c]!=caracter ) return;
	
    Maze[l][c] = 'F';
    fAux.resize(fAux.size()+1);
    fAux[fAux.size()-1].first = l;
    fAux[fAux.size()-1].second = c;
}

int main(){
    int n; cin>>n;
    while(n>0){
        int R,C,tJ,tF; 
        vector<pair<int,int>> J,auxJ,F,auxF;
        bool out = false;
        tJ = tF = 0;
        cin>>R>>C;

        vector<vector<char>> maze(R,vector<char>(C));

        for(int l=0; l < R; l++){
            for(int c=0; c<C; c++){
                cin >> maze[l][c];
                if(maze[l][c] == 'F'){
                    F.resize(tF+1);
                    F[tF].first = l; F[tF].second = c;
                    tF++;
                }
                else if(maze[l][c] == 'J'){
                    if(l == 0 || l == (R-1) ||  c == 0 || c == (C-1)){
                        cout << 1 << endl;
                        out = true;
                    }
                    J.resize(tJ+1);
                    J[tJ].first = l; J[tJ].second = c;
                    tJ++;
                }
            }
        }

        if(!out){
            int D = 1;
            bool escape, v;
            escape = v = false;

            for(int l=0; l<R; l++){
                for(int c=0; c<C; c++){
                    if(!v){
                        for(int p=0; p<F.size(); p++){
                            Fire(maze,auxF,R,C,'.',F[p].first,F[p].second);
                            Fire(maze,auxF,R,C,'.',F[p].first-1,F[p].second);
                            Fire(maze,auxF,R,C,'.',F[p].first+1,F[p].second);
                            Fire(maze,auxF,R,C,'.',F[p].first,F[p].second-1);
                            Fire(maze,auxF,R,C,'.',F[p].first,F[p].second+1);

                        }
                        F = auxF;
                        auxF.resize(0);
                        v = true;
                    }
                    for(int p=0; p<J.size(); p++){
                        Joe(maze,auxJ,R,C,'.',escape,J[p].first,J[p].second);
                        Joe(maze,auxJ,R,C,'.',escape,J[p].first-1,J[p].second);
                        Joe(maze,auxJ,R,C,'.',escape,J[p].first+1,J[p].second);
                        Joe(maze,auxJ,R,C,'.',escape,J[p].first,J[p].second-1);
                        Joe(maze,auxJ,R,C,'.',escape,J[p].first,J[p].second+1);

                        if(escape){
                            D++; 
                            cout << D << endl; 
                            break;
                        }
                    }
                    D++;
                    v = false;
                    J = auxJ;
                    auxJ.resize(0);
                    if(escape) break;
                }
                if(escape) break;
            }
            if(!escape)
                cout << "IMPOSSIBLE" << endl;
        }
        n--;
    }
    return 0;
}