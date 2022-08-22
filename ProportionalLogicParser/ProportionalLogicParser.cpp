// Pedro Bianchini de Quadros
// Enunciado: Ctrl + V here

#include <iostream>
#include "ValidateStringParser.h"

//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
/*
bool VerifyConstant(const char* result, int j);
bool VerifyProposition(const char* result, int j);
bool VerifyOpenParentheses(const char* result, int j);
bool VerifyCloseParentheses(const char* result, int j);
int VerifyLatex(const char* result, int j);
const char* checkOperator(const char* result, int j);
bool VerifyNeg(const char* result, int j);
bool VerifyWedge(const char* result, int j);
bool VerifyRightArrow(const char* result, int j);
bool VerifyLeftRightArrow(const char* result, int j);
*/

int main() {
    // Usando para ler o arquivo.
    FILE* arq;
    char Linha[100];
    char* result;
    bool running = true;

    ValidateStringParser validate;

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
            //exemplo de escrita (p^d)
            while (running)
            {
                //Primeiro veificar as folhas
                //  Constante = "T" | "F"
                //  Proposicao=[a−z0−9]+
                //  AbreParen="(" 
                //  FechaParen = ")"
                //  OperatorUnario = "¬"
                //  OperatorBinario = "∨" | "∧" | "→" | "↔"
                for (int j = 0; j < (lengthOfArray(result)); j++) {
                    if (validate.VerifyConstant(result, j))
                    {
                        std::cout << "Constante: " << result[j] << '\n';
                    }
                    else if (validate.VerifyProposition(result, j))
                    {
                        std::cout << "Preposicao: " << result[j] << '\n';
                    }
                    else if (validate.VerifyOpenParentheses(result, j))
                    {
                        std::cout << "Abertura de parenteses: " << result[j] << '\n';
                    }
                    else if (validate.VerifyCloseParentheses(result, j))
                    {
                        std::cout << "Fecho do parenteses: " << result[j] << '\n';
                    }
                    else if (validate.VerifySpace(result, j))
                    {
                        std::cout << "Espaco" << '\n';
                    }

                    else if (validate.VerifyLatex(result, j) == 3 || validate.VerifyLatex(result, j) == 5 || validate.VerifyLatex(result, j) == 10 || validate.VerifyLatex(result, j) == 14)
                    {
                        std::cout << "Latex comeca no barra: " << result[j] << '\n';
                        j = j + validate.VerifyLatex(result, j);
                    }
                    else if (validate.VerifyLatex(result, j) == 0)
                    {
                        std::cout << "Sintaxe errada do latex na linha: " << result << '\n';
                        break;
                    }
                }
                running = false;
            }
        }
    }
    fclose(arq);

    // Todo working
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

/*
bool VerifyConstant(const char* result, int j) {
    return result[j] == 'T' || result[j] == 'F';
}

bool VerifyProposition(const char* result, int j)
{
    return result[j + 1] == ' ' && result[j - 1] == ' ';
}

bool VerifyOpenParentheses(const char* result, int j)
{
    return result[j] == '(';
}

bool VerifyCloseParentheses(const char* result, int j)
{
    return result[j] == ')';
}

int VerifyLatex(const char* result, int j) {
    if (result[j] == '\\') {

        if (checkOperator(result, j) == "\\neg")
        {
            return 3;
        } 
        else if (checkOperator(result, j) == "\\wedge")
        {
            return 5;
        }
        else if (checkOperator(result, j) == "\\rightarrow")
        {
            return 10;
        }
        else if (checkOperator(result, j) == "\\leftrightarrow")
        {
            return 14;
        }
    }
    return 0;
}

// Verifica os operadores
const char* checkOperator(const char* result, int j) {
    const char* nameOperator;
    if (VerifyNeg(result, j)) {
        nameOperator = "\\neg";
        return "\\neg";

    }
    else if (VerifyWedge(result, j)) {
        nameOperator = "\\wedge";
        return "\\wedge";

    }
    else if (VerifyRightArrow(result, j)) {
        nameOperator = "\\rightarrow";
        return "\\rightarrow";

    }
    else if (VerifyLeftRightArrow(result, j)) {
        nameOperator = "\\leftrightarrow";
        return "\\leftrightarrow";

    }
    return 0;
}

// Função para verificar a sintaxe do latex
bool VerifyNeg(const char* result, int j) {
    return result[j + 1] == 'n' && result[j + 2] == 'e' && result[j + 3] == 'g';
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
*/

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