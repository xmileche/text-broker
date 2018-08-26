#include <cstdlib>
#include <iostream>
#include "Corretor.h"

using namespace std;


int main() {
    string arquivo;
    cout << "#########################################" << endl;
    cout << "### Bem Vindo ao Corretor Ortográfico ###" << endl;
    cout << "#########################################" << endl;
    cout << endl;
    cout << "Insira o nome do arquivo texto: ";
    cin >> arquivo;
    cout << endl;
    
    Corretor c(arquivo); 
    
    c.verificaErros();
               
    return 0;
}
