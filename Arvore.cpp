#include "Arvore.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;
using std::ifstream;

// Construtor que inicializa a árvore apontando para nada
Arvore::Arvore() {
    tamLista = 0;
    raiz = NULL;
}

// Método que verifica se a árvore está vazia
int Arvore:: vazia(){
    if(raiz == NULL)
        return 1;
    else
        return 0;
}

// Método público que chama método privado para inserir palavra na árvore
bool Arvore:: insere(string n){
    if(insere(raiz, n, &cresceu)){
        return 1;
    }
    else
        return 0;
}

bool Arvore:: remove(string n){
    if(remove(raiz, n, &mudouAltura))
        return 1;
    else
        return 0;
}

bool Arvore:: busca(string n){
    if(busca(raiz, n))
        return 1;
    else
        return 0;
}

void Arvore:: buscaSemelhantes(string n){
    
    listaSemelhante(raiz, n);

}

Arvore::~Arvore() {	
    destroi (raiz);
}

/****************MÉTODOS PRIVADOS**************/
//Método cria um novo nó, atualiza seus campos e retorna novo nó

/* Rotinas que auxiliam nas rotações da árvore AVL */

/* Rotação simples RR - Rotação Direira */
void Arvore:: RR(No *&t) {
    No* B = t->dir;
    t->dir = B->esq;
    B->esq = t;
    t->bal = 0;
    B->bal  = 0;
    t = B;
}

/* Rotação simples LL - Rotação Esquerda */
void Arvore:: LL(No *&t) {
    No* B = t->esq;
    t->esq = B->dir;
    B->dir = t;
    t->bal = 0;
    B->bal  = 0;
    t = B;
}

/* Rotação dupla RL - Rotação Direita-Esquerda*/
void Arvore:: RL(No *&t) {
    No* B = t->dir;
    No* C = B->esq;
    B->esq = C->dir;
    C->dir = B;
    t->dir = C->esq;
    C->esq = t;
    if (C->bal == -1) B->bal = +1; else B->bal = 0;
    if (C->bal == +1) t->bal = -1; else t->bal = 0;
    C->bal = 0;
    t = C;
}

/* Rotação dupla LR - Rotação Esquerda-Direita*/
void Arvore:: LR(No *&t) {
    No* B = t->esq;
    No* C = B->dir;
    B->dir = C->esq;
    C->esq = B;
    t->esq = C->dir;
    C->dir = t;
    if (C->bal == +1) B->bal = -1; else B->bal = 0;
    if (C->bal == -1) t->bal = +1; else t->bal = 0;
    C->bal = 0;
    t = C;
}

/* Rotação simples LL remove - Rotação Esquerda */
void Arvore:: rotLLremove(No *&p, int *mudouAltura) {
    No* A = p->esq;
    p->esq = A->dir;
    A->dir = p;
    if(A->bal == 0) {
        A->bal = 1;
        p->bal = -1;
        *mudouAltura = 0;
    } else {
        A->bal = 0;
        p->bal = 0;
        *mudouAltura = 1;
    }
    p = A;
}

/* Rotação simples RR remove - Rotação Direira */
void Arvore:: rotRRremove(No *&p, int *mudouAltura) {
    No* B = p->dir;
    p->dir = B->esq;
    B->esq = p;
    if (B->bal == 0) {
        B->bal = -1;
        p->bal = 1;
        *mudouAltura = 0;
    } else {
        B->bal = 0;
        p->bal = 0;
        *mudouAltura = 1;
    }
    p = B;
}

/* Rotação dupla LR remove - Rotação Esquerda-Direita*/
void Arvore:: rotLRremove(No *&p, int *mudouAltura) {
    *mudouAltura = 1;
    return LR(p);
}

/* Rotação dupla LR - Rotação Direita-Esquerda*/
void Arvore:: rotRLremove(No *&p, int *mudouAltura) {
    *mudouAltura = 0;
    return RL(p);
}

