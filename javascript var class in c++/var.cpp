#include "var.h"

var::var (const int &x)
{
    this->dataint = x;
    this->sign = "int";
}

var::var (const string &x)
{
    this->datastr = x;
    this->sign = "str";
}

var::var(const var &x)
{
    if (x.sign == "str")
    {
        this->datastr = x.datastr;
        this->sign = "str";
    }
    else if (x.sign == "int")
    {
        this->dataint= x.dataint;
        this->sign = "int";
    }
}

var& var::operator= (const var &x)
{
    if (this == &x)
        return *this;
    else
    {
        if (x.sign == "str")
        {
            this->datastr = x.datastr;
            this->sign = "str";
        }
        else if (x.sign == "int")
        {
            this->dataint= x.dataint;
            this->sign = "int";
        }
        return *this;
    }
}

var& var::operator= (const int &x)
{
    this->sign = "int";
    this->dataint = x;
    return *this;
}

var& var::operator= (const string &x)
{
    this->sign = "str";
    this->datastr = x;
    return *this;
}

ostream& operator<< (ostream &out, const var &x)
{
    if (x.sign == "str")
        out << x.datastr;
    else if (x.sign == "int")
        out << x.dataint;
    return out;
}

int var::operator+ (const int &x)
{
    return (this->dataint + x);
}
