#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void geraMatriz(int **v, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			v[i][j] = rand() % 5 + 1 ;
		}
	}
}

void imprimeMatriz(int **v, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void somaMatriz(int **v1, int **v2, int **v3, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			v3[i][j] = v1[i][j] + v2[i][j];
		}
	}
}

bool comparaMatriz(int **A, int **B, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(A[i][j] != B[i][j])
				return false;
		}
	}
	return true;
}

void subtraiMatriz(int **v1, int **v2, int **v3, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			v3[i][j] = v1[i][j] - v2[i][j];
		}
	}
}



void multiplicaNormal(int **A, int **B, int **C, int n) {
	
	int la = 0, ca = 0, lb = 0, cb = 0, lc = 0, cc = 0;
	int somador = 0;
	
	while(la < n) {
		somador += A[la][ca] * B[lb][cb];
		ca++;
		lb++;
		if(ca == n) {
			C[lc][cc] = somador;
			cc++;
			if(cc == n) {
				lc++;
				cc = 0;
			}
			cb++;
			if(cb == n) {
				la++;
				cb = 0;
			}
			ca = 0;
			lb = 0;
			somador = 0;
		}
	}		
	
}

void multiplicaStrassen(int **A, int **B, int **C, int n) {	
	
	int **m1 = new int *[n/2], **m2 = new int *[n/2], **m3 = new int *[n/2], **m4 = new int *[n/2], **m5 = new int *[n/2], **m6 = new int *[n/2], **m7 = new int *[n/2];
	int **operacao1 = new int *[n/2], **operacao2 = new int *[n/2];
	int **a11 = new int *[n/2], **a12 = new int *[n/2], **a21 = new int *[n/2], **a22 = new int *[n/2];
	int **b11 = new int *[n/2], **b12 = new int *[n/2], **b21 = new int *[n/2], **b22 = new int *[n/2];
	int **c11 = new int *[n/2], **c12 = new int *[n/2], **c21 = new int *[n/2], **c22 = new int *[n/2];
	
	for(int i = 0; i < n / 2; i++) {
		m1[i] = new int [n/2];
		m2[i] = new int [n/2];
		m3[i] = new int [n/2];
		m4[i] = new int [n/2];
		m5[i] = new int [n/2];
		m6[i] = new int [n/2];
		m7[i] = new int [n/2];
		a11[i] = new int [n/2];
		a12[i] = new int [n/2];
		a21[i] = new int [n/2];
		a22[i] = new int [n/2];
		b11[i] = new int [n/2];
		b12[i] = new int [n/2];
		b21[i] = new int [n/2];
		b22[i] = new int [n/2];
		c11[i] = new int [n/2];
		c12[i] = new int [n/2];
		c21[i] = new int [n/2];
		c22[i] = new int [n/2];
		operacao1[i] = new int [n/2];
		operacao2[i] = new int [n/2];
	}
	
	if(n == 2) {
		multiplicaNormal(A, B, C, n);
		return;
	}
	
	else {
		for(int i = 0; i < n/2; i++) {
			for(int j = 0; j < n/2; j++) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + (n/2)];
				a21[i][j] = A[i + (n/2)][j];
				a22[i][j] = A[i + (n/2)][j + (n/2)];
				
				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + (n/2)];
				b21[i][j] = B[i + (n/2)][j];
				b22[i][j] = B[i + (n/2)][j + (n/2)];
			}
		}
				
		somaMatriz(a11, a22, operacao1, n/2);  somaMatriz(b11, b22, operacao2, n/2); multiplicaStrassen(operacao1, operacao2, m1, n/2);
		somaMatriz(a21, a22, operacao1, n/2);  multiplicaStrassen(operacao1, b11, m2, n/2);
		subtraiMatriz(b12, b22, operacao2, n/2); multiplicaStrassen(a11, operacao2, m3, n/2);
		subtraiMatriz(b21, b11, operacao2, n/2);  multiplicaStrassen(a22, operacao2, m4, n/2);
		somaMatriz(a11, a12, operacao1, n/2); multiplicaStrassen(operacao1, b22, m5, n/2);
		subtraiMatriz(a21, a11, operacao1, n/2); somaMatriz(b11, b12, operacao2, n/2); multiplicaStrassen(operacao1, operacao2, m6, n/2);
		subtraiMatriz(a12, a22, operacao1, n/2); somaMatriz(b21, b22, operacao2, n/2); multiplicaStrassen(operacao1, operacao2, m7, n/2);
		
				
		somaMatriz(m1, m4, operacao1, n/2); somaMatriz(operacao1, m7, operacao2, n/2); subtraiMatriz(operacao2, m5, c11, n/2);
		somaMatriz(m3, m5, c12, n/2);
		somaMatriz(m2, m4, c21, n/2);
	    somaMatriz(m1, m3, operacao1, n/2);	somaMatriz(operacao1, m6, operacao2, n/2);  subtraiMatriz(operacao2, m2, c22, n/2);
	    
	    for(int i = 0; i < n/2; i++) {
			for(int j = 0; j < n/2; j++) {
				C[i][j] = c11[i][j];
				C[i][j + n/2] = c12[i][j];
				C[i + n/2][j] = c21[i][j];
				C[i + n/2][j + n/2] = c22[i][j];	
			}
		}
	}
	
	for (int i = 0; i < n/2; i++) {
    	delete[] m1[i];
    	delete[] m2[i];
    	delete[] m3[i];
    	delete[] m4[i];
    	delete[] m5[i];
    	delete[] m6[i];
    	delete[] m7[i];
    	delete[] a11[i];
    	delete[] a12[i];
    	delete[] a21[i];
    	delete[] a22[i];
    	delete[] b11[i];
    	delete[] b12[i];
    	delete[] b21[i];
    	delete[] b22[i];
    	delete[] c11[i];
    	delete[] c12[i];
    	delete[] c21[i];
    	delete[] c22[i];
    	delete[] operacao1[i];
    	delete[] operacao2[i];
	}
	
	delete[] m1;
    delete[] m2;
    delete[] m3;
    delete[] m4;
    delete[] m5;
    delete[] m6;
    delete[] m7;
    delete[] a11;
    delete[] a12;
    delete[] a21;
    delete[] a22;
    delete[] b11;
    delete[] b12;
    delete[] b21;
    delete[] b22;
    delete[] c11;
    delete[] c12;
    delete[] c21;
    delete[] c22;
    delete[] operacao1;
    delete[] operacao2;	
}

