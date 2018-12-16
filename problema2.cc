
#include <stdio.h>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


void jSeter(int k, string x, set<string>& s) {
    for(int i = 0; i <= x.size()-k; ++i) {
        string aux = "";
        for(int j = i; j < i+k; ++j) {
            aux.insert(aux.end(),x[j]);
        }
        s.insert(aux);
    }
}

set<string> jUnion(set<string> a, set<string> b) {
    set<string> x = a;
    x.insert(b.begin(),b.end());
    return x;
}

float jSim(string A, string B, int k, int t) {
    set<string> sA, sB;
    jSeter(k,A,sA);
    jSeter(k,B,sB);
    set<string> universal = jUnion(sA, sB);
    srand(universal.size());
    int contador = 0;
    for(int i = 0; i < t; i++){
        set<string>::iterator it = universal.begin();
        for(int j = 0; j < rand()%universal.size(); j++ )
            ++it;
        
        if(sA.find(*it) != sA.end() && sB.find(*it) != sB.end())
            ++contador;
            
    }
    return float(contador)/t;
}

int main() {
    string a,b;
     int k, t;
     getline(cin,a);
     getline(cin,b);
     cin >> k>> t;
    float resultat = jSim(a,b,k, t);
    cout << resultat << endl;
    
}
