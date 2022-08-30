#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FormulaAnalyzer.h"
#include "ValidateStringParser.h"

void FormulaAnalyzer:: RunsProportionalLogicParser(char* result, char* Formula, int sizeFormula)
{
	bool flag = false;
	if (result) {
		CreateFormula(result, Formula);
		AnalyzeExpressionSyntax(Formula, sizeFormula, &flag);
	}
	printStringWithoutBreak(result);
	PrintResultFormula(flag);
}

void FormulaAnalyzer::CreateFormula(char* result, char* Formula)
{
	int conter = 0;
	for (int j = 0; j < (lengthOfArray(result)); j++) {
		char tempLeaveValue = TransformLeavesInGrammar(result, j);
		int latexValue = ValidateStringParser::VerifyLatex(result, j);

		if (tempLeaveValue != 0)
		{
			if (latexValue == 3 || latexValue == 4 || latexValue == 5 || latexValue == 10 || latexValue == 14)
			{
				Formula[conter] = tempLeaveValue;
				conter++;
				if (latexValue == 4)
				{
					j = j + latexValue - 1;
				}
				else {
					j = j + latexValue;
				}
			}
			else 
			{
				Formula[conter] = tempLeaveValue;
				conter++;
			}
			
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

char FormulaAnalyzer::TransformLeavesInGrammar(const char* result, int j)
{
	char Formula;
	Formula = 0;

	if (ValidateStringParser::VerifyConstant(result, j)) {
		return Formula = 'C';
	}
	else if (ValidateStringParser::VerifyOpenParentheses(result, j)) {
		return Formula = 'A';
	}
	else if (ValidateStringParser::VerifyCloseParentheses(result, j)) {
		return Formula = 'F';
	}
	else if (ValidateStringParser::VerifySpace(result, j)) {
		return Formula = 'E';
	}
	else if (ValidateStringParser::VerifyLatex(result, j) == 3 || ValidateStringParser::VerifyLatex(result, j) == 5 || ValidateStringParser::VerifyLatex(result, j) == 10 || ValidateStringParser::VerifyLatex(result, j) == 14 || ValidateStringParser::VerifyLatex(result, j) == 4) {

		if (ValidateStringParser::VerifyLatex(result, j) != 3) {
			return Formula = 'B';
		}
		else {
			return Formula = 'U';
		}
	}
	else if (ValidateStringParser::VerifyProposition(result, j)) {
		return Formula = 'P';
	}

	return Formula;
}

void FormulaAnalyzer::AnalyzeExpressionSyntax(char* Formula, int sizeFormula, bool* flag)
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

void FormulaAnalyzer::RemovePrepositionByFormula(char* Formula, int sizeFormula)
{
	for (int k = 0; k < sizeFormula; k++) {
		if (Formula[k] == 'C' || Formula[k] == 'P') {
			Formula[k] = 'R';
		}
	}

	OrganizeFormula(Formula, sizeFormula);
}

void FormulaAnalyzer::RemoveUnaryFormulaByFormula(char* Formula, int sizeFormula)
{
	sizeFormula = 20;
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
	OrganizeFormula(Formula, sizeFormula);
}

void FormulaAnalyzer::RemoveBinaryFormulaByFormula(char* Formula, int sizeFormula)
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
	OrganizeFormula(Formula, sizeFormula);
}

void FormulaAnalyzer::OrganizeFormula(char* Formula, int sizeFormula)
{
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

bool FormulaAnalyzer::isUnaryFormula(const char* Formula, int j)
{
	return Formula[j] == 'A' && Formula[j + 1] == 'U' && Formula[j + 2] == 'E' && Formula[j + 3] == 'R' && Formula[j + 4] == 'E' && Formula[j + 5] == 'F';
}

bool FormulaAnalyzer::isBinaryFormula(const char* Formula, int p)
{
	return Formula[p] == 'A' && Formula[p + 1] == 'B' && Formula[p + 2] == 'E' && Formula[p + 3] == 'R' && Formula[p + 4] == 'E'
		&& Formula[p + 5] == 'R' && Formula[p + 6] == 'E' && Formula[p + 7] == 'F';
}

bool FormulaAnalyzer::isResult(const char* Formula, int sizeFormula)
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

bool FormulaAnalyzer::CheckIfItIsFormula(char* Formula, int sizeFormula)
{
	for (int r = 0; r < sizeFormula; r++) {
		if (Formula[r] != 'R' && Formula[r] != 0) {
			return false;
		}
	}
	return true;
}

void FormulaAnalyzer::PrintResultFormula(bool flag)
{
	if (flag) {
		std::cout << "Sintaxe correta" << '\n';
	}
	else {
		std::cout << "Sintaxe errada" << '\n';
	}
}

void FormulaAnalyzer::printStringWithoutBreak(const char* arr)
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

int FormulaAnalyzer::lengthOfArray(const char* arr)
{
	int size = 0;

	while (*arr) {
		size += 1;
		arr += 1;
	}

	return size;
}
