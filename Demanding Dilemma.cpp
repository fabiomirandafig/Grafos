#include <iostream>
#include <vector>

using namespace std;

int main () {
    int t; cin>>t;

    while (t > 0){
        int total=0;
        bool Maux=false;
        bool Maux2=true;
        int n,m; cin>>n>>m;

        vector<vector<int>> M(n,vector<int>(m));
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                cin>>M[i][j];
            }
        } 

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++){
                total += M[j][i];
            }  
            if (total==2)
                Maux = true;
            else
                Maux = false;
            total=0;
            if (!Maux) break;
        }

		int auxiliar=0;
        for (int j=0; j<m-1; j++) {
			if(Maux == false) break;
			for (int p=j+1; p<m; p++) {
				for (int i=0; i<n; i++) {
					if(M[i][j] == M[i][p])
						auxiliar++;
				}
				if (auxiliar == n) {
					Maux2=false;
					break;
				} 
                else 
                    auxiliar=0;
			}
			if (!Maux2) break;
        }

        if (m==0 && n>0 || (Maux && Maux2))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        t--;
    }
    return 0;
}