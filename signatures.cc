#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

#define INF 1000

// Tenim associats tots els shingles a un nombre diferent
map<int, string> hash_shingles (set<string>& s) {
	map<int, string> result;
	int i = 0;
	for (auto c : s) {
		result[i] = c;
		++i;
	}
	return result;
}

/*void imprimir_universal(map<int, string>& m) {
  for (int i = 0; i < m.size(); ++i) {
    cout << m[i] << endl;
  }
}

void imprimir_sets(std::vector<set<string> >& v) {
  for (auto i : v) {
    for (auto s : i) {
      cout << s << endl;
    }
  }
}*/

void imprimir_signatures(vector<vector<int> >& v) {
  for (int i = 0; i < v.size(); ++i){
    cout << "h" << i << ": ";
    for (int j = 0; j < v[0].size(); ++j) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
}

bool set_conte_shingle(int row, map<int, string>& univ_hash, set<string>& s) {
  string sh = univ_hash[row];
  return (s.find(sh) != s.end());
}

void init_signatures(vector<vector<int> >& v) {
  vector<int> inf(v[0].size(), INF);
  for (int i = 0; i < v.size(); ++i) {
    v[i] = inf;
  }
}

int main() {
  set<string> mA, mB;
  cout << "Introducir textos a comparar:" << endl;
  string A, B;
  getline(cin, A);
  getline(cin, B);
  cout << "\nTexto 1: " << A << "\n\nTexto 2: " << B << endl;
  int k;
  cout << "\nK: ";
  cin >> k;
  // Obtenim els diferents sets de cada text
  for(int i = 0; i < A.size()-k; ++i) {
    string aux = "";
    for(int j = i; j < i+k; ++j) {
      aux.insert(aux.end(),A[j]);
    }
    mA.insert(aux);
  }
  for(int i = 0; i < B.size()-k; ++i) {
    string aux = "";
    for(int j = i; j < i+k; ++j) {
      aux.insert(aux.end(),B[j]);
    }
    mB.insert(aux);
  }
  // Generem el set universal
  set<string> universal;
  set<string>::iterator itA = mA.begin();
  while (itA != mA.end()) {
    universal.insert(*itA); ++itA;
  }
  set<string>::iterator itB = mB.begin();
  while (itB != mB.end()) {
    universal.insert(*itB);
    ++itB;
  }
  map<int, string> univ_hash = hash_shingles(universal);
  //imprimir_universal(univ_hash);
  vector<set<string> > sets(2);
  sets[0] = mA; sets[1] = mB;
  //imprimir_sets(sets);
  vector<vector<int> > signatures(100, vector<int>(sets.size())); // 100 permutacions
                                                        // tantes columnes com dels textos tinguem
  init_signatures(signatures);
  for (int i = 0; i < 100; ++i) {
    int permutacio = (3*i + 1)% 100;
    for (int j = 0; j < univ_hash.size(); ++j) {
      for (int k = 0; k < sets.size(); ++k) {
        if (set_conte_shingle(j, univ_hash, sets[k])) {
          if (signatures[i][k] > permutacio)
            signatures[i][k] = permutacio;
        }
      }
    }
  }
  imprimir_signatures(signatures);
}
