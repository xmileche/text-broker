#include "Palavra.h"
#include <cstring>
#include <algorithm>
using namespace std;

Palavra::Palavra() {
    // Não possui conteúdo na palavra quando é criada
    palavra = "\0";
    chave = '\0';
    e = 0;
}

// Retorna o conteudo da palavra
string Palavra::getPalavra(){
    return palavra;
}

// Realiza a sobrecarga no operador de igualdade
bool Palavra::operator==(string p){
    if(palavra == p)
            return 1;
    else
        return 0;
}

// Verifica se duas palavras são semelhantes se suas duas primeiras letras são iguais
bool Palavra::verificaSemelhante(string p){
	if(strncmp(palavra.c_str(), p.c_str(), 2))
		return 0; 
	else
		return 1;
}

// Seta uma palavra, guardando a palavra sem nenhum caracter especial no começo ou fim dela e o caracter especial que a acompanha
void Palavra:: setPalavra(string p){
    if( p[p.size() - 1] == '.' || p[p.size() - 1] == ',' || p[p.size() - 1] == '!' || p[p.size() - 1] == '?' ) {
		string copia;
		remove_copy(p.begin(), p.end(), back_inserter(copia), p[p.size() - 1]); 
		palavra = copia; // Guarda a palavra
		chave = p[p.size() - 1]; //Guarda o caracter especial que acompanha a palavra
    } else
        palavra = p; //Caso nao tiver caracter especial ao lado da palavra, guarda apenas ela
}

// Retorna o caracter especial
char Palavra:: getChave(){
    return chave;
}

// Seta a ocorrência de enter no arquivo texto
void Palavra:: set_enter(){
    e = 1;
}

// Retorna se houve a ocorrência ou não de enter no arquivo texto
int Palavra:: get_enter(){
    return e;
}
