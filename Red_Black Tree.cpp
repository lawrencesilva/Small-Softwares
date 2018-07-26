#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct node* arvore;  

struct node {
	int valor;
	char cor;
	struct node *esquerda;
	struct node *direita;
};

char cor(struct node *x) {
	if(x == NULL) {
		return 'P';
	}
	else
		return x->cor;
}

void trocaCor(struct node *x) {
	if(x->cor == 'V')
		x->cor = 'P';
		
	else if (x->cor == 'P')
		x->cor = 'V';
		
	if(x->esquerda->cor != NULL) {
		if(x->esquerda->cor == 'V')
			x->esquerda->cor = 'P';
		else 
			x->esquerda->cor = 'V';
	}
	
	if(x->direita->cor != NULL) {
		if(x->direita->cor == 'V')
			x->direita->cor = 'P';
		else 
			x->direita->cor = 'V';
	}				
}

struct node* giraEsquerda(struct node *x) {
	struct node* y = x->direita;
	x->direita = y->esquerda;
	y->esquerda = x;
	y->cor = x->cor;
	x->cor = 'V';
	return y;
}

struct node* giraDireita(struct node *x) {
	struct node* y = x->esquerda;
	x->esquerda = y->direita;
	y->direita = x;
	y->cor = x->cor;
	x->cor = 'V';
	return y;
}

struct node* trocaEsquerda(struct node *x) {
	trocaCor(x);
	if(cor(x->direita->esquerda) == 'V') {
		x->direita = giraDireita(x->direita);
		x = giraEsquerda(x);
		trocaCor(x);
	}
	return x;
}

struct node* trocaDireita(struct node *x) {
	trocaCor(x);
	if(cor(x->esquerda->esquerda) == 'V') {
		x = giraDireita(x);
		trocaCor(x);
	}
	return x;
}

struct node* conserta(struct node *x) {
	if(cor(x->direita) == 'V') {
		x = giraEsquerda(x);
	}
	if(x->esquerda != NULL && cor(x->direita) == 'V' && cor(x->esquerda->esquerda) == 'V') {
		x = giraDireita(x);
	}
	if(cor(x->esquerda) == 'V' && cor(x->direita) == 'V') {
		trocaCor(x);
	}
	return x;
}

struct node* insereNode(struct node *x, int valor, int *guarda) {
	if(x == NULL) {
		struct node *novo;
		novo = (struct node*) malloc(sizeof(struct node));
		if(novo == NULL) {
			*guarda = 0;
			return NULL;
		}
	novo->valor = valor;
	novo->cor = 'V';
	novo->direita = NULL;
	novo->esquerda = NULL;
	*guarda = 1;
	return novo;
	}
	
	if(valor == x->valor) {
		*guarda = 0;
	}
	else {
		if(valor < x->valor) {
			x->esquerda = insereNode(x->esquerda, valor, guarda);
		}
		else {
			x->direita = insereNode(x->direita, valor, guarda);
		}
	}
	
	if(cor(x->direita) == 'V' && cor(x->esquerda) == 'P') {
		x = giraEsquerda(x);
	}
	
	if(cor(x->esquerda) == 'V' && cor(x->esquerda->esquerda) == 'V') {
		x = giraDireita(x);
	}
	
	if(cor(x->esquerda) == 'V' && cor(x->esquerda) == 'V') {
		trocaCor(x);
	}
	
	
	return x;
}

int insereArvore(arvore *raiz, int valor) {
	int valido;
	
	*raiz = insereNode(*raiz, valor, &valido);
	
	if((*raiz) != NULL) {
		(*raiz)->cor = 'P';
	}
		
	return valido;
}

int main() {
	
	arvore *raiz;
	int valor, guarda;
		
	while(true) {
		cout << "Entre o valor do no(-100 para acabar): ";	
		cin >> valor;
		if(valor == 100) {
			break;
		}
		guarda = insereArvore(raiz, valor);
	}
	
	
	
	
	
	
}
