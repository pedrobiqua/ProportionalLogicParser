// Pedro Bianchini de Quadros
// Enunciado: Ctrl + V here

#include <iostream>
//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
void VerifyLatex(const char* result, int j);
const char* checkOperator(const char* result, int j);
bool VerifyNeg(const char* result, int j);
bool VerifyWedge(const char* result, int j);
bool VerifyRightArrow(const char* result, int j);
bool VerifyLeftRightArrow(const char* result, int j);

int main() {
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

    // Percorre todo o arquivo
    while (!feof(arq)) {
        // Obtêm a linha
        result = fgets(Linha, 100, arq);
        if (result) {
            // Percorre toda a linha
            for (int j = 0; j < (lengthOfArray(result) - 1); j++) {
                //Verifica se tem Latex
                VerifyLatex(result, j);
            }
        }
    }
    fclose(arq);

    // Todo working
    // std::cout << gramatica.Constante[0] << '\n';
    // std::cout << gramatica.Constante[1] << '\n';
}

FILE* OpenFile() { return fopen("arq1.txt", "rt"); }

int lengthOfArray(const char* arr) {
    int size = 0;

    while (*arr) {
        size += 1;
        arr += 1;
    }

    return size;
}

void VerifyLatex(const char* result, int j) {
    if (result[j] == '\\') {
        std::cout << checkOperator(result, j);
    }
}

// Verifica os operadores
const char* checkOperator(const char* result, int j) {
    const char* nameOperator;
    if (result[j + 1] == 'n' && result[j + 2] == 'e' && result[j + 3] == 'g') {
        nameOperator = "\\neg";
        return nameOperator;

    }
    else if (VerifyNeg(result, j)) {
        nameOperator = "";
        return nameOperator;

    }
    else if (VerifyWedge(result, j)) {
        nameOperator = "\\wedge";
        return nameOperator;

    }
    else if (VerifyRightArrow(result, j)) {
        nameOperator = "\\rightarrow";
        return nameOperator;

    }
    else if (VerifyLeftRightArrow(result, j)) {
        nameOperator = "\\leftrightarrow";
        return nameOperator;

    }
    else {
        std::cout << "Sintaxe errada na linha: " << result << '\n';
        return 0;
    }
}

// Função para verificar a sintaxe do latex
bool VerifyNeg(const char* result, int j) {
    return result[j + 1] == 'v' && result[j + 2] == 'e' && result[j + 3] == 'e';
}

// Função para verificar a sintaxe do latex
bool VerifyWedge(const char* result, int j) {
    return result[j + 1] == 'w' && result[j + 2] == 'e' && result[j + 3] == 'd' &&
        result[j + 4] == 'g' && result[j + 5] == 'e';
}

// Função para verificar a sintaxe do latex
bool VerifyRightArrow(const char* result, int j) {
    return result[j + 1] == 'r' && result[j + 2] == 'i' && result[j + 3] == 'g' &&
        result[j + 4] == 'h' && result[j + 5] == 't' && result[j + 6] == 'a' &&
        result[j + 7] == 'r' && result[j + 8] == 'r' && result[j + 9] == 'o' &&
        result[j + 10] == 'w';
}

// Função para verificar a sintaxe do latex
bool VerifyLeftRightArrow(const char* result, int j) {
    return result[j + 1] == 'l' && result[j + 2] == 'e' && result[j + 3] == 'f' &&
        result[j + 4] == 't' && result[j + 5] == 'r' && result[j + 6] == 'i' &&
        result[j + 7] == 'g' && result[j + 8] == 'h' && result[j + 9] == 't' &&
        result[j + 10] == 'a' && result[j + 11] == 'r' &&
        result[j + 12] == 'r' && result[j + 13] == 'o' &&
        result[j + 14] == 'w';
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