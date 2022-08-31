// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

#include <iostream>
#include "ValidateStringParser.h"
#include "FormulaAnalyzer.h"

//Funções usadas
FILE* OpenFile(const char* nameFile);

int main() {
	// Usando para ler o arquivo.
	FILE* arq;
	char Linha[100];
	char* result;
	char listaDeArquivos[][100] = {"arq1.txt", "arq2.txt", "arq3.txt"};
	int numeroArquivos;
	int contador = 0;
	//Será nessa variavel que será manipulado a formula

	std::cout << "Quantos arquivos tem no projeto ? ";
	std::cin >> numeroArquivos;
	
	while (contador < numeroArquivos)
	{
		// Abertura do arquivo
		arq = OpenFile(listaDeArquivos[contador]);

		if (arq == NULL)
		{
			std::cout << "Problemas na abertura do arquivo" << '\n';
			return 0;
		}

		while (!feof(arq))
		{
			char Formula[100] = {};
			result = fgets(Linha, 100, arq);
			FormulaAnalyzer::RunsProportionalLogicParser(result, Formula, sizeof(Formula));
		}
		fclose(arq);
		contador++;
	}
	return 0;
}

FILE* OpenFile(const char* nameFile) 
{ 
	return fopen(nameFile, "rt");
}
