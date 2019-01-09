//
//  main.cpp
//  assignment 2 new
//
//  Created by Kazi Zubayer Quader on 7/23/17.
//  Copyright © 2017 Kazi Zubayer Quader. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual string getName() const = 0;
    virtual void printShapeInformation() const = 0;
};

class Triangle : public Shape
{
private:
    double s1,s2,s3;
    
public:
    Triangle();
    Triangle(double s1, double s2, double s3);
    
    double getSide1()const;
    double getSide2()const;
    double getSide3()const;
    
    void setSide1(const double s1);
    void setSide2(const double s2);
    void setSide3(const double s3);
    
    double getCircumference() const;
    virtual double getArea() const;
    virtual string getName() const;
    virtual void printShapeInformation() const;
};
Triangle :: Triangle()
{
    this->s1 = 1.0;
    this->s2 = 1.0;
    this->s3 = 1.0;
}
Triangle :: Triangle(double s1, double s2, double s3)
{
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
}
double Triangle :: getSide1()const
{
    return this->s1;
}
double Triangle :: getSide2()const
{
    return this->s2;
}
double Triangle :: getSide3()const
{
    return this->s3;
}
void Triangle :: setSide1(const double s1)
{
    this->s1 = s1;
}
void Triangle :: setSide2(const double s2)
{
    this->s2 = s2;
}
void Triangle :: setSide3(const double s3)
{
    this->s3 = s3;
}
double Triangle :: getCircumference() const
{
    return this->s1+this->s2+this->s3;
}
double Triangle :: getArea() const
{
    double p = (this->s1 + this->s2 + this->s3) / 2;
    double area = sqrt(p*(p-this->s1)*(p-this->s2)*(p-this->s3));
    return area;
}
string Triangle :: getName() const
{
    return "Triangle";
}
void Triangle::printShapeInformation() const
{
    cout << this->getName() << endl;
    cout << "\tSide1 = " << this->getSide1() << ", Side2 = " << this->getSide2() << ", Side3 = " << this->getSide3() << endl;
    cout << "\tCircumference = " << this->getCircumference() << ", Area = " << this->getArea() << endl;
}

class Rectangle : public Shape
{
private:
    double s1,s2;
    
public:
    Rectangle();
    Rectangle(double s1, double s2);
    
    double getSide1() const;
    double getSide2() const;
    
    void setSide1(const double s1);
    void setSide2(const double s2);
    
    double getCircumference() const;
    virtual double getArea() const;
    virtual string getName() const;
    virtual void printShapeInformation() const;
};
Rectangle :: Rectangle()
{
    this->s1 = 1.0;
    this->s2 = 2.0;
}
Rectangle :: Rectangle(double s1, double s2)
{
    this->s1 = s1;
    this->s2 = s2;
}
double Rectangle :: getSide1() const
{
    return this->s1;
}
double Rectangle :: getSide2() const
{
    return this->s2;
}
void Rectangle :: setSide1(const double s1)
{
    this->s1 = s1;
}
void Rectangle :: setSide2(const double s2)
{
    this->s2 = s2;
}
double Rectangle :: getCircumference() const
{
    double circ;
    circ = 2*(this->s1 + this->s2);
    return circ;
}
double Rectangle :: getArea() const
{
    return this->s1*this->s2;
}
string Rectangle :: getName() const
{
    return "Rectangle";
}
void Rectangle::printShapeInformation() const
{
    cout << this->getName() << endl;
    cout << "\tSide1 = " << this->getSide1() << ", Side2 = " << this->getSide2() << endl;
    cout << "\tCircumference = " << this->getCircumference() << ", Area = " << this->getArea() << endl;
}

class Circle : public Shape
{
private:
    double r;
    
public:
    Circle();
    Circle(double r);
    
    double getRadius() const;
    void setRadius(const double r);
    
    double getCircumference() const;
    virtual double getArea() const;
    virtual string getName() const;
    virtual void printShapeInformation() const;
};
Circle :: Circle()
{
    this->r = 1.0;
}
Circle :: Circle(double r)
{
    this->r = r;
}
double Circle :: getRadius() const
{
    return this->r;
}
void Circle::setRadius(const double r)
{
    this->r = r;
}
double Circle :: getCircumference() const
{
    return 2 * 3.14 * this->r;
}
double Circle :: getArea() const
{
    return 3.14 * this->r * this->r;
}
string Circle::getName() const
{
    return "Circle";
}
void Circle::printShapeInformation() const
{
    cout << this->getName() << endl;
    cout << "\tRadius = " << this->getRadius() << endl;
    cout << "\tCircumference = " << this->getCircumference() << ", Area = " << this->getArea() << endl;
}

