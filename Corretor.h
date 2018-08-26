#ifndef CORRETOR_H
#define CORRETOR_H
#include "Texto.h"
#include "Dicionario.h"

class Corretor {
    private:
        Texto *txt; // Aloca uma variavel do tipo Texto
        Dicionario *dic; // Aloca uma variavel do tipo Dicionario
        std::string palavrasErradas[10000]; //Aloca um vetor para todas as palavras erradas encontradas
        int qtdErros[10000]; // Guarda a quantidade de erros de cada palavra
        int selecionarSemelhante(int posicao); //Método privado que seleciona uma palavra na lista de semelhantes pela posição
        int getTamanhoSemelhantes(); //Método privado que retorna o tamanho da lista de semelhantes
        
    public:
        Corretor(std::string arquivo); //Construtor da classe Corretor
        void verificaErros(); // Método que verifica todos os erros encontrados no texto
        void corrigePalavra(std::string p); // Método que corrigi uma palavra do texto 
        void selecionaSemelhantes(std::string p); // Método que seleciona uma palavra na lista de semelhantes
        void adicionarDic(std::string p); // Método que adiciona uma nova palavra ao dicionario
        ~Corretor(); // Destrutor da classe Corretor
        bool exibeSemelhantes(std::string p); // Método que exibi todas as palavras semelhantes encontradas
        void corrigirPalavra(std::string palavra); // Método que corrigi uma determinada palavra do texto

};

#endif /* CORRETOR_H */
