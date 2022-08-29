#pragma once
class FormulaAnalyzer
{
public:
	static void RunsProportionalLogicParser(char* result, char* Formula, int sizeFormula);
private:
	static void CreateFormula(char* result, char* Formula);
	static char TransformLeavesInGrammar(const char* result, int j);
	static void AnalyzeExpressionSyntax(char* Formula, int sizeFormula, bool* flag);
	static void RemovePrepositionByFormula(char* Formula, int sizeFormula);
	static void RemoveUnaryFormulaByFormula(char* Formula, int sizeFormula);
	static void RemoveBinaryFormulaByFormula(char* Formula, int sizeFormula);
	static void OrganizeFormula(char* Formula, int sizeFormula);
	static bool isUnaryFormula(const char* Formula, int j);
	static bool isBinaryFormula(const char* Formula, int p);
	static bool isResult(const char* Formula, int sizeFormula);
	static bool CheckIfItIsFormula(char* Formula, int sizeFormula);
	static void PrintResultFormula(bool flag);
	static void printStringWithoutBreak(const char* arr);
	static int lengthOfArray(const char* arr);
};

