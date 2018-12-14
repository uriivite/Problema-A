#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
	map<string,int> mA, mB;
	cout << "Introducir textos a comparar:" << endl;
	string A, B;
	getline(cin, A);
	getline(cin, B);
	cout << "\nTexto 1: " << A << "\n\nTexto 2: " << B << endl;
	int k;
	cout << "\nK: ";
	cin >> k;
	cout << k << endl;
	for(int i = 0; i < A.size()-k; ++i) {
		string aux = "";
		for(int j = i; j < i+k; ++j) {
			aux.insert(aux.end(),A[j]);
		}
		++mA[aux];
	}
	for(int i = 0; i < B.size()-k; ++i) {
		string aux = "";
		for(int j = i; j < i+k; ++j) {
			aux.insert(aux.end(),B[j]);
		}
		++mB[aux];
	}
	map<string,int>::iterator it;
	int unio = 0, inter = 0;
	//cout << "Similitudes: " << endl;
	for(it = mA.begin(); it != mA.end(); ++it) {
		if(mB.find(it->first) != mB.end()) {
			inter += mB.find(it->first)->second + it->second;
			//cout << "   " << it->first << endl;
		}
		unio += it->second;
	}
	for(it = mB.begin(); it != mB.end(); ++it) {
		unio += it->second;
	}
	cout << "Similitud de Jaccard: " << double(inter)/unio << endl;
	
	
}
	
