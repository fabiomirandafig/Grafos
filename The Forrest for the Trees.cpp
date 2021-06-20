#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
using namespace std;

int main(){
    int testcases;
    cin>>testcases;

    while(testcases>0){
        cin.ignore();
        vector<pair <string,int>> vertices;
        vector<string>edges; 

        while(true){
            string s;
            getline(cin,s);
            if(s[0]=='*')
                break;
            edges.push_back(s);
        }

        string v,t;
        cin>>v;
        istringstream tokenizer(v);
        while (getline(tokenizer, t, ','))
            vertices.push_back(make_pair(t,0));

        int acorn,three;
        acorn = three = 0;
        
        for(int i = 0; i < edges.size(); i++){
            char c1 = edges[i][1];
            char c2 = edges[i][3];    
            for(int j = 0; j < vertices.size(); j++){
                if(c1 == vertices[j].first[0] || c2 == vertices[j].first[0])
                    vertices[j].second++;
            }
        }
    
        for(int i = 0 ; i < vertices.size();i++)
            if(vertices[i].second == 0)
                acorn++;
        
        three = vertices.size() - edges.size() - acorn;
        cout<<"There are "<<three<<" tree(s) and "<< acorn<<" acorn(s)."<<endl;

        testcases--;
    }

    return 0;
}