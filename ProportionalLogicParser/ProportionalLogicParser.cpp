// Pedro Bianchini de Quadros
// Enunciado: Ctrl + V here

#include <iostream>

FILE* OpenFile();

int main()
{
    typedef struct Grammar {
        char Constante[2] = { 'T', 'F' };
        char Preposicao[100];
        char AbreParen = '(';
        char FechaParen = ')';
        char OperadorUnario = '~';
        char OperadorBinario[4] = { 'v', '^', '>', '-' };
        char Formula[100];
        char FormulaUnaria[100];
        char FormulaBinaria[100];
    };

    // Usando para ler o arquivo.
    FILE* arq;
    char Linha[100];
    char* result;

    // Abertura do arquivo
    arq = OpenFile();

    if (arq == NULL) {
        std::cout << "Problemas na abertura do arquivo" << '\n';
        return 0;
    }

    //Obtêm a primeira linha 
    result = fgets(Linha, 100, arq);
    if (result) {
        std::cout << result;
    }

    //Todo working


}

FILE* OpenFile() {
    return fopen("arq1.txt", "rt");;
}

// Assim consigo pular para a proxima linha como mostra abaixo
/*
    Linha[0]++;

    result = fgets(Linha, 100, arq);

    if (result) {
        std::cout << result << '\n';
    }

    Linha[0]++;

    result = fgets(Linha, 100, arq);

    if (result) {
        std::cout << result << '\n';
    }
*/
