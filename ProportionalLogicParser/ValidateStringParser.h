#pragma once
class ValidateStringParser
{
public:
	bool VerifyConstant(const char* result, int j);
	bool VerifyProposition(const char* result, int j);
	bool VerifyOpenParentheses(const char* result, int j);
	bool VerifyCloseParentheses(const char* result, int j);
	bool VerifySpace(const char* result, int j);
	int VerifyLatex(const char* result, int j);
	
private:
	const char* checkOperator(const char* result, int j);
	bool VerifyNeg(const char* result, int j);
	bool VerifyWedge(const char* result, int j);
	bool VerifyRightArrow(const char* result, int j);
	bool VerifyLeftRightArrow(const char* result, int j);
};

