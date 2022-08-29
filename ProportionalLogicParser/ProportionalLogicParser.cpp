// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

#include <iostream>
#include "ValidateStringParser.h"

//Funções usadas
FILE* OpenFile();
int lengthOfArray(const char* arr);
// Funções para analisar os galhos da arvore;
void CreateFormula(char* result, char* Formula);
char TransformLeavesInGrammar(const char* result, int j);
void AnalyzeExpressionSyntax(char* Formula, int sizeFormula, bool* flag);
void RemovePrepositionByFormula(char* Formula, int sizeFormula);
void RemoveUnaryFormulaByFormula(char* Formula, int sizeFormula);
void RemoveBinaryFormulaByFormula(char* Formula, int sizeFormula);
void OrganizeFormula(char* Formula, int sizeFormula);
bool isUnaryFormula(const char* Formula, int j);
bool isBinaryFormula(const char* Formula, int p);
bool isResult(const char* Formula, int sizeFormula);
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

	if (arq == NULL)
	{
		std::cout << "Problemas na abertura do arquivo" << '\n';
		return 0;
	}

	while (!feof(arq))
	{
		result = fgets(Linha, 100, arq);
		if (result) {
			CreateFormula(result, Formula);
			AnalyzeExpressionSyntax(Formula, sizeof(Formula), &flag);
		}
		printStringWithoutBreak(result);
		PrintResultFormula(flag);
	}
	fclose(arq);

}

FILE* OpenFile() { return fopen("arq1.txt", "rt"); }

int lengthOfArray(const char* arr)
{
	int size = 0;

	while (*arr) {
		size += 1;
		arr += 1;
	}

	return size;
}

void CreateFormula(char* result, char* Formula)
{
	int conter = 0;
	for (int j = 0; j < (lengthOfArray(result)); j++) {
		if (TransformLeavesInGrammar(result, j) != 0)
		{
			Formula[conter] = TransformLeavesInGrammar(result, j);
			conter++;
		}
	}
}

char TransformLeavesInGrammar(const char* result, int j)
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

void AnalyzeExpressionSyntax(char* Formula, int sizeFormula, bool* flag)
{
	bool running = true;
	while (running) {

		// Transformar C e P em R pois são formula
		RemovePrepositionByFormula(Formula, sizeFormula);

		// Ver se existe Formula Unaria
		RemoveUnaryFormulaByFormula(Formula, sizeFormula);

		// Ver se existe Formula Binaria
		RemoveBinaryFormulaByFormula(Formula, sizeFormula);

		if (CheckIfItIsFormula(Formula, sizeFormula))
		{
			*flag = true;
			running = false;
		}
		else
		{
			running = isResult(Formula, sizeof(Formula));
		}

	}
}
/*
			Gabarito das Letras:
			_____________________________
			|    A = Abre parênteses    |
			|    F = Fecha parênteses   |
			|    E = Espaço             |
			|    P = Preposição         |
			|    C = Constante          |
			|    U = Unário             |
			|    B = Binário            |
			|    R = Resultado          |
			_____________________________
*/
void RemovePrepositionByFormula(char* Formula, int sizeFormula)
{
	for (int k = 0; k < sizeFormula; k++) {
		if (Formula[k] == 'C' || Formula[k] == 'P') {
			Formula[k] = 'R';
		}
	}
}

void RemoveUnaryFormulaByFormula(char* Formula, int sizeFormula)
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

void RemoveBinaryFormulaByFormula(char* Formula, int sizeFormula)
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
	char tempFormula[100] = {};
	int conter;
	conter = 0;

	for (int k = 0; k < sizeFormula; k++) {
		if (Formula[k] == 'R' && Formula[k + 1] != 'R') {
			tempFormula[conter] = 'R';
			conter++;

		}
		else if (Formula[k] != 'R' && Formula[k + 1] == 'R') {
			tempFormula[conter] = Formula[k];
			conter++;

		}
		else if (Formula[k] != 'R' && Formula[k + 1] != 'R') {
			tempFormula[conter] = Formula[k];
			conter++;
		}
	}

	//Copia a nova formula;
	memcpy(Formula, tempFormula, sizeof tempFormula);

}

bool isUnaryFormula(const char* Formula, int j)
{
	return Formula[j] == 'A' && Formula[j + 1] == 'U' && Formula[j + 2] == 'E' && Formula[j + 3] == 'R' && Formula[j + 4] == 'E' && Formula[j + 5] == 'F';
}

bool isBinaryFormula(const char* Formula, int p)
{
	return Formula[p] == 'A' && Formula[p + 1] == 'B' && Formula[p + 2] == 'E' && Formula[p + 3] == 'R' && Formula[p + 4] == 'E'
		&& Formula[p + 5] == 'R' && Formula[p + 6] == 'E' && Formula[p + 7] == 'F';
}

bool isResult(const char* Formula, int sizeFormula)
{
	for (int i = 0; i < sizeof(Formula); i++)
	{
		if (Formula[i] == 'A')
		{
			if (!isBinaryFormula(Formula, i) && !isUnaryFormula(Formula, i))
			{
				return false;
			}
		}
	}

	return true;
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