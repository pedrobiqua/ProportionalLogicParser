#include "ValidateStringParser.h"

//Funções para verificar as folhas
bool ValidateStringParser::VerifyConstant(const char* result, int j) {
    return result[j] == 'T' || result[j] == 'F';
}

//Arrumar as preposições
bool ValidateStringParser::VerifyProposition(const char* result, int j)
{
    return result[j + 1] == ' ' && result[j - 1] == ' ';
}

bool ValidateStringParser::VerifyOpenParentheses(const char* result, int j)
{
    return result[j] == '(';
}

bool ValidateStringParser::VerifyCloseParentheses(const char* result, int j)
{
    return result[j] == ')';
}

bool ValidateStringParser::VerifySpace(const char* result, int j)
{
    return result[j] == ' ';
}

int ValidateStringParser::VerifyLatex(const char* result, int j) {
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
const char* ValidateStringParser::checkOperator(const char* result, int j) {
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
bool ValidateStringParser::VerifyNeg(const char* result, int j) {
    return result[j + 1] == 'n' && result[j + 2] == 'e' && result[j + 3] == 'g';
}

// Função para verificar a sintaxe do latex
bool ValidateStringParser::VerifyWedge(const char* result, int j) {
    return result[j + 1] == 'w' && result[j + 2] == 'e' && result[j + 3] == 'd' &&
        result[j + 4] == 'g' && result[j + 5] == 'e';
}

// Função para verificar a sintaxe do latex
bool ValidateStringParser::VerifyRightArrow(const char* result, int j) {
    return result[j + 1] == 'r' && result[j + 2] == 'i' && result[j + 3] == 'g' &&
        result[j + 4] == 'h' && result[j + 5] == 't' && result[j + 6] == 'a' &&
        result[j + 7] == 'r' && result[j + 8] == 'r' && result[j + 9] == 'o' &&
        result[j + 10] == 'w';
}

// Função para verificar a sintaxe do latex
bool ValidateStringParser::VerifyLeftRightArrow(const char* result, int j) {
    return result[j + 1] == 'l' && result[j + 2] == 'e' && result[j + 3] == 'f' &&
        result[j + 4] == 't' && result[j + 5] == 'r' && result[j + 6] == 'i' &&
        result[j + 7] == 'g' && result[j + 8] == 'h' && result[j + 9] == 't' &&
        result[j + 10] == 'a' && result[j + 11] == 'r' &&
        result[j + 12] == 'r' && result[j + 13] == 'o' &&
        result[j + 14] == 'w';
}