// Pedro Bianchini de Quadros
// Enunciado: 
/*
Para  obter  os  pontos  relativos  a  este  trabalho,  você  deverá  fazer  um  programa,  usando  a
linguagem de programação que desejar, que seja capaz de validar expressões de lógica propisicional
escritas em latex e definir se são expressões gramaticalmente corretas. Você validará apenas a forma
da expressão (sintaxe).
A entrada será fornecida por um arquivo de textos que será carregado em linha de comando,
com a seguinte formatação:
1. Na primeira linha deste arquivo existe um número inteiro que informa quantas expressões
lógicas estão no arquivo.
2. Cada uma das linhas seguintes contém uma expressão lógica que deve ser validada.
A saída do seu programa será no terminal padrão do sistema e constituirá de uma linha de saída
para cada expressão lógica de entrada contendo ou a palavra valida ou a palavra inválida e nada mais.

Gramática:
	Formula=Constante|Proposicao|FormulaUnaria|FormulaBinaria.
	Constante="T"|"F".
	Proposicao=[a−z0−9]+
	FormulaUnaria=AbreParen OperadorUnario Formula FechaParen
	FormulaBinaria=AbreParen OperatorBinario Formula Formula FechaParen
	AbreParen="("
	FechaParen=")"
	OperatorUnario="¬"
	OperatorBinario="∨"|"∧"|"→"|"↔"

Cada  expressão  lógica  avaliada  pode  ter  qualquer  combinação  das  operações  de  negação,
conjunção, disjunção, implicação e bi-implicação sem limites na combiação de preposições e operações.
Os valores lógicos True e False estão representados na gramática e, como tal, podem ser usados em
qualquer expressão de entrada.
*/

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
