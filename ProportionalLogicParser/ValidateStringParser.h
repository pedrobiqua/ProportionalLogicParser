#pragma once
class ValidateStringParser
{
public:
	static bool VerifyConstant(const char* result, int j);
	static bool VerifyProposition(const char* result, int j);
	static bool VerifyOpenParentheses(const char* result, int j);
	static bool VerifyCloseParentheses(const char* result, int j);
	static bool VerifySpace(const char* result, int j);
	static int VerifyLatex(const char* result, int j);
	
private:
	static const char* checkOperator(const char* result, int j);
	static bool VerifyNeg(const char* result, int j);
	static bool VerifyWedge(const char* result, int j);
	static bool VerifyRightArrow(const char* result, int j);
	static bool VerifyLeftRightArrow(const char* result, int j);
};

