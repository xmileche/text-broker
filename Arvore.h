#ifndef ARVORE_H
#define ARVORE_H
#include <string>
#include "Palavra.h"
#include <new> //operador new padrao
using namespace std;

class Arvore {
    private:
        // Classe referente a cada nó
        class No{           
                    public:
                        No *esq, *dir; // Ponteiros 
                        Palavra info; // Palavra armazenada
                        int bal; // Bal do nó
        };

        int tamLista; // Guarda o tamanho da lista de palavras semelhantes
        Palavra palavra[10000]; // Guarda 
        No *raiz; //Guarda o primeiro nó da arvore (nó raiz)
        int n;
        int cresceu; // Indica se a arvore cresceu ou não durante a inserção de um elemento          
        int mudouAltura; // Indica se houve uma mudança de altura na arvore durante a remoção de um elemento
        int insere(No *&t, std::string n, int *cresceu); // Método privado responsável por realizar a inserção de uma determinada palavra na arvore
        int remove(No *&t, std::string n, int *mudouAltura); // Método privado responsável por realizar a remoção de uma determinada palavra na arvore
        void RR(No *&t); // Método privado responsável por realizar uma rotação simples para a esquerda caso a inserção desequilibrar a arvore
        void LL(No *&t); // Método privado responsável por relaizar uma rotação simples para a direita caso a inserção desequilibrar a arvore
        void RL(No *&t); // Método privado responsável por realizar uma rotação dupla a esquerda e depois para a direita caso a inserção desequilibrar a arvore
        void LR(No *&t); // Método privado responsável por realizar uma rotação dupla a direita e depois para a esquerda caso a inserção desequilibrar a arvore
        void rotLLremove(No *&p, int *mudouAltura); // Método privado responsável por rotacionar de forma simples uma sub-arvore a direita caso a remocao desiquilibrar a arvore
        void rotLRremove(No *&p, int *mudouAltura); // Método privado responsável por realizar uma rotação dupla em uma sub-arvore para direita e depois para esquerda caso a remocao desequilibrar a arvore
        void rotRRremove(No *&p, int *mudouAltura); // Método privado responsável por rotacionar de forma simples uma sub-arvore a direita caso a remocao desiquilibrar a arvore
        void rotRLremove(No *&p, int *mudouAltura); // Método privado responsável por realizar uma rotação dupla em uma sub-arvore para esquerda e depois para direita caso a remocao desequilibrar a arvore
        bool sucessor(No *&atual, No *&proximo, int *mudouAltura); // Método privado responsável
        int busca(No *t, std::string n); // Método privado responsável por buscar uma determinada palavra na arvore
        void emOrdem(No *x, ofstream& arquivo); // Método privado responsável por realizar um percurso em ordem na arvore
        void listaSemelhante(No *raiz, std::string n); // Método privado responsável por buscar palavras semelhantes na arvore a partir dos dois primeiros caracteres de uma determinada palavra
        void destroi (No *raiz); //Libera a memoria alocada, método chamado apenas no destrutor
        void armazenarDic(); // Armazena dicionário novo
    public:
        Arvore(); // Construtor que inicializa a árvore com a raíz para nulo
        int vazia(); // Método responsável por verifica se a árvore está vazia
        bool insere(std::string n); // Método responsável por verificar se a inserção de uma palavra foi realizada com sucesso ou não no dicionário
        bool busca(std::string n); // Método responsável por verificar se uma determinada palavra esta contida ou não no dicionário
        void buscaSemelhantes(std::string n); //Método responsável por buscar palavras semelhantes na arvore por uma busca de semelhantes privada
        bool remove(std::string n); // Método responsável por indicar se uma determinada palavra na árvore foi removida ou não
        ~Arvore(); // Destrutor da arvore, libera todos os nós
        std::string getPosicaoLista(int i); // Método responsável por retornar a posição de uma palavra da lista de palavras que foram encontradas semelhantes
        int getTamanho(); // Método responsável por retornar o número de palavras semelhantes encontradas
        void setTamanho(); 
        void armazenaDic();
};

#endif /* ARVORE_H */
