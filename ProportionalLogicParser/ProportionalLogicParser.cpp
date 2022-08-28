// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

#include <iostream>
#include "ValidateStringParser.h"

//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
// Funções para analisar os galhos da arvore;
char CreateFormula(const char* result, int j);
void RemovePrepositionByFormula(char* Formula, int sizeFormula);
void RemoveUnaryFormulaByFormula(char* Formula, int sizeFormula);
void RemoveBinaryFormulaByFormula(char* Formula, int sizeFormula);
void OrganizeFormula(char* Formula, int sizeFormula);
bool CheckIfItIsFormula(char* Formula, int sizeFormula);
void PrintResultFormula(bool flag);
void printStringWithoutBreak(const char* arr);

int main() {
    // Usando para ler o arquivo.
    FILE* arq;
    char Linha[100];
    char* result;

    bool running = true;
    bool flag = false;

    //Será nessa variavel que será manipulado a formula
    char Formula[100] = {};
    int conter = 0;

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
                    if (CreateFormula(result, j) != 0)
                    {
                        Formula[conter] = CreateFormula(result, j);
                        conter++;
                    }
                }

                // Transformar C e P em R pois são formula
                RemovePrepositionByFormula(Formula, sizeof(Formula));
                
                // Ver se existe Formula Unaria
                RemoveUnaryFormulaByFormula(Formula, sizeof(Formula));

                // Ver se existe Formula Binaria
                RemoveBinaryFormulaByFormula(Formula, sizeof(Formula));
                
                if (CheckIfItIsFormula(Formula, sizeof(Formula)))
                {
                    flag = true;
                }
                
                running = false;
            }
        }
        printStringWithoutBreak(result);
        PrintResultFormula(flag);
    }
    fclose(arq);
    
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

char CreateFormula(const char* result, int j)
{
    char Formula;
    Formula = 0;
    if (ValidateStringParser::VerifyConstant(result, j)) {
        Formula = 'C';
    }
    else if (ValidateStringParser::VerifyOpenParentheses(result, j)) {
        Formula = 'A';
    }
    else if (ValidateStringParser::VerifyCloseParentheses(result, j)) {
        Formula = 'F';
    }
    else if (ValidateStringParser::VerifyProposition(result, j)) {
        Formula = 'P';
    }
    else if (ValidateStringParser::VerifySpace(result, j)) {
        Formula = 'E';
    }
    else if (ValidateStringParser::VerifyLatex(result, j) == 3 || ValidateStringParser::VerifyLatex(result, j) == 5 || ValidateStringParser::VerifyLatex(result, j) == 10 || ValidateStringParser::VerifyLatex(result, j) == 14) {

        if (ValidateStringParser::VerifyLatex(result, j) != 3) {
            Formula = 'B';
        }
        else {
            Formula = 'U';
        }
        j = j + ValidateStringParser::VerifyLatex(result, j) + 1;
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

void RemoveUnaryFormulaByFormula(char *Formula, int sizeFormula) 
{
    for (int o = 0; o < sizeFormula; o++) {
        if (Formula[o] == 'A' && Formula[o + 1] == 'U' && Formula[o + 2] == 'E' && Formula[o + 3] == 'R' && Formula[o + 4] == 'E' && Formula[o + 5] == 'F') {
            Formula[o] = 'R';
            Formula[o + 1] = 'R';
            Formula[o + 2] = 'R';
            Formula[o + 3] = 'R';
            Formula[o + 4] = 'R';
            Formula[o + 5] = 'R';

        }
    }
    // Organiza o array
    OrganizeFormula(Formula, sizeof(Formula));
}

void RemoveBinaryFormulaByFormula(char *Formula, int sizeFormula)
{
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
    // Organiza o array
    OrganizeFormula(Formula, sizeof(Formula));
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

    //Copia a nova formula;
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

void printStringWithoutBreak(const char* arr)
{
    for (size_t i = 0; i < lengthOfArray(arr); i++)
    {
        if (arr[i] != '\n')
        {
            std::cout << arr[i];
        }
    }
    std::cout << ": ";
}