int main() {
	
	int n;
	double tempoIN, tempoFN, tempoIS, tempoFS, tempoN, tempoS;
	
	cout << "Entre o tamanho N das matrizes (NxN)" << endl;
	cout << "N = ";
	cin >> n;
	
	int **A = new int *[n], **B = new int *[n];
	int **C1 = new int *[n], **C2 = new int *[n];
	
	for(int i = 0; i < n; i++) {
		A[i] = new int [n];
		B[i] = new int [n];
		C1[i] = new int [n];
		C2[i] = new int [n];
	}
	
	srand(time(NULL));
	geraMatriz(A, n);
	srand(time(NULL) * 2);
	geraMatriz(B, n);	
	
	tempoIN = time(NULL);
	multiplicaNormal(A, B, C1, n);
	tempoFN = time(NULL);
	tempoN = difftime(tempoFN, tempoIN);
	cout << "Tempo total (em segundos) do algoritmo normal: " << tempoN  << " segundos."<< endl;
	multiplicaStrassen(A, B, C2, n);
	tempoFN = time(NULL);
	tempoN = difftime(tempoFN, tempoIN);
	cout << "Tempo total (em segundos) do algoritmo de Strassen: " << tempoN  << " segundos."<< endl;
	cout << endl;
	
	
	cout << "As matrizes geradas sao iguais?" << endl;
	if(comparaMatriz(C1, C2, n) == true)
		cout << "Sim" << endl;
	else
		cout << "Não" << endl;
			
	
	
	return 0;
}