// Insere palavra nos nós
int Arvore:: insere(No *&t, string n, int *cresceu) {
    if(t == NULL){      // Achou o local da palavra, vamos inserir
        try {
			t = new No();   
		}
		catch (bad_alloc &memoryAllocationException) {
			cerr << "Uma exceção ocorreu: " << memoryAllocationException.what() << endl;
		}
        t->info.setPalavra(n);  // Função da classe palavra que modifica o conteúdo do nó
        *cresceu = 1;           // Foi inserido, propaga verificação
        return 1;
    }
    else if(t->info == n){      // Não insere palavras iguais
        *cresceu = 0;
        return 0;
    } else if( n < (t->info).getPalavra() ){
        if(insere(t->esq, n, cresceu)){
            if(*cresceu){       //inseriu na esquerda, vamos verificar balanceamento dos nós
                switch(t->bal){
                    case -1:
                        if (t->esq->bal== -1){ // sinais iguais – pendem para mesmo lado
                            LL(t);
                            *cresceu = 0;
                        }else if (t->esq->bal == 1){
                            LR(t);
                            *cresceu = 0;
                        }else{
                            LL(t); // retorna balanceado
                            *cresceu = 1;
                        }
                        break;

                    case 0:
                        t->bal = -1; // ficou maior à esq.
                        *cresceu = 1; // propaga verificação
                        break;
                    case 1: // era maior à direita
                        t->bal = 0; // balanceou com ins. esq
                        *cresceu = 0; //interrompe propagação
                        break;
                }
            }
            return 1;
        }
        else
            return 0;
    } else if( n > (t->info).getPalavra() ){
        if(insere(t->dir, n, cresceu)){
            if(*cresceu){       //inseriu na direita, vamos verificar balanceamento dos nós
                switch(t->bal){
                    case -1:
                        t->bal = 0; // balanceou com ins. esq
                        *cresceu = 0; //interrompe propagação
                        break;
                    case 0:
                        t->bal = 1; // ficou maior à dir
                        *cresceu = 1; // propaga verificação
                        break;
                    case 1: // era maior à direita
                        if (t->dir->bal == 1){ // sinais iguais – pendem para mesmo lado
                            RR(t);
                            *cresceu = 0;
                        }else if (t->dir->bal == -1){
                            RL(t); // retorna balanceado
                            *cresceu = 0;
                        }else{
                            RR(t);
                            *cresceu = 1;
                        }break;
                        
                }
            }
            return 1;
        }
        else
            return 0;
    }


}

bool Arvore:: sucessor(No *&atual, No *&proximo, int *mudouAltura){
    if(proximo->dir != NULL){
        if(sucessor(atual, proximo->dir, mudouAltura)){
            switch(proximo->bal){
                case -1:
                if (proximo->esq->bal== -1) // sinais iguais – pendem para mesmo lado
                    rotLLremove(proximo, mudouAltura);
                else rotLRremove(proximo, mudouAltura); // retorna balanceado
                break;

                case 0:
                    proximo->bal = -1;
                    *mudouAltura = 0;
                    break;

                case 1:
                    proximo->bal = 0;
                    *mudouAltura = 1;
                    break;
            }
        }
        return (0);
    } else {
        atual->info = proximo->info;
        atual = proximo;
        proximo = proximo->esq;
        return(1);
    }
}

int Arvore:: remove(No *&t, string n, int *mudouAltura) {
        if(t == NULL){     //Apenas retorna falso quando não encontra nenhum elemento
        return -1;
    } else if( n < (t->info).getPalavra() ){
        if(remove(t->esq, n, mudouAltura)){
            if(*mudouAltura){   //Vamos analisar o que acontece
                switch(t->bal) {
                    case -1:
                        t->bal = 0;
                        *mudouAltura = 1;
                        break;

                    case 0:
                        t->bal = 1;
                        *mudouAltura = 0;
                        break;

                    case 1: //sub árvore direita cresceu
                        //oooops, precisa balancear
                        //Houve remoção da esquerda então balanceia a direita
                        if (t->dir->bal == 1) // sinais iguais – pendem para mesmo lado
                            rotRRremove(t, mudouAltura);
                        else if (t->dir->bal == -1)
                            rotRLremove(t, mudouAltura); // retorna balanceado
                        else
                            rotRRremove(t, mudouAltura);
                        break;

                }
            }
        }
    } else if(n > (t->info).getPalavra() ){
        if(remove(t->dir, n, mudouAltura)){
            if(*mudouAltura){
                switch(t->bal) {
                    case -1:        //ops, precisa balancear
                        //Houve remoção da direita então balenceia a esquerda
                        if (t->esq->bal== -1) // sinais iguais – pendem para mesmo lado
                            rotLLremove(t, mudouAltura);
                        else if (t->esq->bal == 1)
                            rotLRremove(t, mudouAltura);
                        else
                            rotLLremove(t, mudouAltura); // retorna balanceado
                        break;

                    case 0:
                        t->bal = -1;
                        *mudouAltura = 0;
                        break;

                    case 1:
                        t->bal = 0;
                        *mudouAltura = 1;
                        break;

                }
            }
        }

    } else { //Encontrou o elemento
        No *aux;
        aux = *&t;

        if(aux->esq == NULL){
            t = aux->dir;
            *mudouAltura = 1;
            return 1;
        } else if (aux->dir == NULL){
            t = aux->esq;
            *mudouAltura = 1;
            return 1;
        } else {
            if(sucessor(aux, aux->esq, mudouAltura)) {
                switch (t->bal) {
                    case -1:
                        t->bal = 0;
                        *mudouAltura = 1;
                        break;

                    case 0:
                        t->bal = 1;
                        *mudouAltura = 0;
                        break;

                    case 1: //sub árvore direita cresceu
                        //oooops, precisa balancear
                        //Houve remoção da esquerda então balanceia a direita
                        if (t->dir->bal == 1) // sinais iguais – pendem para mesmo lado
                            rotRRremove(t, mudouAltura);
                        else if (t->dir->bal == -1)
                            rotRLremove(t, mudouAltura); // retorna balanceado
                        else
                            rotRRremove(t, mudouAltura);
                        break;

                }
            }
        }
        delete aux;
        return 1;
    }
    
}

