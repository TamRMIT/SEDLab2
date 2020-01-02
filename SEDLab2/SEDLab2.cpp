#include <iostream>
#include <string>

using namespace std;

string getA(string input) {
	if (isdigit(input[0]) == 0 && input[0] != '-')
		return "1";
	else {
		int length = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '*' || input[i] == '\0') {
				break;
			}
			else length++;
		}
		char* numberA = new char[length];
		for (int i = 0; i < length; i++) {
			numberA[i] = input[i];
		}
		numberA[length] = '\0';
		return numberA;
	}
}

string getB(string input) {
	int length = 0;
	int start;
	bool foundX = false;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {	// b before x, ex: a*sin(b*x)
			start = i + 1;
			foundX = true;
			for (int j = start; j < input.length(); j++) {
				if (input[j] == 'x') {
					return "1";
				}
				else if (input[j] == '*') {
					break;
				}
				else length++;
			}
			break;
		}
		else if (input[i] == 'x') {	// x before b, ex: a*x^(b)
			foundX = true;
			if (input[i + 1] == '\0') {
				return "1";
			}
		}
	}
	if (!foundX) {
		return "0";
	}
	char* numberB = new char[length];
	for (int i = 0; i < length; i++) {
		numberB[i] = input[start + i];
	}
	numberB[length] = '\0';
	return numberB;
}

string removeParenthesis(string input) {
	int length = 0;
	int start = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			start++;
		}
		else if (input[i] == ')') {
			break;
		}
		else {
			length++;
		}
	}
	char* newInput = new char[length];
	for (int i = 0; i < length; i++) {
		newInput[i] = input[i + start];
	}
	newInput[length] = '\0';
	return newInput;
}

string differentiatePower(string input) {
	int a = stoi(removeParenthesis(getA(input)));
	int b = stoi(removeParenthesis(getB(input)));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (b < 0) {
		return to_string(b * a) + "/(x^(" + to_string(1 - b) + "))";
	}
	else if (b == 1) {	// a*x
		return to_string(a);
	}
	else if (b == 2) {	// a*x^2
		return to_string(b * a) + "*x";
	}
	else {	// a*x^b
		return to_string(b * a) + "*x^(" + to_string(b - 1) + ")";
	}
}

string differentiateExponential(string input) {
	int a = stoi(removeParenthesis(getA(input)));
	int b = stoi(removeParenthesis(getB(input)));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (a == 1 && b == 1) {
		return "e^x";
	}
	else if (a != 1 && b == 1) {	// a*e^x
		return to_string(a) + "*e^x";
	}
	else {	// a*e^(b*x)
		return to_string(b * a) + "*e^((" + to_string(b) + ")*x)";
	}
}

string differentiateLogarithmic(string input) {
	int a = stoi(removeParenthesis(getA(input)));
	int b = stoi(removeParenthesis(getB(input)));
	if (b == 0) {
		return "Error";
	}
	else if (a == 0 && b != 0) {
		return "0";
	}
	else {
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == 'g' && input[i + 1] == '1') {	// log base 10
				return to_string(a) + "/(x*loge(10))";
			}
			else { // log base e
				return to_string(a) + "/x";
			}
		}
	}
}

string differentiateSin(string input) {
	int a = stoi(removeParenthesis(getA(input)));
	int b = stoi(removeParenthesis(getB(input)));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (a == 1 && b == 1) {
		return "cos(x)";
	}
	else if (a != 1 && b == 1) {
		return to_string(a) + "*cos(x)";
	}
	else {
		return to_string(b * a) + "*cos((" + to_string(b) + ")*x)";
	}
}

string differentiateCos(string input) {
	int a = stoi(removeParenthesis(getA(input)));
	int b = stoi(removeParenthesis(getB(input)));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (a == 1 && b == 1) {
		return "-sin(x)";
	}
	else if (a != 1 && b == 1) {
		return to_string(0 - a) + "*sin(x)";
	}
	else {
		return to_string(0 - (b * a)) + "*sin((" + to_string(b) + ")*x)";
	}
}

int main()
{
	cout << differentiatePower("x^(-24)") << endl;
	cout << differentiatePower("50*x^(16)") << endl;
	cout << differentiateExponential("25*e^((-12)*x)") << endl;
	cout << differentiateLogarithmic("-5*loge(12*x)") << endl;
	cout << differentiateSin("sin((-3)*x)") << endl;
	cout << differentiateCos("-12*cos(12*x)") << endl;
}


