#include "Corretor.h"
#include "Texto.h"
#include <ctype.h>
#include <stdio.h>
using namespace std;

// Construtor da classe Corretor
Corretor::Corretor(string arquivo) {
    // Aloca um novo Texto guardando todas as suas palavras
    try {    
		txt = new Texto(arquivo);
	}
	catch (bad_alloc &memoryAllocationException) {
			cerr << "Uma exceção ocorreu: " << memoryAllocationException.what() << endl;
		}	
    
    //Aloca um dicionario com todas as suas palavras em uma arvore
    try {
		dic = new Dicionario;
	}
	catch (bad_alloc &memoryAllocationException) {
			cerr << "Uma exceção ocorreu: " << memoryAllocationException.what() << endl;
	}
    for(int i = 0; i < 10000; i++){ //Inicializa o vetor de quantidade e palavras erradas
        palavrasErradas[i] = "\0";
        qtdErros[i] = 0;
    }
}

// Corrigi uma determinada palavra do texto
void Corretor::corrigePalavra(string p) {
	txt->altera(p);
}

// Adiciona uma nova palavra ao dicionário
void Corretor::adicionarDic(string palavra) {
        dic->inserePalavra(palavra);
}

// Seleciona uma 
void Corretor::selecionaSemelhantes(string p){
    dic->listaSemelhantes(p);
}

// Exibi todas as palavras semelhantes com a palavra passada como parâmetro
bool Corretor::exibeSemelhantes(string p) {
    return dic->listaSemelhantes(p);   
}

// Verifica todos os erros encontrados no arquivo texto
void Corretor::verificaErros(){
    string p, palavra;
    string lower;
    int i, posicao, valor;
    int op;
    int percorre;
    
    p = txt->getPalavra();
    lower = p;
    
        int j = 0;
        
        //repassa todas as palavras para caracteres minusculos
        while(lower[j]) {
            lower[j] = tolower(lower[j]);
            j++;
        }
    
    // Enquanto houver para ser verificada no texto, as mesmas vao ser tratadas corretamente
    while(p != "\0") 
    {
        percorre = 0;
        if(!(dic->consultaPalavra(lower))){ // Verifica se palavra NÃO existe no dicionário, por isso a negação
            i = 0;
            while(palavrasErradas[i] != lower && palavrasErradas[i] != "\0"){
                i++;
            }
		if(palavrasErradas[i] != lower)
			palavrasErradas[i] = lower;
		qtdErros[i]++;
		
                cout << "*******************************************" << endl;		
		cout << "Erro: " << p << endl;
                txt->predec_antec();
                cout << "*******************************************" << endl;
		// ADICIONADO ANTECESSOR E POSTERIOR DA PALAVRA
                cout << endl;
                cout << "MENU - Escolha uma das seguintes opções:" << endl;
                cout << endl;
                cout << "#########################################################" << endl;
                cout << "# 1-) Corrigir palavra                                  #" << endl;
                cout << "# 2-) Ignorar erro ortográfico                          #" << endl;
                cout << "# 3-) Selecionar palavra semelhante                     #" << endl;
                cout << "# 4-) Adicionar palavra ao dicionário                   #" << endl;
                cout << "#########################################################" << endl;
                cout << endl;
                cout << "Opção: ";
                cin >> op;
                cout << endl;

                
                switch(op){
			case 1:
                            cout << "Insira a nova palavra correta: " << endl;
                            cin >> palavra;
                            cout << endl;
                            lower = palavra;
                            
                            j = 0;
        
                            while(lower[j]) {
                                lower[j] = tolower(lower[j]);
                                j++;
                            }
                            
                            if(dic->consultaPalavra(lower)){
                                corrigePalavra(palavra);
                                cout << "A palavra foi corrigida com sucesso!" << endl;
                            } else {
                                cout << "A palavra digitada não encontra-se no dicionário!" << endl;
                                percorre = 1;
                            }
                            
                             cout << endl;
                             
                        break;
                        
                        case 2:
                            cout << "O erro ortográfico foi ignorado!" << endl;
                            cout << endl;
                        break;
                        
                    case 3:  
                            if(exibeSemelhantes(lower)){
                                    cout << "Selecione a posicao da palavra para realizar a correção: ";
                                    cin >> posicao;
                                    cout << endl;
                                    valor = selecionarSemelhante(posicao);

                                    while(valor == 0) {
                                        cout << "A posicao não foi digitada corretamente, digite novamente a posicao!" << endl;
                                        cin >> posicao;
                                        valor = selecionarSemelhante(posicao);
                                        cout << endl;
                                    } 
                    
                                    dic->setTamanhoLista();
                                cout << "A palavra foi corrigida com sucesso no Texto!" << endl; 
                                cout << endl;
                            } else {
                                cout << "Não há palavras semelhantes no dicionário." << endl;
                                cout << endl;
                                percorre = 1;
                            }
                        break;           
                        
                        case 4:
                            adicionarDic(lower);
                            cout << "Palavra adicionada ao Dicionario." << endl;
                            cout << endl;
                            break;
                }
                          
        }
        
        if(!percorre)
            txt->percorreTexto();
	p = txt->getPalavra();
        lower = p;
    
        int j = 0;
        
        while(lower[j]) {
            lower[j] = tolower(lower[j]);
            j++;
        }
    }
    
        cout << "Exibir erros encontrados? (1 - Sim/2 - Não)" << endl;
	int opc;
	cin >> opc;
	if( opc == 1 ) {
            if (palavrasErradas[0] != "\0") { 
                for( i = 0 ; palavrasErradas[i] != lower && palavrasErradas[i] != "\0" ; i++ ) {
			cout << palavrasErradas[i] << ": " << qtdErros[i] << endl;
		}
            } else 
		cout << "Nao foi encontrado nenhum erro no arquivo." << endl;
	}

	cout << "Digite o nome do arquivo p/ gravação: ";
	string arqSaida;
	cin >> arqSaida;
	txt->gravaemArq(arqSaida+".txt");
        
        cout << endl;
        cout << "Deseja atualizar o arquivo do dicionário?" << endl;
        cout << "1-) Sim" << endl;
        cout << "2-) Não" << endl;
        cin >> op;
	
        if(op == 1){ 
            dic->atualizarDic();
            cout << "Dicionário atualizado com sucesso!" << endl;
        } else {
            cout << "Dicionário não foi atualizado." << endl;
        }
        
        
}

// Seleciona a posição da palavra na lista de semelhantes
int Corretor::selecionarSemelhante(int posicao) {
    string n;
    
    //Caso não existir a posicao na lista
    if(posicao < 0 || posicao >= getTamanhoSemelhantes()) {
        return 0;
    }
    
    n = dic->getSemelhante(posicao);
    
    // Corrigi a palavra com a posição escolhida
    corrigirPalavra(n);
    return 1;

}

// Retorna o tamanho da lista de palavras semelhantes
int Corretor::getTamanhoSemelhantes() {
    return dic->getTamanhoLista();
}

//Corrigi a palavra, a partir de outra passada como parâmetro na posição correta pelo iterador
void Corretor::corrigirPalavra(std::string palavra){
    txt->altera(palavra,txt->getIterador());
   
}

// Destrutor da palavra Corretor
Corretor::~Corretor() {    
    delete txt;
    delete dic;
}
