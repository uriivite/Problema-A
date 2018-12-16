#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <stdlib.h>

using namespace std;

#define INF 1000

//////////////////////////////////////////////////////

void imprimir_signatures(vector<vector<int> >& v) {
  for (int i = 0; i < v.size(); ++i){
    cout << "h" << i << ":	";
    for (int j = 0; j < v[0].size(); ++j) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
}

void printSet(set<string>& s) {
  for (auto c : s)
    cout << c << endl;
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
        for(int j = i; j < i+k; ++j) {
            aux.insert(aux.end(),x[j]);
        }
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
  cout << "Tria el nombre de documents: ";
  int n; cin >> n;
  cout << "K: "; int k; cin >> k;
  cout << "Insereix els documents:" << endl;
  map<int, set<string> > D;
  set<string> universal;
  for (int i = 0; i < n; ++i) {
    string doc;
    cout << "Peta aqui" << endl;
    getline(cin, doc);
    set<string> sD;
    jSeter(k, doc, sD);
    cout << "Ara peta" << endl;
    universal = jUnion(universal, sD);
    cout << "Has falat jeje" << endl;
    D[i] = sD;
  }
  map<int, string> univ_hash = hash_shingles(universal);
  vector<vector<int> > signatures(univ_hash.size(), vector<int>(D.size()));
  init_signatures(signatures);
	for (int r = 0; r < univ_hash.size(); ++r) {
		for (int c = 0; c < D.size(); ++c) {
			if (set_conte_shingle(r, univ_hash, D[c])) {
        srand(univ_hash.size());
				for (int h = 0; h < univ_hash.size(); ++h) {
					int hi = ((rand()%10)*r + 1)%univ_hash.size();
					if (signatures[h][c] > hi)
						signatures[h][c] = hi;
				}
      }
		}
	}
  imprimir_signatures(signatures);
  cout << jaccard(signatures) << endl;
}