// Busca uma palavra na árvore de dados
int Arvore::busca(No *t, string n){
	if(t == NULL)
		return 0;
	if( (t->info).getPalavra() > n) // Caso a palavra atual for maior que a passada como parâmetro no metodo
		return busca(t->esq, n);
	else if( (t->info).getPalavra() < n){ // Caso a palavra menor for menor que a passada como parâmetro no metodo
		return busca(t->dir, n);
	} else if( t->info == n) // Se encontrar a palavra na arvore
		return 1;
}

// Realiza um percurso em ordem na arvore
void Arvore::emOrdem(No *x, ofstream& arquivo){
	if (x != NULL){
            emOrdem(x->esq, arquivo);    
            arquivo << (x->info).getPalavra();
            arquivo << endl;
            emOrdem(x->dir, arquivo);  
	}
}


// Realiza uma busca para encontrar todas as palavras semelhantes no dicionario
void Arvore::listaSemelhante(No *raiz, string n) {
    
    // Caso chegar na raiz ou a arvore estiver vazia
    if(raiz == NULL) {
        
        return;
    }
    
    //Se as palavras que queremos procurar for menor
    if( n < (raiz->info).getPalavra() || (raiz->info).verificaSemelhante(n)) {
        
        listaSemelhante(raiz->esq, n);
    }
    
    //Se foi encontrada uma palavra semelhante
    if((raiz->info).verificaSemelhante(n)) {
        
        string n2 = (raiz->info).getPalavra();
        palavra[tamLista].setPalavra(n2);
        tamLista++;
    }
    
    //Se as palavras que queremos procurar for maior
    if(n > (raiz->info).getPalavra() || (raiz->info).verificaSemelhante(n)) {
        
        listaSemelhante(raiz->dir,n);
    }
}

// Retorna a palavra da lista de semelhantes atraves de sua posiçao
string Arvore::getPosicaoLista(int i) {
    return palavra[i].getPalavra();
}

// Retorna o tamanho da lista de palavras semelhantes
int Arvore::getTamanho() {
    return tamLista;
}

void Arvore::setTamanho() {
    tamLista = 0;
}

//Libera a memoria alocada, método chamado apenas no destrutor
void Arvore::destroi(No *raiz) {		
	if (raiz == NULL)
		return;
	destroi(raiz->esq);
	destroi(raiz->dir);
	free(raiz);
}

// Método que lê o txt do dicionário e chama método pra inserir cada palavra do dicionário
void Arvore::armazenarDic(){   
    string arqDestino = "dicUTF8.txt";
    ofstream arquivo(arqDestino.c_str()); // Abre o arquivo para gravaçao
	if(arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
            emOrdem(raiz, arquivo);
	} else {
		 cout << "Erro no arquivo de destino." << endl; // Retorna caso der erro na abertura do arquivo
	}
}

void Arvore::armazenaDic() {
    
    armazenarDic();
}
