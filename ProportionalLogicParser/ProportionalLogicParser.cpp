// Pedro Bianchini de Quadros
// Enunciado: Ctrl + V here

#include <iostream>
#include "ValidateStringParser.h"

//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
char CreateFormula(const char* result, int j, ValidateStringParser validate);
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
    bool flag = true;
    char Formula[100] = {};
    char ResultFormula[100] = {};
    int conter = 0;
    int newconter = 0;
    int u = 0;

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
            while (running) {
                // Em casa mudar a ordem e criar uma função
                for (int j = 0; j < (lengthOfArray(result)); j++) {
                    if (CreateFormula(result, j, validate) != 0)
                    {
                        Formula[conter] = CreateFormula(result, j, validate);
                        conter++;
                    }
                }

                //Criar uma função para isso
                // Transformar C e P em R pois são formula
                for (int k = 0; k < sizeof(Formula); k++) {
                    if (Formula[k] == 'C' || Formula[k] == 'P') {
                        Formula[k] = 'R';
                    }
                }

                //Criar uma função para isso
                // Ver se existe Formula Unaria
                for (int o = 0; o < sizeof(Formula); o++) {
                    if (Formula[o] == 'A' && Formula[o + 1] == 'U' &&
                        Formula[o + 2] == 'R' && Formula[o + 3] == 'F') {
                        Formula[o] = 'R';
                        Formula[o + 1] = 'R';
                        Formula[o + 2] = 'R';
                        Formula[o + 3] = 'R';
                    }
                }

                //Criar uma função para isso
                // Organiza o array
                for (int k = 0; k < sizeof(Formula); k++) {
                    if (Formula[k] == 'R' && Formula[k + 1] != 'R') {
                        ResultFormula[newconter] = 'R';
                        newconter++;

                    }
                    else if (Formula[k] != 'R' && Formula[k + 1] == 'R') {
                        ResultFormula[newconter] = Formula[k];
                        newconter++;

                    }
                    else if (Formula[k] != 'R' && Formula[k + 1] != 'R') {
                        ResultFormula[newconter] = Formula[k];
                        newconter++;
                    }
                }

                //Criar uma função para isso
                // Ver se existe Formula Binaria
                for (int p = 0; p < sizeof(ResultFormula); p++) {
                    if (ResultFormula[p] == 'A' && ResultFormula[p + 1] == 'R' && ResultFormula[p + 2] == 'B' && ResultFormula[p + 3] == 'R' && ResultFormula[p + 4] == 'F') {
                        ResultFormula[p] = 'R';
                        ResultFormula[p + 1] = 'R';
                        ResultFormula[p + 2] = 'R';
                        ResultFormula[p + 3] = 'R';
                        ResultFormula[p + 4] = 'R';
                    }
                }

                ////Criar uma função para isso.
                for (int r = 0; r < sizeof(ResultFormula); r++) {
                    if (ResultFormula[r] != 'R' && ResultFormula[r] != 0) {
                        flag = false;
                    }
                }
                running = false;
            }
        }
        std::cout << result << '\n';
    }
    fclose(arq);

    if (flag) {
        std::cout << "Sintaxe correta" << '\n';
    }
    else {
        std::cout << "Sintaxe errada" << '\n';
    }
    

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

char CreateFormula(const char* result, int j, ValidateStringParser validate)
{
    char Formula;
    Formula = 0;
    if (validate.VerifyConstant(result, j)) {
        // std::cout << "Constante: " << result[j] << '\n';
        Formula = 'C';

    }
    else if (validate.VerifyProposition(result, j)) {
        // std::cout << "Preposicao: " << result[j] << '\n';
        Formula = 'P';

    }
    else if (validate.VerifyOpenParentheses(result, j)) {
        // std::cout << "Abertura de parenteses: " << result[j] << '\n';
        Formula = 'A';

    }
    else if (validate.VerifyCloseParentheses(result, j)) {
        // std::cout << "Fecho do parenteses: " << result[j] << '\n';
        Formula = 'F';

    }
    else if (validate.VerifySpace(result, j)) {
        // std::cout << "Espaco" << '\n';

    }
    else if (validate.VerifyLatex(result, j) == 3 || validate.VerifyLatex(result, j) == 5 || validate.VerifyLatex(result, j) == 10 || validate.VerifyLatex(result, j) == 14) {
        // std::cout << "Latex comeca no barra: ";
        for (int l = 0; l <= validate.VerifyLatex(result, j); l++) {
            //std::cout << result[j + l];
        }
        if (validate.VerifyLatex(result, j) != 3) {
            Formula = 'B';

        }
        else {
            Formula = 'U';

        }
        j = j + validate.VerifyLatex(result, j) + 1;
        //std::cout << '\n';

    }

    return Formula;
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