class Node
{
private:
    Shape* sPtr;
    Node* link;
public:
    Node();
    Node(Shape* sPtr, Node* link);
    
    Shape* getShape() const;
    Node* getLink() const;
    
    void setShape(Shape* sPtr);
    void setLink(Node* link);
};
Node::Node()
{
    this->sPtr = nullptr;
    this->link = nullptr;
}
Node::Node(Shape* sPtr, Node* link)
{
    this->sPtr = sPtr;
    this->link = link;
}
Shape* Node::getShape() const
{
    return this->sPtr;
}
Node* Node::getLink() const
{
    return this->link;
}
void Node::setShape(Shape* sPtr)
{
    this->sPtr = sPtr;
}
void Node::setLink(Node* link)
{
    this->link = link;
}

typedef Node* NodePtr;
typedef Shape* ShapePtr;

class LinkedList
{
private:
    NodePtr head;
    
public:
    LinkedList();
    ~LinkedList();
    
    bool isEmptyLinkedList() const;
    void printLinkedList() const;
    
    //ASSIGNMENT QUESTIONS
    /*
     1. Implement the head_insert member function.
     This function must insert the shape argument at the head of the Linked List
     */
    void head_insert(ShapePtr sPtr);
    
    /*
     2. Implement the insert_grouped member function.
     This function must insert the shape argument in the Linked List such that
     same shapes are always grouped together in the Linked List. Here it does
     not matter where you insert the new shape within the group of shapes of same type
     */
    void insert_grouped(ShapePtr sPtr);
    /*
     3. Implement the insert_grouped_sorted member function
     This function must insert the shape argument in the Linked List such that
     same shapes are always grouped together in the Linked List and group of
     the same shapes are sorted in increasing order of their areas.
     */
    void insert_grouped_sorted(ShapePtr sPtr);
};
LinkedList::LinkedList()
{
    this->head = nullptr;
}
LinkedList::~LinkedList()
{
    //This member function wipes out the whole Linked List
    while (this->isEmptyLinkedList() == false)
    {
        //First get the pointer of the Node to be deleted
        NodePtr temp = this->head;
        //Advance head to the next Node
        this->head = this->head->getLink();
        //At this point temp is a pointer to a Node
        //But the Node pointed by temp has a pointer pointing to a shape object
        //So first delete the shape object
        delete temp->getShape();
        //Finally delete the Node
        delete temp;
    }
}
bool LinkedList::isEmptyLinkedList() const
{
    if (this->head == nullptr)
        return true;
    else
        return false;
}
void LinkedList::printLinkedList() const
{
    if (this->isEmptyLinkedList())
    {
        cout << "Empty Linked List" << endl << endl;
        return;
    }
    else
    {
        NodePtr temp = head;
        while (temp != nullptr)
        {
            temp->getShape()->printShapeInformation();
            temp = temp->getLink();
        }
    }
    cout << endl;
}
void LinkedList::head_insert(ShapePtr sPtr)
{
    NodePtr a = new Node();
    a->setLink(this->head);
    this->head = a;
    a->setShape(sPtr);
}
void LinkedList::insert_grouped(ShapePtr sPtr)
{
    NodePtr n1, n2;
    if (this->head == nullptr)
    {
        head_insert(sPtr);
        return;
    }
    else if (this->head->getShape()->getName() == sPtr-> getName())
    {
        head_insert(sPtr);
        return;
    }
    else
    {
        n2 = this->head;
        n1 = this->head->getLink();
        while (n1 != nullptr)
        {
            if (n1->getShape()->getName() == sPtr->getName())
            {
                NodePtr a = new Node();
                a->setShape(sPtr);
                a->setLink(n2->getLink());
                n2->setLink(a);
                return;
            }
            else
            {
                n2=n1;
                n1=n1->getLink();
            }
        }
        NodePtr a = new Node ();
        a->setShape(sPtr);
        a->setLink(nullptr);
        n2->setLink(a);
    }
}
void LinkedList::insert_grouped_sorted(ShapePtr sPtr)
{
    //IMPLEMENT THIS
    NodePtr n1, n2;
    if (this->head == nullptr)
    {
        head_insert(sPtr);
        return;
    }
    else if ((this->head->getShape()->getName() == sPtr-> getName()) && (sPtr->getArea() <= this->head->getShape()->getArea()))
    {
        head_insert(sPtr);
        return;
    }
    else
    {
        n2 = this->head;
        n1 = this->head->getLink();
        while (n1 != nullptr)
        {
            if ((n1->getShape()->getName() == sPtr->getName()) && (sPtr->getArea() <= this->head->getShape()->getArea()))
            {
                NodePtr a = new Node();
                a->setShape(sPtr);
                a->setLink(n2->getLink());
                n2->setLink(a);
                return;
            }
            else if ((n2->getShape()->getName() == sPtr->getName()) && (n1->getShape()->getName() != sPtr->getName()))
            {
                NodePtr a = new Node();
                a->setShape(sPtr);
                a->setLink(n2->getLink());
                n2->setLink(a);
                return;
            }
            else
            {
                n2=n1;
                n1=n1->getLink();
            }
        }
        NodePtr a = new Node ();
        a->setShape(sPtr);
        a->setLink(nullptr);
        n2->setLink(a);
    }
}

