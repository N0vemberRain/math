#include <iostream>
#include <cmath>
#include <cstdlib>
#include <initializer_list>
#include <typeinfo>
#include <exception>
#include "point_exception.cpp"
//#include "point_interface.h"

using namespace std;

template <class T>
class Point
{
private:
    T x, y, z;
    //int x, y, z;

public:
    Point();

    Point(T new_x, T new_y, T new_z);

    //template <class T>
    /*Point(initializer_list<T> initList)
        : x(initList[0]), y(initList[1]), z(initList[2])
    {}*/

    Point(const Point& p);
/*
    Point(T&& x, T&& y, T&& z)
        : x(x), y(y), z(z)
    {}
*/
    ~Point();

    void setX(T new_x) { x = new_x; }
    void setY(T new_y) { y = new_y; }
    void setZ(T new_z) { z = new_z; }

    T getX() { return x; }
    T getY() { return y; }
    T getZ() { return z; }

    Point operator=(const Point& p);

    template <class Type>
    friend ostream& operator<<(ostream& stream, const Point<Type>& p);

    template <class Type>
    friend bool operator<(const Point<Type>& p1, const Point<Type>& p2);
};

template <typename T>
class FromDecToSphere
{
private:
    Point<T> A;
    double r;
    double teta;
    double phi;
public:
    FromDecToSphere()
        //: A(A)
    {}

        void operator()(Point<T> A)
        {
            r = sqrt(pow(A.getX(), 2) +
                     pow(A.getY(), 2) +
                     pow(A.getZ(), 2));

            teta = acos((double)(A.getZ()
             / (sqrt(pow(A.getX(), 2) +
                     pow(A.getY(), 2) +
                     pow(A.getZ(), 2)))));

            phi = atan((double)(A.getY()/A.getZ()));
            /*Point<double> dA;
            dA.setX(static_cast <double> (A.getX()));
            dA.setY(static_cast <double> (A.getY()));
            dA.setZ(static_cast <double> (A.getZ()));
            cout << dA << endl;
            phi = [](Point<double> dA) ->double
                { return atan((double)(dA.getY()/dA.getZ())); };*/

            cout << "Sphere coords: \n";
            cout << "r: " << r << endl;
            cout << "teta: " << teta << endl;
            cout << "phi: " << phi << endl;
            //cout << typeid(phi).name() << endl;
        }
    /*void operator()(Point<T> A)
    {
        r = sqrt(pow(this->A->getX(), 2) +
                 pow(this->A->getY(), 2) +
                 pow(this->A->getZ(), 2));

        teta = acos((double)(this->A->getZ()
         / (sqrt(pow(this->A->getX(), 2) +
                 pow(this->A->getY(), 2) +
                 pow(this->A->getZ(), 2)))));

        phi = atan((double)(this->A->getY()/this->A->getZ()));
    }*/
};

template <class T>
Point<T>::Point()
    : x(0.0), y(0.0), z(0.0)
{}

template <class T>
Point<T>::Point(T new_x, T new_y, T new_z)
    : x(new_x), y(new_y), z(new_z)
{}

template <class T>
Point<T>::Point(const Point& p)
    : x(p.x), y(p.y), z(p.z)
{}

template <class T>
Point<T>::~Point()
{}


template <class T>
Point<T> Point<T>::operator=(const Point& p)
{
    if (this != &p)
    {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }

    return *this;
}

template <class T>
ostream& operator<<(ostream& stream, const Point<T>& p)
{
    stream << "(" << p.x << ", " << p.y
           << ", " << p.z << ")";

    return stream;
}

template <class T>
bool operator<(const Point<T>& p1, const Point<T>& p2)
{
    float s1 = pow(p1.x, 2) + pow(p1.y, 2) + pow(p1.z, 2);
    float s2 = pow(p2.x, 2) + pow(p2.y, 2) + pow(p2.z, 2);

    return  sqrt(s1) < sqrt(s2) ? true : false;
}
/*
int main(int argc, char const *argv[]) {

    Point<int> A(-2, 3, 4);

    FromDecToSphere<int> f;
    f(A);

    return 0;
}
*/
