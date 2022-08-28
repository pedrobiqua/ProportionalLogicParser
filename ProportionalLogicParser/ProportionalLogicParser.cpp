// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

#include <iostream>
#include "ValidateStringParser.h"

//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
char CreateFormula(const char* result, int j, ValidateStringParser validate);
void RemovePrepositionByFormula(char* Formula, int sizeFormula);
void OrganizeFormula(char* Formula, int sizeFormula);
bool CheckIfItIsFormula(char* Formula, int sizeFormula);
void PrintResultFormula(bool flag);
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

                // Transformar C e P em R pois são formula
                RemovePrepositionByFormula(Formula, sizeof(Formula));
                
                //Criar uma função para isso
                // Ver se existe Formula Unaria
                for (int o = 0; o < sizeof(Formula); o++) {
                    if (Formula[o] == 'A' && Formula[o + 1] == 'U' && Formula[o + 2] == 'E' && Formula[o + 3] == 'R' && Formula[o + 4] == 'E' && Formula[o + 5] == 'F') {
                        Formula[o] = 'R';
                        Formula[o + 1] = 'R';
                        Formula[o + 2] = 'R';
                        Formula[o + 3] = 'R';
                        Formula[o + 4] = 'R';
                        Formula[o + 5] = 'R';

                    }
                }

                //Criar uma função para isso
                // Organiza o array
                OrganizeFormula(Formula, sizeof(Formula));

                //Criar uma função para isso
                // Ver se existe Formula Binaria
                for (int p = 0; p < sizeof(Formula); p++) {
                    if (Formula[p] == 'A' && Formula[p + 1] == 'B' && Formula[p + 2] == 'E' && Formula[p + 3] == 'R' && Formula[p + 4] == 'E'
                        && Formula[p + 5] == 'R' && Formula[p + 6] == 'E' && Formula[p + 7] == 'F') {

                        Formula[p] = 'R';
                        Formula[p + 1] = 'R';
                        Formula[p + 2] = 'R';
                        Formula[p + 3] = 'R';
                        Formula[p + 4] = 'R';
                        Formula[p + 5] = 'R';
                        Formula[p + 6] = 'R';
                        Formula[p + 7] = 'R';
                    }
                }

                if (CheckIfItIsFormula(Formula, sizeof(Formula)))
                {
                    flag = true;
                }
                
                running = false;
            }
        }
        std::cout << result << '\n';
    }
    fclose(arq);
    PrintResultFormula(flag);
    
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
    else if (validate.VerifyOpenParentheses(result, j)) {
        // std::cout << "Abertura de parenteses: " << result[j] << '\n';
        Formula = 'A';

    }
    else if (validate.VerifyCloseParentheses(result, j)) {
        // std::cout << "Fecho do parenteses: " << result[j] << '\n';
        Formula = 'F';

    }
    else if (validate.VerifyProposition(result, j)) {
        // std::cout << "Preposicao: " << result[j] << '\n';
        Formula = 'P';

    }
    else if (validate.VerifySpace(result, j)) {
        // std::cout << "Espaco" << '\n';
        Formula = 'E';

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

void RemovePrepositionByFormula(char* Formula, int sizeFormula)
{
    for (int k = 0; k < sizeFormula; k++) {
        if (Formula[k] == 'C' || Formula[k] == 'P') {
            Formula[k] = 'R';
        }
    }
}

void OrganizeFormula(char* Formula, int sizeFormula) 
{
    sizeFormula = 20;
    char ResultFormula[100] = {};
    int conter;
    conter = 0;

    for (int k = 0; k < sizeFormula; k++) {
        if (Formula[k] == 'R' && Formula[k + 1] != 'R') {
            ResultFormula[conter] = 'R';
            conter++;

        }
        else if (Formula[k] != 'R' && Formula[k + 1] == 'R') {
            ResultFormula[conter] = Formula[k];
            conter++;

        }
        else if (Formula[k] != 'R' && Formula[k + 1] != 'R') {
            ResultFormula[conter] = Formula[k];
            conter++;
        }
    }
    /* Como era antes no main
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
    */

    memcpy(Formula, ResultFormula, sizeof ResultFormula);

}

bool CheckIfItIsFormula(char* Formula, int sizeFormula)
{
    for (int r = 0; r < sizeFormula; r++) {
        if (Formula[r] != 'R' && Formula[r] != 0) {
            return false;
        }
    }
    return true;
}

void PrintResultFormula(bool flag)
{
    if (flag) {
        std::cout << "Sintaxe correta" << '\n';
    }
    else {
        std::cout << "Sintaxe errada" << '\n';
    }
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