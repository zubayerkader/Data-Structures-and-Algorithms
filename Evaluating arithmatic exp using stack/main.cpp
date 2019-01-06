#include "postfixUtility.h"

int main (int argc, char** argv)
{
    string pexp = getPostfix(argv[1]);
    float result = evaluatePostfix(pexp);
    cout << result << endl;
    
    //cout << evaluatePostfix("8 12-4 20*+14 12-/7+") << endl;
    //cout << evaluatePostfix("5 222+3 4*+2 3+5 3-**") << endl;
    
//    cout << getPostfix(  "(5+2+3*4)*((2+3)*(5-3))"  ) << endl;
//    cout << getPostfix(  "((8-12) + 4 * 20) / (14 - 12) + 7"  ) << endl;
//    cout << getPostfix(  "12 + 3 - 6 + 8"  ) << endl;
//    cout << getPostfix(  "5 * 2 / 4 * 3"  ) << endl;
//    cout << getPostfix(  "( 12 + 3 ) - (6 + 8)"  ) << endl;
    
	return 0;
}

