// Pedro Bianchini de Quadros
// Enunciado: Ctrl C + V

//OBS: Professor critique o meu código, para eu poder evoluir no c++, independente da nota!

#include <iostream>
#include "FormulaAnalyzer.h"

//Funções usadas
FILE* OpenFile(const char* nameFile);

int main() {
	// Usando para ler o arquivo.
	FILE* arq;
	char Linha[100];
	char* result{};
	char listaDeArquivos[][100] = {"arq1.txt", "arq2.txt", "arq3.txt"};
	int numeroArquivos;
	int contador = 0;
	//Será nessa variavel que será manipulado a formula

	numeroArquivos = 3;
	//Se quiser usar o input da tela somente descomente as linhas 24 e 25
	//std::cout << "Quantos arquivos tem no projeto ? ";
	//std::cin >> numeroArquivos;
	
	while (contador < numeroArquivos)
	{
		// Abertura do arquivo
		arq = OpenFile(listaDeArquivos[contador]);

		if (arq == NULL)
		{
			std::cout << "Problemas na abertura do arquivo" << '\n';
			return 0;
		}
		
		//Tive q colocar essa variavel pois não deu tempo de criar a implementação de ler um certo número de linhas do arquivo
		bool ignoreNumber = false;

		while (!feof(arq))
		{
			result = fgets(Linha, 100, arq);
			if (ignoreNumber)
			{
				char Formula[100] = {};
				FormulaAnalyzer::RunsProportionalLogicParser(result, Formula, sizeof(Formula));
			}
			ignoreNumber = true;
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
