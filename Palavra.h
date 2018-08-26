#ifndef PALAVRA_H
#define PALAVRA_H
#include <string>
#include <iostream>

class Palavra {
        private:
		std::string palavra; //Guarda uma determinada palavra
                int e; // Marca a ocorrência de algum enter no texto
                char chave; // Guarda os caracteres ao lado das palavras (. , ? , ! etc)
    
	public:
		Palavra();
		std::string getPalavra(); // Retorna palavra
		bool operator==(std::string p); // Operador == sobrecarregado
		bool verificaSemelhante(std::string p); // Verifica se duas palavras são iguais
                void setPalavra(std::string p); // Modifica a palavra a partir de outra passada como referência
                void set_enter(); // Modifica a o atributo e para indicar a ocorrencia de um enter no arquivo texto
                int get_enter(); // Retorna um enter para indicar o indice de um enter no arquivo texto
                char getChave(); // Retorna algum caracter especial(. , , , ? , ! , etc) que em algum dos lados de alguma palavra;
               

};

#endif /* PALAVRA_H */

