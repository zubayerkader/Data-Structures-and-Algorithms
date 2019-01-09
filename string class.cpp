//
//  main.cpp
//  Assignment 1
//
//  Created by Kazi Zubayer Quader on 6/15/17.
//  Copyright © 2017 Kazi Zubayer Quader. All rights reserved.
//
//#include "stdafx.h"
#include <iostream>
using namespace std;

class CMPT135_String
{
private:
    int length;//This will be the length of the string without counting the NULL character
    char *buffer; //This buffer will actually have length + 1 characters including the NULL char
public:
    //Very useful Static member function
    static int getC_StringLength(const char *charArray);
    
    //Constructors
    CMPT135_String();
    CMPT135_String(const char &c);
    CMPT135_String(const char *buffer);//*buffer is a null terminated char array
    CMPT135_String(const CMPT135_String &s);
    
    //Destructor
    ~CMPT135_String();
    
    //Assignment operators
    CMPT135_String& operator = (const CMPT135_String &s);
    CMPT135_String& operator = (const char &c);
    CMPT135_String& operator = (const char* buffer); //*buffer is a null terminated char array

    //Getter member functions
    int getLength() const;
    char& operator[](const int &index) const;

    //Setter member functions
    void append(const CMPT135_String &s);
    void append(const char &c);
    void append(const char *buffer);
    void setBuffer(const char *buffer);
    
    //Other member functions
    int findCharIndex(const char &c) const;
    int reverseFindCharIndex(const char &c) const;
    CMPT135_String getSubString(const int &startIndex, const int &length) const;
    bool isSubString(const CMPT135_String &s) const;
    bool isSubString(const char *buffer) const;
    void reverse();
    void removeChar(const char &c);
    void replace(const char &c1, const char &c2);
    
    //Operator member functions
    CMPT135_String operator + (const CMPT135_String &s) const;
    CMPT135_String operator + (const char *buffer) const; //*buffer is a null terminated char array
    CMPT135_String operator + (const char &c) const;
    void operator += (const CMPT135_String &s);
    void operator += (const char &c);
    void operator += (const char* buffer); //*buffer is a null char terminated char array
    bool operator == (const CMPT135_String &s) const;
    bool operator == (const char *buffer) const; //*buffer is a null char terminated char
    bool operator != (const CMPT135_String &s) const;
    bool operator != (const char *buffer) const; //*buffer is a null char terminated char
    bool operator < (const CMPT135_String &s) const;
    bool operator < (const char *buffer) const; //*buffer is a null char terminated char array
    bool operator > (const CMPT135_String &s) const;
    bool operator > (const char *buffer) const; //*buffer is a null char terminated char array
    bool operator >= (const CMPT135_String &s) const;
    bool operator >= (const char *buffer) const; //*buffer is a null char terminated char array
    bool operator <= (const CMPT135_String &s) const;
    bool operator <= (const char *buffer) const; //*buffer is a null char terminated char array
    