int main()
{
    //Setup random number generator
    srand(time(0));
    
    //Create an Empty Linked List
    LinkedList L;
    
    //Print the Linked List to see it is Empty Linked List
    cout << "Created an Empty Linked List which looks like" << endl;
    L.printLinkedList();
    system("Pause");
    
    //Insert ten random objects in the Linked List using head_insert member function
    for (int i = 0; i < 10; i++)
    {
        int randomShape = rand() % 3;
        if (randomShape == 0)
        {
            cout << "Inserting Triangle with head_insert member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.head_insert(new Triangle(s1, s2, sqrt(s1*s1+s2*s2)));
        }
        else if (randomShape == 1)
        {
            cout << "Inserting Rectangle with head_insert member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.head_insert(new Rectangle(s1, s2));
        }
        else
        {
            cout << "Inserting Circle with head_insert member function." << endl;
            double r = static_cast<double>(rand()) / RAND_MAX;
            L.head_insert(new Circle(r));
        }
    }
    
    //Print the Linked List to see we have inserted ten Nodes
    cout << "After inserting ten nodes with head_insert member function, the Linked List is" << endl;
    L.printLinkedList();
    system("Pause");
    
    //Delete the Linked List
    cout << "Deleting the Linked List" << endl;
    L.~LinkedList();
    
    //Print the Linked List to see it is Empty Linked List
    cout << "After deleting the Linked List, the Linked List is" << endl;
    L.printLinkedList();
    system("Pause");
    
    //Insert ten random shapes using insert_grouped member function
    for (int i = 0; i < 10; i++)
    {
        int randomShape = rand() % 3;
        if (randomShape == 0)
        {
            cout << "Inserting Triangle with insert_grouped member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped(new Triangle(s1, s2, sqrt(s1*s1+s2*s2)));
        }
        else if (randomShape == 1)
        {
            cout << "Inserting Rectangle with insert_grouped member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped(new Rectangle(s1, s2));
        }
        else
        {
            cout << "Inserting Circle with insert_grouped member function." << endl;
            double r = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped(new Circle(r));
        }
    }
    
    //Print the Linked List to see we have inserted ten Nodes
    cout << "After inserting ten nodes with insert_grouped member function, the Linked List is" << endl;
    L.printLinkedList();
    
    //Delete the Linked List
    cout << "Deleting the Linked List" << endl;
    L.~LinkedList();
    
    //Print the Linked List to see it is Empty Linked List
    cout << "After deleting the Linked List, the Linked List is" << endl;
    L.printLinkedList();
    system("Pause");
    
    //Insert ten random shapes using insert_grouped_sorted member function
    for (int i = 0; i < 10; i++)
    {
        int randomShape = rand() % 3;
        if (randomShape == 0)
        {
            cout << "Inserting Triangle with insert_grouped_sorted member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped_sorted(new Triangle(s1, s2, sqrt(s1*s1+s2*s2)));
        }
        else if (randomShape == 1)
        {
            cout << "Inserting Rectangle with insert_grouped_sorted member function." << endl;
            double s1 = static_cast<double>(rand()) / RAND_MAX;
            double s2 = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped_sorted(new Rectangle(s1, s2));
        }
        else
        {
            cout << "Inserting Circle with insert_grouped_sorted member function." << endl;
            double r = static_cast<double>(rand()) / RAND_MAX;
            L.insert_grouped_sorted(new Circle(r));
        }
    }
    
    //Print the Linked List to see we have inserted ten Nodes
    cout << "After inserting ten nodes with insert_grouped_sorted member function, the Linked List is" << endl;
    L.printLinkedList();
    
    //Delete the Linked List
    cout << "Deleting the Linked List" << endl;
    L.~LinkedList();
    
    //Print the Linked List to see it is Empty Linked List
    cout << "After deleting the Linked List, the Linked List is" << endl;
    L.printLinkedList();
    
    system("Pause");
    return 0;
}


