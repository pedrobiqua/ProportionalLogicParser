// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

#include <iostream>
#include "ValidateStringParser.h"
#include "FormulaAnalyzer.h"

//Funções usadas
FILE* OpenFile();

int main() {
	// Usando para ler o arquivo.
	FILE* arq;
	char Linha[100];
	char* result;
	//Será nessa variavel que será manipulado a formula
	char Formula[100] = {};
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
		FormulaAnalyzer::RunsProportionalLogicParser(result, Formula, sizeof(Formula));
	}
	fclose(arq);
	return 0;
}

FILE* OpenFile() { return fopen("arq1.txt", "rt"); }