    //Friend Functions (for operators)
    friend CMPT135_String operator + (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend CMPT135_String operator + (const char &c, const CMPT135_String &s);
    friend bool operator == (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend bool operator != (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend bool operator < (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend bool operator > (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend bool operator <= (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend bool operator >= (const char *buffer, const CMPT135_String &s); //*buffer is a null terminated char array
    friend ostream& operator << (ostream &outputStream, const CMPT135_String &s);
    friend istream& operator >> (istream &inputStream, CMPT135_String &s);
};

//Very useful Static member function
int CMPT135_String::getC_StringLength(const char *charArray)
{
    //This function returns the length of the charArray
    //It does not include the null char at the end of charArray
    int len = 0;
    for (int i = 0; charArray[i] != '\0'; i++)
        len++;
    return len;
}

//Constructors
CMPT135_String::CMPT135_String()
{
    this->length=0;
    this->buffer = new char [1];
    this->buffer[0] = '\0';
}
CMPT135_String::CMPT135_String(const char &c)
{
    this->length=1;
    this->buffer = new char [2];
    this->buffer[0] = c;
    this->buffer[1] = '\0';
}
CMPT135_String::CMPT135_String(const char *buffer) //*buffer is a null terminated char array
{
    this->length = CMPT135_String::getC_StringLength(buffer);
    this->buffer = new char[this->getLength() + 1];
    for (int i = 0; i < this->getLength(); i++)
         this->buffer[i] = buffer[i];
    this->buffer[this->getLength()] = '\0';
}
CMPT135_String::CMPT135_String(const CMPT135_String &s)
{
    this->length=getC_StringLength(s.buffer);
    if (this->length>0)
    {
        this->buffer=new char [this->length+1];
        for (int i=0; i<this->length; i++)
            this->buffer[i]=s.buffer[i];
        this->buffer[this->length]='\0';
    }
}

//Destructor
CMPT135_String::~CMPT135_String()
{
    if (this->length>0)
    {
        delete [] this->buffer;
        this->length=0;
        this->buffer = new char [1];
        this->buffer[0] = '\0';
    }
}

//Assignment operators
CMPT135_String& CMPT135_String::operator = (const CMPT135_String &s)
{
    if (this==&s)
        return *this;
    this->length=s.length;
    delete [] this->buffer;
    this->buffer = new char [this->length+1];
    for (int i=0; i<this->length; i++)
        this->buffer[i]=s.buffer[i];
    this->buffer[this->length]='\0';
    return *this;
}
CMPT135_String& CMPT135_String::operator = (const char &c)
{
    delete [] this->buffer;
    this->length=1;
    this->buffer = new char [2];
    this->buffer[0] = c;
    this->buffer[1] = '\0';
    return *this;
}
CMPT135_String& CMPT135_String::operator = (const char* buffer) //*buffer is a null terminated char array
{
    this->length = CMPT135_String::getC_StringLength(buffer);
    this->buffer = new char[this->getLength() + 1];
    for (int i = 0; i < this->getLength(); i++)
        this->buffer[i] = buffer[i];
    this->buffer[this->getLength()] = '\0';
    return *this;
}

//Getter member functions
int CMPT135_String::getLength() const
{
    return this->length;
}
char& CMPT135_String::operator[](const int &index) const
{
    if (index>=0 && index<=this->length)
        return this->buffer[index];
    else
    {
        cout << "ERROR! Index out of bound." << endl;
        system("exit");
        return this->buffer[0];
    }
}

//Setter member functions
void CMPT135_String::append(const CMPT135_String &s)
{
    int size=this->getLength()+s.getLength()+1;
    char *ch = new char [size];
    for (int i=0; i<this->getLength(); i++)
        ch[i]=this->buffer[i];
    int x=0;
    for (int i=this->getLength(); i<size; i++)
    {
        ch[i]=s[x];
        x++;
    }
    //ch[size]='\0';
    delete [] this->buffer;
    this->buffer=ch;
    this->length=size-1;
}
void CMPT135_String::append(const char &c)
{
    char *ch = new char [this->getLength()+2];
    for (int i=0; i<this->getLength(); i++)
        ch[i]=this->buffer[i];
    ch[this->getLength()]=c;
    ch[this->getLength()+1]='\0';
    delete [] this->buffer;
    this->buffer=ch;
    this->length=this->getLength()+1;
}
void CMPT135_String::append(const char *buffer)
{
    CMPT135_String obj(buffer);
    this->append(obj);
}
void CMPT135_String::setBuffer(const char *buffer)
{
    int s=getC_StringLength(buffer);
    char *ch = new char [s+1];
    for (int i=0; i<s; i++)
        ch[i]=buffer[i];
    ch[s]='\0';
    delete [] this->buffer;
    this->buffer=ch;
    this->length=s;
}

//Other member functions
int CMPT135_String::findCharIndex(const char &c) const
{
    for (int i=0; i<this->getLength(); i++)
    {
        if (this->buffer[i]==c)
            return i;
    }
    return -1;
}
int CMPT135_String::reverseFindCharIndex(const char &c) const
{
    for (int i=this->getLength()-1; i>=0; i--)
    {
        if (this->buffer[i]==c)
            return i;
    }
    return -1;
}
CMPT135_String CMPT135_String::getSubString(const int &startIndex, const int &length) const
{
    CMPT135_String obj;
    int end=length+startIndex-1;
    if (length>(getC_StringLength(this->buffer)-1))
        end=getC_StringLength(this->buffer)-1;
    for (int i=startIndex; i<=end; i++)
    {
        obj.append(this->buffer[i]);
    }
    return obj;
}
bool CMPT135_String::isSubString(const CMPT135_String &s) const
{
    for (int i=0; i<this->getLength()-s.getLength()+1; i++)
    {
        if (this->getSubString(i,s.getLength())==s)
            return true;
    }
    return false;
}
bool CMPT135_String::isSubString(const char *buffer) const
{
    CMPT135_String obj(buffer);
    for (int i=0; i<this->getLength()-obj.getLength()+1; i++)
    {
        if (this->getSubString(i,obj.getLength())==obj)
            return true;
    }
    return false;
}
void CMPT135_String::reverse()
{
    char *ch = new char [this->length+1];
    int x=this->length-1;
    for (int i=0; i<this->length; i++)
    {
        ch[i]=this->buffer[x];
        x--;
    }
    ch[this->length]='\0';
    delete [] this->buffer;
    this->buffer=ch;
}
void CMPT135_String::removeChar(const char &c)
{
    CMPT135_String obj;
    for (int i=0; i<this->getLength(); i++)
    {
        if (this->buffer[i]!=c)
            obj.append(this->buffer[i]);
    }
    *this=obj;
}
void CMPT135_String::replace(const char &c1, const char &c2)
{
    for (int i=0; i<this->getLength(); i++)
    {
        if (this->buffer[i]==c1)
            this->buffer[i]=c2;
    }
}

//Operator member functions
CMPT135_String CMPT135_String::operator + (const CMPT135_String &s) const
{
    CMPT135_String obj;
    obj.append(*this);
    obj.append(s);
    return obj;
}
CMPT135_String CMPT135_String::operator + (const char *buffer) const // *buffer is a null terminated char array
{
    CMPT135_String obj;
    obj.append(*this);
    obj.append(buffer);
    return obj;
}
CMPT135_String CMPT135_String::operator + (const char &c) const
{
    CMPT135_String obj;
    obj.append(*this);
    obj.append(c);
    return obj;
}
void CMPT135_String::operator += (const CMPT135_String &s)
{
    *this=*this+s;
}
void CMPT135_String::operator += (const char &c)
{
    *this=*this+c;
}
void CMPT135_String::operator += (const char* buffer) // *buffer is a null char terminated char array
{
    *this=*this+buffer;
}
bool CMPT135_String::operator == (const CMPT135_String &s) const
{
    if (this->getLength()==s.getLength())
    {
        for (int i=0; i<this->getLength(); i++)
        {
            if (this->buffer[i]==s.buffer[i])
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}
bool CMPT135_String::operator == (const char *buffer) const // *buffer is a null char terminated char
{
    CMPT135_String obj(buffer);
    if (*this==obj)
        return true;
    else
        return false;
}
bool CMPT135_String::operator != (const CMPT135_String &s) const
{
    if (*this==s)
        return false;
    else
        return true;
}
bool CMPT135_String::operator != (const char *buffer) const // *buffer is a null char terminated char
{
    CMPT135_String obj(buffer);
    if (*this==obj)
        return false;
    else
        return true;
}
bool CMPT135_String::operator < (const CMPT135_String &s) const
{
    if (this->isSubString(s) && this->getLength()==s.getLength())
        return false;
    for (int i=0; this->getLength() && s[i]!='\0'; i++)
    {
        if (this->buffer[i]==s[i])
            continue;
        if (this->buffer[i]<s[i])
            return true;
        if (this->buffer[i]>s[i])
            return false;
    }
    return true;
}
bool CMPT135_String::operator < (const char *buffer) const // *buffer is a null char terminated char array
{
    CMPT135_String obj(buffer);
    if (this->isSubString(obj) && this->getLength()==obj.getLength())
        return false;
    return (*this<obj);
}
bool CMPT135_String::operator > (const CMPT135_String &s) const
{
    if (this->isSubString(s) && this->getLength()==s.getLength())
        return false;
    return !(*this<s);
}
bool CMPT135_String::operator > (const char *buffer) const // *buffer is a null char terminated char array
{
    CMPT135_String obj(buffer);
    if (this->isSubString(obj) && this->getLength()==obj.getLength())
        return false;
    return !(*this<obj);
}
bool CMPT135_String::operator >= (const CMPT135_String &s) const
{
    if (this->isSubString(s) && this->getLength()==s.getLength())
        return true;
    return !(*this<s);
}
bool CMPT135_String::operator >= (const char *buffer) const // *buffer is a null char terminated char array
{
    CMPT135_String obj(buffer);
    if (this->isSubString(obj) && this->getLength()==obj.getLength())
        return true;
    return !(*this<obj);
}
bool CMPT135_String::operator <= (const CMPT135_String &s) const
{
    if (this->isSubString(s) && this->getLength()==s.getLength())
        return true;
    return (*this<s);
}
bool CMPT135_String::operator <= (const char *buffer) const // *buffer is a null char terminated char array
{
    CMPT135_String obj(buffer);
    if (this->isSubString(obj) && this->getLength()==obj.getLength())
        return true;
    return (*this<obj);
}

//Friend Functions (for operators)
CMPT135_String operator + (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj;
    obj.append(buffer);
    obj.append(s);
    return obj;
}
CMPT135_String operator + (const char &c, const CMPT135_String &s)
{
    CMPT135_String obj;
    obj.append(c);
    obj.append(s);
    return obj;
}
bool operator == (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj==s);
}
bool operator != (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj!=s);
}
bool operator < (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj<s);
}
bool operator > (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj>s);
}
bool operator <= (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj<=s);
}
bool operator >= (const char *buffer, const CMPT135_String &s) // *buffer is a null terminated char array
{
    CMPT135_String obj(buffer);
    return (obj>=s);
}

ostream& operator << (ostream &outputStream, const CMPT135_String &s)
{
    for (int i = 0; i < s.getLength(); i++)
        outputStream << s[i];
    return outputStream;
}

istream& operator >> (istream &inputStream, CMPT135_String &s)
{
    /* This function is designed to read ANY length input string from the user.
    In order to achieve this, we will read characters until end of line character ('\n') is read.
    The trouble will be where to store the unknown length input. 
     For this, we will create a char array (named buffer1) of length 100.
    The hope is, the input won't exceed 100 chars.
    However if it does, we will copy the 100 chars to a temp char array, make the buffer1 array of twice its current length,
    copy the characters in the temp array to buffer1 and continue reading; applying same principle if buffer1 gets filled again.
    Finally, we will copy the exact characters read to another buffer (named buffer2) and use that to set the buffer of CMPT135_String object parameter.
    Finally, we will do clean up of unnecessary dynamic arrays. */
    int bufferCurrentLength = 100;
    char *buffer1 = new char[bufferCurrentLength];
    int length = 0;
    char c;
    while (1)
    {
        inputStream.get(c);
        if (c == '\n')
            break;
        buffer1[length++] = c;
        
        //Now, check in case buffer is filled
        if (length == bufferCurrentLength)
        {
            //Copy current buffer to temp array
            char *temp = new char[2*bufferCurrentLength];
            for (int i = 0; i < bufferCurrentLength; i++)
                temp[i] = buffer1[i];
            //Delete current buffer
            delete[] buffer1;
            //Point buffer1 to temp
            buffer1 = temp;
            //Adjust the size of the current buffer
            bufferCurrentLength *= 2;
        }
    }
    //Create a buffer of exact size for the characters read
    char *buffer2 = new char[length + 1];
    //Copy chars in current buffer to the exact size buffer
    for (int i = 0; i < length; i++)
        buffer2[i] = buffer1[i];
    //Append the a NULL character to the exact size buffer
    buffer2[length] = '\0';
    /* Set the exact size buffer as the buffer of the CMPT135_String object being read.
    The set buffer function will take care of adjusting the length of the object. 
    Also the setBuffer function will first clean the current buffer for us. */
    s.setBuffer(buffer2);
    
    //Clean up the current buffer and the exact size buffer
    delete[] buffer1;
    delete[] buffer2;
    
    //Return the input stream
    return inputStream;
}


int main()
{
    //Test getC_StringLength static member function
    char *charArray = "This is interesting."; //Length must be 20
    cout << "The length of charArray is " << CMPT135_String ::getC_StringLength(charArray) << endl;
    
    //Test default constructor
    CMPT135_String s1;
    cout << "s1 is " << s1 << ", length = " << s1.getLength() << endl;
    
    //Test non-default constructor
    CMPT135_String s2(charArray);
    cout << "s2 is " << s2 << ", length = " << s2.getLength() << endl;
    
    //Test copy constructor
    CMPT135_String s3 = s2;
    cout << "s3 is " << s3 << ", length = " << s3.getLength() << endl;
    
    //Test destructor
    s3.~CMPT135_String();
    cout << "After destruction, s3 is " << s3 << ", length = " << s3.getLength() << endl;
    
    //Test assignment operators
    CMPT135_String s4;
    s4 = s2; //length of s4 must be 20
    cout << "s4 assigned s2. s4 is " << s4 << ", length = " << s4.getLength() << endl;
    s4 = 'Y';
    cout << "s4 assigned 'Y'. s4 is " << s4 << ", length = " << s4.getLength() << endl;
    s4 = "So far so good!"; //length of s4 must be 15
    cout << "s4 assigned \"So far so good!\". s4 is " << s4 << ", length = " << s4.getLength() << endl;
    
    //Test chain assignment
    CMPT135_String t1, t2, t3;
    t1 = t2 = t3 = s4;
    cout << "After assigning t1 = t2 = t3 = s4, we get:" << endl; cout << "\tt1 is " << t1 << endl;
    cout << "\tt2 is " << t2 << endl;
    cout << "\tt3 is " << t3 << endl;
    
    //Test getLength. Already used (tested) above.
    
    //Test operator [ ]
    cout << "s4 printed using indexing operator is ";
    for (int i = 0; i < s4.getLength(); i++)
        cout << s4[i];
    cout << endl;
    s4[3] = 'F';
    s4[7] = 'S';
    s4[10] = 'G';
    cout << "s4 capitalized. s4 is " << s4 << ", length = " << s4.getLength() << endl;
    
    //Test append member functions
    s3.append(s4);
    cout << "s3 appened by s4. s3 is now " << s3 << ", length = " << s3.getLength() << endl;
    s1.append("I was empty before I got appended"); //length must be 33
    cout << "s1 got appened. s1 is now " << s1 << ", length = " << s1.getLength() << endl;
    s1.append('.'); //length must be 34
    cout << "s1 appened by '.'. s1 is now " << s1 << ", length = " << s1.getLength() << endl;
    
    //Test setBuffer member function
    s1.setBuffer("I am changing a lot."); //length must be 20
    cout << "s1 got modified. s1 is now " << s1 << ", length = " << s1.getLength() << endl;
    
    //Test findCharIndex
    char c = 'a';
    cout << "The first index of " << c << " in " << s1 << " is " << s1.findCharIndex(c) << endl;
    c = 'A';
    cout << "The first index of " << c << " in " << s1 << " is " << s1.findCharIndex(c) << endl;
    
    //Test reverseFindCharIndex
    c = 'a';
    cout << "The last index of " << c << " in " << s1 << " is " << s1.reverseFindCharIndex(c) << endl;
    c = 'A';
    cout << "The last index of " << c << " in " << s1 << " is " << s1.reverseFindCharIndex(c) << endl;
    
    //Test getSubString
    cout << "Substring of s2 starting from index 8 having length 11 is \"" << s2.getSubString(8, 11) << "\"" << endl;
    
    //Test isSubString member functions
    CMPT135_String sb = "So";
    if (s3.isSubString(sb))
        cout << sb << " is a substring of " << s3 << endl;
    else
        cout << sb << " is NOT a substring of " << s3 << endl;
    sb = "so";
    if (s3.isSubString(sb))
        cout << sb << " is a substring of " << s3 << endl;
    else
        cout << sb << " is NOT a substring of " << s3 << endl;
    if (s3.isSubString(""))
        cout << "" << " is a substring of " << s3 << endl;
    else
        cout << "" << " is NOT a substring of " << s3 << endl;
    if (s3.isSubString("oF"))
        cout << "oF" << " is a substring of " << s3 << endl;
    else
        cout << "oF" << " is NOT a substring of " << s3 << endl;
    
    //Test reverse
    s1.reverse();
    cout << "The reverse of s1 is " << s1 << endl;
    s1.reverse();
    cout << "Reversing s1 again, we get " << s1 << endl;
    
    //Test removeChar
    s4.removeChar(' '); //Rwemove the spaces
    cout << "After removing spaces, s4 is " << s4 << endl;
    
    //Test replace
    s1.replace('.', '!');
    cout << "After replacing . by ! in s1, s1 is now " << s1 << endl;
    
    //Test operator + member functions
    cout << "s1 + s2 is " << s1 + s2 << endl;
    cout << "s1 + \" HUH\" is " << s1 + " HUH" << endl;
    cout << "s4 + '!' is " << s4 + '!' << endl;
    
    //Test += operators
    CMPT135_String s5;
    s5 += CMPT135_String("Yonas ");
    cout << "s5 is " << s5 << endl;
    s5 += "T";
    cout << "s5 is " << s5 << endl;
    s5 += ". ";
    cout << "s5 is " << s5 << endl;
    s5 += "Weldeselassie";
    cout << "s5 is " << s5 << endl;
    
    //Test operator == member functions
    cout << "Using == operator: ";
    if (s3 == s4)
        cout << s3 << " and " << s4 << " are equal" << endl;
    else
        cout << s3 << " and " << s4 << " are NOT equal" << endl;
    cout << "Using == operator: ";
    if (s3 == "So Far So Good!")
        cout << s3 << " and " << "\"So Far So Good!\"" << " are equal" << endl;
    else
        cout << s3 << " and " << "\"So Far So Good!\"" << " are NOT equal" << endl;
    
    //Test operator != member functions
    cout << "Using != operator: ";
    if (s3 != s4)
        cout << s3 << " and " << s4 << " are NOT equal" << endl;
    else
        cout << s3 << " and " << s4 << " are equal" << endl; cout << "Using != operator: ";
    if (s3 != "So Far So Good!")
        cout << s3 << " and " << "\"So Far So Good!\"" << " are NOT equal" << endl;
    else
        cout << s3 << " and " << "\"So Far So Good!\"" << " are equal" << endl;
    
    //Test operator < member operators
    cout << "Using < operator: ";
    if (s3 < s4)
        cout << s3 << " is less than " << s4 << endl;
    else
        cout << s3 << " is NOT less than " << s4 << endl;
    cout << "Using < operator: ";
    if (s3 < "So Far So Good!")
        cout << s3 << " is less than " << "\"So Far So Good!\"" << endl;
    else
        cout << s3 << " is NOT less than " << "\"So Far So Good!\"" << endl;
    
    //Test operator > member operators
    cout << "Using > operator: ";
    if (s4 > s3)
        cout << s4 << " is greater than " << s3 << endl;
    else
        cout << s4 << " is NOT greater than " << s3 << endl;
    cout << "Using > operator: ";
    if (s3 > "So Far So Good!")
        cout << s3 << " is greater than " << "\"So Far So Good!\"" << endl;
    else
        cout << s3 << " is NOT greater than " << "\"So Far So Good!\"" << endl;
    
    //Test operator >= member operators
    cout << "Using >= operator: ";
    if (s4 >= s3)
        cout << s4 << " is greater than or equal to " << s3 << endl;
    else
        cout << s4 << " is NOT greater than or equal to " << s3 << endl;
    cout << "Using >= operator: ";
    if (s3 >= "So Far So Good!")
        cout << s3 << " is greater than or equal to " << "\"So Far So Good!\"" << endl;
    else
        cout << s3 << " is NOT greater than or equal to " << "\"So Far So Good!\"" << endl;
    
    //Test operator <= member operators
    cout << "Using <= operator: ";
    if (s3 <= s4)
        cout << s3 << " is less than or equal to " << s4 << endl;
    else
        cout << s3 << " is NOT less than or equal to " << s4 << endl;
    cout << "Using <= operator: ";
    if (s3 <= "So Far So Good!")
        cout << s3 << " is less than or equal to " << "\"So Far So Good!\"" << endl;
    else
        cout << s3 << " is NOT less than or equal to " << "\"So Far So Good!\"" << endl;
    
    //Test operator + friend functions
    cout << "\"HUH \" + " << s1 << " is " << "HUH " + s1 << endl;
    cout << "! + " << s1 << " is " << '!' + s1 << endl;
    
    //Test operator == friend function
    cout << "Using == friend function: ";
    if ("Yonas T. Weldeselassie" == s5)
        cout << "\"Yonas T. Weldeselassie\" is equal to " << s5 << endl;
    else
        cout << "\"Yonas T. Weldeselassie\" is NOT equal to " << s5 << endl;
    
    //Test operator != friend function
    cout << "Using != friend function: ";
    if ("Yonas T. Weldeselassie" != s5)
        cout << "\"Yonas T. Weldeselassie\" is NOT equal to " << s5 << endl;
    else
        cout << "\"Yonas T. Weldeselassie\" is equal to " << s5 << endl;
    
    //Test operator < friend function
    cout << "Using < friend function: ";
    if ("Yonas Weldeselassie" < s5)
        cout << "\"Yonas Weldeselassie\" is less than " << s5 << endl;
    else
        cout << "\"Yonas Weldeselassie\" is NOT less than " << s5 << endl;
    
    //Test operator > friend function
    cout << "Using > friend function: ";
    if ("Yonas Weldeselassie" > s5)
        cout << "\"Yonas Weldeselassie\" is greater than " << s5 << endl;
    else
        cout << "\"Yonas Weldeselassie\" is NOT greater than " << s5 << endl;
    
    //Test operator <= friend function
    cout << "Using <= friend function: ";
    if ("Yonas Weldeselassie" <= s5)
        cout << "\"Yonas Weldeselassie\" is less than or equal to " << s5 << endl;
    else
        cout << "\"Yonas Weldeselassie\" is NOT less than or equal to " << s5 << endl;
    
    //Test operator >= friend function
    cout << "Using >= friend function: ";
    if ("Yonas Weldeselassie" >= s5)
        cout << "\"Yonas Weldeselassie\" is greater than or equal to " << s5 << endl;
    else
        cout << "\"Yonas Weldeselassie\" is NOT greater than or equal to " << s5 << endl;
    
    //Test operator << friend function: Already tested above.
    
    //Test operator >> friend function: Already tested above.
    CMPT135_String s6;
    cout << "Enter a CMPT135_String object. Just type the characters: ";
    cin >> s6;
    cout << "You entered the CMPT135_String object \"" << s6 << "\"" << endl;
    
    cout << endl << "This completes the test program..." << endl << endl;
    
    //system("Pause");
    return 0;
}
