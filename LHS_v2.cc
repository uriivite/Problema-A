#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define INF 1000

//////////////////////////////////////////////////////

void imprimir_signatures(vector<vector<int> >& v) {
    for (int i = 0; i < v.size(); ++i){
        cout << "h" << i << ":    ";
        for (int j = 0; j < v[0].size(); ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void printSet(set<string>& s) {
    for (auto c : s)
        cout << c << " ";
}

void print_hash(map<int, string>& m) {
    for (int i = 0; i < m.size(); ++i) {
        cout << i << ": " << m[i] << endl;
    }
}

///////////////////////////////////////////////////////////////////77

void jSeter(int k, string x, set<string>& s) {
    for(int i = 0; i <= x.size()-k; ++i) {
        string aux = "";
        for(int j = i; j < i+k; ++j)
            aux.insert(aux.end(),x[j]);
        s.insert(aux);
    }
}

set<string> jUnion(const set<string>& a, const set<string>& b) {
    set<string> x = a;
    x.insert(b.begin(),b.end());
    return x;
}

double jaccard(std::vector<std::vector<int> >& v) {
    double sim = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i][0] == v[i][1]) ++sim;
    }
    return sim/v.size();
}

// Tenim associats tots els shingles a un nombre diferent
map<int, string> hash_shingles (set<string>& s) {
    map<int, string> result;
    int i = 0;
    set<string>::iterator it = s.begin();
    while (it != s.end()) {
        result[i] = *it;
        ++it;
        ++i;
    }
    return result;
}

bool set_conte_shingle(int row, map<int, string>& univ_hash, set<string>& s) {
    string sh = univ_hash[row];
    return !(s.find(sh) == s.end());
}

void init_signatures(vector<vector<int> >& v) {
    vector<int> inf(v[0].size(), INF);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = inf;
    }
}

int main() {

    cout << "Nombre de documents:" << endl;
    int n; cin >> n;
    cout << "K: "; int k; cin >> k;
    cout << "Insereix els documents:" << endl;
    map<int, set<string> > D;
    set<string> universal;
    string saux;
    getline(cin, saux);
    int i = 0;
    while (i < n) {
        string doc;
        getline(cin, doc);
        set<string> sD;
        jSeter(k, doc, sD);
        //cout << "S" << i << ": ";
        //printSet(sD); cout << endl;
        universal = jUnion(universal, sD);
        D[i] = sD;
        ++i;
    }
    map<int, string> univ_hash = hash_shingles(universal);
    int b;
    cout << "Introdueix el nombre de band " << endl;
    cin >> b;
    while(univ_hash.size() %b != 0) {
        cout << "Introdueix un nombre divisor de " << univ_hash.size() << endl;
        cin >> b;
    }
    int r = univ_hash.size()/b;
    vector<vector<int> > signatures(r, vector<int>(D.size()));
    set< pair<int,int> > similars;
    double t = pow((double) 1/b,(double) 1/r);
    for (int i = 0; i < b; ++i) {
      init_signatures(signatures);
      for (int j = i*r; j < (i*r)+r; ++j) {
          for (int c = 0; c < D.size(); ++c) {
              if (set_conte_shingle(j, univ_hash, D[c])) {
                  srand(r);
                  for (int h = 0; h < r; ++h) {
                      int hi = ((rand()%10)*j + 1)%r;
                      if (signatures[h][c] > hi)
                          signatures[h][c] = hi;
                  }
              }
          }
      }
      for (int j = 0; j < D.size(); j ++) {
          for(int m = j+1; m < D.size(); m++) {
              if(similars.find(make_pair(j, m)) == similars.end()) {
                  vector < vector <int> > aux(r,vector<int>(2));
                  for(int l = i*r; l < (i*r)+r; l++) {
                      aux[l%r][0] = signatures[l][j];
                      aux[l%r][1] = signatures[l][m];
                  }
                  if(jaccard(aux) >= t){
                      similars.insert(make_pair(j,m));
                  }
              }
          }
      }
    }
    cout << "Documents candidats a ser similars amb una precisio del " << t << ":" << endl;
    for (auto s : similars){
        cout << s.first << " " << s.second << endl;
    }



        //  cout << jaccard(signatures) << endl;
}
