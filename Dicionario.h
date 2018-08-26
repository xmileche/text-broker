#ifndef DICIONARIO_H
#define DICIONARIO_H
#include <iostream>
#include <string>
#include "Palavra.h"
#include "Arvore.h"
using namespace std;

class Dicionario {
    private:
        Arvore t; // Dicionário cria a árvore que as palavras ficarão armazenadas
    public:
        Dicionario(); // Construtor do dicionário
        void armazenarDic(); // Método que lê o txt do dicionário 
        void inserePalavra(string n); // Método que chama o método público de inserção da árvore
        int consultaPalavra(string n);  // Método que chama o método de busca da árvore
        int listaSemelhantes(string n); // Método responsável por listar todas as palavras semelhantes do dicionário a uma determinada palavra
        ~Dicionario();   // Destrutor do dicionário
        string getSemelhante(int posicao); // Método responsável por retornar a posição de uma palavra na lista de semelhantes
        int getTamanhoLista(); // Método responsável por retornar o tamanho da lista de palavras semelhantes
        void setTamanhoLista(); // Método responsável por setar o tamanho da lista de palavras semelhantes
        void atualizarDic(); // Grava dic
};

#endif /* DICIONARIO_H */
