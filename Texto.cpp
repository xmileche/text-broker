#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Texto.h"
#include "Palavra.h"
using namespace std;

//Construtor da classe Texto
Texto::Texto(string arq) {
    arquivo = arq + ".txt"; //atribui o nome do arquivo da palavra passada como parametro 
    i = 0; 
    carregaTexto(); // Carrega todas as palavras do arquivo texto antes de manipular os métodos da classe
}

// Carrega todas as palavras de um arquivo texto e armazena em um vetor de palavras
void Texto::carregaTexto() {
	ifstream Arq((arquivo.c_str())); // Abre um arquivo texto 
	if(Arq.is_open()) { // Verifica se o arquivo foi aberto com sucesso
	string palavra2;
	while(Arq >> palavra2) // verifica todas as palavras no arquivo texto enquanto houver palavras
        {
            try {
                static int j = 0;
                palavra[j++].setPalavra(palavra2);
                if(Arq.peek() == '\n') {
                    palavra[j - 1].set_enter();  //Guarda todas as ocorrencias de enter no arquivo texto
                }
                
                //Caso for ultrapassado o limite do tamanho do vetor para leitura do arquivo texto
                //O programa é finalizado indicando um erro
                if(j > 10000) {       
                    throw 1;
                }
            }
            catch(int n) {
                cout << "Foi ultrapassado o limite do tamanho do vetor para o armazenamento de palavras!" << endl;
                exit(1);
            }
	}
	} else {
		cout << "Erro ao abrir arquivo." << endl; // Caso der erro ao abrir o arquivo
                exit(1);
        }
}

//Altera o valor de uma palavra por outra a partir da posição do iterador (i)
void Texto::altera(string p) {
    palavra[i].setPalavra(p);
}

// Incrementa o iterador i para percorrer o vetor de palavras do texto
void Texto::percorreTexto() {
    i = i+1;
}

// Retorna o valor de uma palavra na posição que esta o iterador i
string Texto::getPalavra(){
    return palavra[i].getPalavra();
}

// Grava os dados das palavras corridas a partir de um arquivo texto em um outro arquivo ou no próprio arquivo
void Texto::gravaemArq(string arqDestino) {
    int j = 0;
    ofstream arquivo(arqDestino.c_str()); // Abre o arquivo para gravaçao
	if(arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
		while( palavra[j].getPalavra() != "\0") { //Enquanto houver palavras no vetor de palavras, as mesmas serão repassadas no arquivo destino
                    arquivo << palavra[j].getPalavra();
                    if(palavra[j].getChave() != '\0') // Grava no arquivo o caracter especial do arquivo texto original
			arquivo << palavra[j].getChave();
                    if(palavra[j].get_enter()) // Grava no arquivo o enter do arquivo texto original
			arquivo << endl;
                    else if( palavra[j+1].getPalavra() != "\0" ) // Realiza os devidos espaçamentos no arquivo destino do texto
			arquivo << ' ';
                    j++;
                    
		}
	} else {
		 cout << "Erro no arquivo de destino." << endl; // Retorna caso der erro na abertura do arquivo
	}
}

// Altera o valor de uma palavra por outra na posição que foi passada como parametro no método
void Texto::altera(string p, int k) {
    palavra[k].setPalavra(p);
}

// Retorna o valor do iterador
int Texto::getIterador(){
    return i;
}

void Texto::predec_antec(){
    
    // Se é a primeira palavra do texto, retorna a palavra atual e a sucessora
    if(i == 0){ 
                cout << "Não há palavra anterior." << endl;
		cout << "Palavra posterior: " << palavra[i+1].getPalavra();
                if(palavra[i+1].getChave() != '\0' )
			cout << palavra[i+1].getChave() << endl;
                else
                    cout << endl;
        
        // Se é a ultima palavra do texto, retorna apenas a palavra antecessora e atual
	} else if (i == 9999) { 
            
		cout << "Palavra anterior: " << palavra[i-1].getPalavra();
		if( palavra[i-1].getChave() != '\0' )
                    cout << palavra[i-1].getChave() << endl;
                else
                    cout << endl;
                
		cout << "Não há palavra posterior." << endl;

        //Caso nao for nem a primeira palavra do texto e nem a ultima, retorna a palavra antecessora, atual e sucessora
	} else { 
		cout << "Palavra anterior: " << palavra[i-1].getPalavra();
		if( palavra[i-1].getChave() != '\0' )
			cout << palavra[i-1].getChave() << endl;
		else
                    cout << endl;
                
                cout << "Palavra posterior: " << palavra[i+1].getPalavra();
		if(palavra[i+1].getChave() != '\0' )
			cout << palavra[i+1].getChave() << endl;
                else
                    cout << endl;
	}
    
}

