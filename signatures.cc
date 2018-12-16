#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <stdlib.h>

using namespace std;

#define INF 1000

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
    cout << "h" << i << ":	";
    for (int j = 0; j < v[0].size(); ++j) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
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
  for(int i = 0; i < A.size(); ++i) {
		if (A.size() - i + 1 > k) {
			string aux = "";
			for (int j = i; j < i+k; ++j)
				aux+=A[j];
			mA.insert(aux);
		}
  }
	for(int i = 0; i < B.size(); ++i) {
		if (B.size() - i + 1 > k) {
			string aux = "";
			for (int j = i; j < i+k; ++j)
				aux+=B[j];
			mB.insert(aux);
		}
  }
  // Generem el set universal
  set<string> universal;
  set<string>::iterator itA = mA.begin();
  while (itA != mA.end()) {
    universal.insert(*itA);
		++itA;
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
	for (int r = 0; r < univ_hash.size(); ++r) {
		for (int c = 0; c < sets.size(); ++c) {
			if (set_conte_shingle(r, univ_hash, sets[c]))
				for (int h = 0; h < 100; ++h) {
					int hi = ((rand()%10)*r + 1)%univ_hash.size();
					if (signatures[h][c] > hi)
						signatures[h][c] = hi;
				}
		}
	}
	//imprimir_signatures(signatures);
  cout << jaccard(signatures) << endl;
}
