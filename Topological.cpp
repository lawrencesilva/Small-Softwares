#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

typedef struct lista lista;

struct lista {
	string aponta;
};

bool eNumero(char testa) {
	if(testa == '0' || testa == '1' || testa == '2' || testa == '3' || testa == '4' ||  testa == '5' || testa == '6' || testa == '7' || testa == '8' || testa == '9')
		return true;
	else
		return false;	
}

int qualNumero(char numero) {
	switch(numero) {
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		default :
			return 9;
			break;									
	}
}

void adicionar(int *pilha, int &topo, int numero) {
	pilha[topo] = numero;
	topo++;
	return;
}

int tirar(int *pilha, int &topo) {
	int numero = pilha[topo - 1];
	topo--;
	return numero;
}

int main() {
	
	int v, a, algarismos = 0, copia, soma = 0, anda = 0, salva;
	bool achou = false;
	
	cin >> v >> a;
	
	lista vertices[v];
	int entrada[v];
	int final[v];
	int proximo[v];
	int topo = 0;
	
	for(int i = 0; i < v; i++) {
		entrada[i] = 0;
	}
	
	cin.ignore();
	
	for(int i = 0; i < v; i++) {
		getline(cin, vertices[i].aponta);
	}
	
	for(int i = 0; i < v; i++) {
		for(int j = 0; vertices[i].aponta[j] != '\0'; j++) {
			copia = j;
			while(eNumero(vertices[i].aponta[copia])) {
				algarismos++;
				copia++;
			}
			while(eNumero(vertices[i].aponta[j])) {
				soma += qualNumero(vertices[i].aponta[j]) * pow(10, algarismos - 1);
				algarismos--;
				j++;
			}
			
			entrada[soma - 1]++;
			soma = 0;
			algarismos = 0;	
		}	
	}
	
	while(true) {
		for(int i = 0; i < v; i++) {
			if(entrada[i] == 0) {
				entrada[i] = -1;
				achou = true;
				final[anda] = i + 1;
				anda++;
				adicionar(proximo, topo, i);
			}
		}
		
		while(topo > 0) {
			salva = tirar(proximo, topo);
			
			for(int j = 0; vertices[salva].aponta[j] != '\0'; j++) {
				copia = j;
				while(eNumero(vertices[salva].aponta[copia])) {
					algarismos++;
					copia++;
				}
				while(eNumero(vertices[salva].aponta[j])) {
					soma += qualNumero(vertices[salva].aponta[j]) * pow(10, algarismos - 1);
					algarismos--;
					j++;
				}
				
				entrada[soma - 1]--;
				soma = 0;
				algarismos = 0;	
			}
		}
		
		if(achou == false) {
			break;
		}
		
		achou = false;
	}
	
	for(int i = 0; i < v; i++) {
		cout << final[i] << " ";
	}
	
	cout << endl;
	
	
	return 0;
}
