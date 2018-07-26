#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

void adiciona(int pilha[], int &topo, int num) {
	pilha[topo] = num;
	topo++;
	return;
}

void adiciona(char pilha[], int &topo, char operacao) {
	pilha[topo] = operacao;
	topo++;
	return;
}

void remove(int pilha[], int &topo) {
	topo--;
}

void remove(char pilha[], int &topo) {
	topo--;
	return;
}

int retornaTopo(int pilha[], int topo) {
	if(topo == 0) {
		cout << "Pilha vazia!" << endl;
		return NULL;
	}
	return pilha[topo - 1];
}

char retornaTopo(char pilha[], int topo) {
	if(topo == 0) {
		cout << "Pilha vazia!" << endl;
		return NULL;
	}
	return pilha[topo - 1];
}

bool eOperacao(char testa) {
	if(testa == '+' || testa == '-' || testa == 'x' || testa == 'X' || testa == '*' || testa == '/')
		return true;
	else
		return false;	
}

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

int opera(char operacao, int A, int B) {
	switch(operacao) {
		case 'x':
			return A * B;
			break;
		case 'X':
			return A * B;
			break;
		case '*':
			return A * B;
			break;
		case '+':
			return A + B;
			break;
		case '/':
			return A / B;
			break;	
		default :
			return A - B;
			break;									
	}
}

int main() {
	int anda = 0, copia, soma = 0, algarismos = 1, A, B, operado;
	char operador;
	int pilha1[100];
	char pilha2[100];
	int topo1 = 0, topo2 = 0;
	string entrada;
	int resultado;
	
	cout << "Entre com a operacao: ";
	getline(cin, entrada);
	cout << endl;
	
	while(entrada[anda] != '\0') {
		if(eOperacao(entrada[anda]) == true) {
			adiciona(pilha2, topo2, entrada[anda]);
			anda++;
			continue;
		}
		if(eNumero(entrada[anda]) == true) {
			copia = anda + 1;
			while(eNumero(entrada[copia]) == true) {
				algarismos *= 10;
				copia++;
			}
			copia = anda + 1;
			soma += qualNumero(entrada[anda]) * algarismos;
			algarismos /= 10;
			while(eNumero(entrada[copia]) == true) {
				soma += qualNumero(entrada[copia]) * algarismos;
				algarismos /= 10;
				copia++;
			}
	
			adiciona(pilha1, topo1, soma);		
			algarismos = 1;
			soma = 0;
			anda = copia;
			continue;
		}
		if(entrada[anda] == ')') {
			B = retornaTopo(pilha1, topo1);
			remove(pilha1, topo1);
			A = retornaTopo(pilha1, topo1);
			remove(pilha1, topo1);
			operador = retornaTopo(pilha2, topo2);
			remove(pilha2, topo2);
			operado = opera(operador, A, B);
			adiciona(pilha1, topo1, operado);
			anda++;
			continue;
		}
		
		anda++;	
	}
	
	
	resultado = retornaTopo(pilha1, topo1);
	
	cout << "O resultado da operacao e: " << resultado << endl;
		
	return 0;
}
