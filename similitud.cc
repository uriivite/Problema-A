#include <iostream>
#include <string>
#include <vector>
#include <set>

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
	
int jInterseccion(set<string> a, set<string> b) {
	int inter = 0;
	set<string>::iterator it;
	for(it = a.begin(); it != a.end(); ++it) {
		if(b.find(*it) != b.end()) ++inter;
	}
	return inter;
}

void jSim(string A, string B, int k) {
	set<string> mA, mB;
	jSeter(k,A,mA); 
	jSeter(k,B,mB); 
	cout << float(jInterseccion(mA,mB))/(jUnion(mA,mB).size()) << endl;
}


void miniHash() {
	int nF,k;
	cin >> nF >> k; // nF = Numero de fitxer a pasarli, k = k-shingle
	string basura;
	getline(cin,basura);
	vector<string> textos(nF);
	vector<set<string> > sets(nF);
	set<string> total;
	for(int i = 0; i < nF; ++i) {
		string s;
		getline(cin,s);
		textos[i] = s;
		jSeter(k,s,sets[i]); 
		total = jUnion(sets[i],total);
	}
	for(set<string>::iterator it = total.begin(); it != total.end(); ++it) {
		if(it == total.begin()) {
			for(int q = 0; q < k; ++q) cout << ' ';
			for(int q = 0; q < nF; ++q) cout << " f" << q;
			cout << endl;
		}
		for(int i = 0; i < nF; ++i) {
			if(i == 0) cout << *it << ' ';
			if(sets[i].find(*it) != sets[i].end()) cout << "1  ";
			else cout << "0  ";
		}
		cout << endl;
	}
}


int main() { 
	/*string a,b;
	int k;
	getline(cin,a);
	getline(cin,b);
	cin >> k;
	jSim(a,b,k);*/
	miniHash(); //Només printa la taula de de shingles, no fa res més
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
