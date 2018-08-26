#include "Dicionario.h"
#include "Arvore.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using std::ifstream;

// Construtor do dicionário
Dicionario::Dicionario() {
    armazenarDic();     // Assim que o construtor é chamado, o método para ler do dicionário também é chamado
}

// Destrutor do dicionário
Dicionario::~Dicionario() {
}


// Método que lê o txt do dicionário e chama método pra inserir cada palavra do dicionário
void Dicionario::armazenarDic(){
    string palavra2;
    ifstream Dic("dicUTF8.txt", ios::in);       // Abre o arquivo
	if(Dic.is_open())
        {
            while(Dic >> palavra2)      // Coloca cada palavra do dicionário na string
            { 
		inserePalavra(palavra2);    // Chama o método do DICIONÁRIO que insere palavras
            }
	}
        else            // Não foi possível abrir o arquivo
        {
            cout << "Erro ao abrir o arquivo." << endl;
	}
}

// Método que chama método público de inserção da árvore 
void Dicionario::inserePalavra(string n){   
    t.insere(n);
}

// Método que chama método público de busca da árvore
int Dicionario::consultaPalavra(string n){
    if(t.busca(n)){ // Caso encontrar a palavra retorna 1 (true), se nao retorna 0 (false)
	return 1;
    }
                
    else
	return 0;
}

// Método que lista todas as palavras semelhantes no dicionario a partir de uma palavra
int Dicionario::listaSemelhantes(string n){
    int tamanho = 0;
    
    // busca as palavras semelhantes
    t.buscaSemelhantes(n);
    
    // guarda o tamanho da busca
    tamanho = t.getTamanho();

    //Caso nao for encontrado nenhuma palavra semelhante
    if(!tamanho)
        return 0;
    
    // retorna a posição de cada palavra semelhante
    for(int i=0; i<tamanho; i++) {
        
        cout << i << "-) " << t.getPosicaoLista(i) << endl; 
    }
        return 1;
}

// Retorna a posição de uma palavra na lista de palavras semelhantes
string Dicionario::getSemelhante(int posicao) {
    
    return t.getPosicaoLista(posicao);
}

// Retorna o tamanho da lista de palavras semelhantes contruida
int Dicionario::getTamanhoLista() {    
    
    int tamanho;    
    tamanho = t.getTamanho();
    return tamanho;
}

// Seta tamanho da lista
void Dicionario::setTamanhoLista() {    
    t.setTamanho();
}

void Dicionario:: atualizarDic() {  
    t.armazenaDic();
}
    

