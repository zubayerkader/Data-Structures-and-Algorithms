#include <iostream>
#include <string>
using namespace std;

class var
{
private:
    string datastr;
    int dataint;
    
    string sign;
    
public:
    var() {};
    var(const var&);
    var (const int &x);
    var (const string &x);
    var& operator= (const var &x);
    var& operator= (const int&);
    var& operator= (const string&);
    friend ostream& operator<< (ostream &out, const var &x);
    int operator+ (const int&);
};
