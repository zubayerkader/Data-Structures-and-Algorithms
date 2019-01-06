#include "postfixUtility.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	string exp = argv[1];
	//cout << exp << endl;
	string pexp = getPostfix(exp);
	cout << pexp << endl;
	float f = evaluatePostfix(pexp);
	cout << f << endl;
}

