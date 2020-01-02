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
	int mark;
	bool foundX = false;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == 'x') {
			foundX = true;
			if (input[i + 1] == '\0' || input[i + 1] == ')') {
				return "1";
			}
			else {
				mark = i;
				for (int j = i + 2; j < input.length(); j++) {
					if (input[j] == '\0' || input[j] == ')') {
						break;
					}
					else length++;
				}
			}
			break;
		}
	}
	if (!foundX) {
		return "0";
	}
	char* numberB = new char[length];
	for (int i = 0; i < length; i++) {
		numberB[i] = input[mark + i + 2];
	}
	numberB[length] = '\0';
	return numberB;
}

int convertStringToInteger(string n)
{
	int number = 0;
	int offset;
	if (n[0] == '-' || n[0] == '+')
		offset = 1;
	else offset = 0;
	for (int i = offset; i < n.length(); i++)
	{
		number += (n[i] - '0') * (int)pow(10, n.length() - 1 - i);
	}
	if (offset == 1 && n[0] == '-')
		number = -number;
	return number;
}

string differentiatePower(string input) {
	int a = convertStringToInteger(getA(input));
	int b = convertStringToInteger(getB(input));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (b < 0) {
		return to_string(b * a) + "/(x^" + to_string(1 - b) + ")";
	}
	else if (b == 1) {	// a*x
		return to_string(a);
	}
	else if (b == 2) {	// a*x^2
		return to_string(b * a) + "*x";
	}
	else {	// a*x^b
		return to_string(b * a) + "*x^" + to_string(b - 1);
	}
}

string differentiateExponential(string input) {
	int a = convertStringToInteger(getA(input));
	int b = convertStringToInteger(getB(input));
	if (a == 0 || b == 0) {
		return "0";
	}
	else if (a == 1 && b == 1) {
		return "e^x";
	}
	else if (a != 1 && b == 1) {	// a*e^x
		return to_string(a) + "*e^x";
	}
	else {	// a*e^(x*b)
		return to_string(b * a) + "*e^(x*" + to_string(b) + ")";
	}
}

string differentiateLogarithmic(string input) {
	int a = convertStringToInteger(getA(input));
	int b = convertStringToInteger(getB(input));
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
	int a = convertStringToInteger(getA(input));
	int b = convertStringToInteger(getB(input));
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
		return to_string(b * a) + "*cos(x*" + to_string(b) + ")";
	}
}

string differentiateCos(string input) {
	int a = convertStringToInteger(getA(input));
	int b = convertStringToInteger(getB(input));
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
		return to_string(0 - (b * a)) + "*sin(x*" + to_string(b) + ")";
	}
}

int main()
{
	cout << differentiatePower("50*x^16") << endl;
	cout << differentiatePower("50*x^-16") << endl;
	cout << differentiateExponential("25*e^(x*12)") << endl;
	cout << differentiateLogarithmic("-5*loge(x*2)") << endl;
	cout << differentiateSin("sin(x*3)") << endl;
	cout << differentiateCos("-12*cos(x*12)") << endl;
}


