#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

#define INF 50000

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

// Tenim associats tots els sets a un nombre diferent
map<int, set<string> > hash_sets (const set<string>& s1, const set<string>& s2) {
	map<int, set<string> > result;
	result[0] = s1; result[1] = s2;
	return result;
}

vector<int> permutacio (const vector<int>& v, int x) {
	vector<int> perm(v.size());
	for (auto i : v) {
		perm[i] = ( (x * v[i]) + 1)%v.size();
	}
	return v;
}

void jaccard(const set<string>& s1, const set<string>& s2) {
	int typeX = 0, ty = 0;
	//cout << "Similitudes: " << endl;
	set<string>::iterator it1;
	for(it = s1.begin(); it1 != s1.end(); ++it1) {
		if(s2.find(*it) != s2.end()) {
			inter += s2.find(it->first)->second + it->second;
			//cout << "   " << it->first << endl;
		}
		unio += it->second;
	}
	for(it = mB.begin(); it != mB.end(); ++it) {
		unio += it->second;
	}
	cout << "Similitud de Jaccard: " << double(inter)/unio << endl;
}

void sortida(const vector<set <string> >& si) {
	for (auto i : si) {
		for (auto j 1 : si) {
			jaccard(si[i], si[j]);
		}
	}
}


/* Retorna h(S)
string minHash(set<string> S, map<int, string>& univ_hash, vector<int>& rows) {
	// set<string>::iterator it;
	for (auto i : rows) {
		string aux = universal[i];
		if (S.find(aux) != S.end()) {
			// hem trobat la primera aparicio
			return aux;
		}
	}
}*/

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
	cout << k << endl;
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
	map<int, set<string> > sets = hash_sets(mA, mB);
	// Obtenim un vector amb rang de valors = [0..nombre de shingles]
	// L'utilitzarem per anar fent permutacions
	int nrows = univ_hash.size(); // IMPORTANT = El nombre de permutacions es (ara per ara) el nombre de shingles
	int columns = sets.size(); // El nombre de sets que tenim
	vector<vector<int> > result(nrows, INF);
	for (int i = 0; i < nrows; ++i) {
		string sh = univ_hash.find(i);
		int hi = (i + 1) % nrows;
		for (int j = 0; j < columns; ++j) {
			if (sets[j].find(sh) != sets[j].end()) {
				// A la M hi ha un 1
				for (int l = 0; l <= i; ++l) {
					if (result[l][j] > hi)
						result[l][j] = hi;
				}
			}
		}
	}
		// rows[i] = i;
		
	sortida(signatures);
}
