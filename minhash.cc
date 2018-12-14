#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

#define INF 50000

// Tenim associats tots els shingles a un nombre diferent
map<int, string> hash_set (set<string>& s) {
	map<int, string> result;
	int i = 0;
	for (auto c : s) {
		result[i] = c;
		++i;
	}
	return result;
}

vector<int> permutacio (const vector<int>& v, int x) {
	vector<int> perm(v.size());
	for (auto i : v) {
		perm[i] = ( (x * v[i]) + 1)%v.size();
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
	map<int, string> univ_hash = hash_set(universal);
	// Obtenim un vector amb rang de valors = [0..nombre de shingles]
	// L'utilitzarem per anar fent permutacions
	int n = univ_hash.size();
	vector<int> rows(n);
	for (int i = 0; i < n; ++i)
		rows[i] = i;
		// Anem a generar cada permutacio, i despres obrindrem les diferents signatures
	for (int i = 0; i < n; ++i) {

	}
}
