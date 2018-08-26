#ifndef TEXTO_H
#define TEXTO_H
#include <string>
#include "Palavra.h"

class Texto {
    private:
        int i; //iterador para percorrer o vetor de palavras a partir do arquivo texto
        std::string arquivo; // Nome do arquivo onde sera escrito e gravado
        Palavra palavra[10000]; // Vetor de Palavras
    public:
        Texto(std::string Arq);
        void carregaTexto(); //Método responsável por carregar todas as palavras de um arquivo texto
        void altera(std::string p); //Método responsável por alterar uma palavra no vetor de palavras pelo iterador sendo a posição
        void percorreTexto(); //Método responsável por percorrer o texto a partir do atributo iterador (i) da classe
        void gravaemArq(std::string arqDestino); //Método responsável por regravar o texto em algum arquivo passando pelo corretor ortográfico
        std::string getPalavra(); //Método responsável por recuperar uma palavra do vetor de palavras
        void altera(std::string p, int k); //Método responsável por alterar uma palavra a partir de uma determinada posição do vetor de palavras
        int getIterador(); //Método responsável por retornar o valor do iterador i da classe
        void predec_antec(); //Método responsável por pegar o a palavra antecessora e sucessora a palavra errada no texto 

};

#endif /* TEXTO_H */

