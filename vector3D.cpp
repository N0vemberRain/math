#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <functional>
#include <utility>
#include <typeinfo>
#include "point.cpp"
#include "vector.cpp"

using namespace std;

template <typename T>
class Vector_3d
    : public Vector<T>
{
private:
    Point<T> begin;
    Point<T> end;

public:

//    T& X = v[0]; T& Y = v[1]; T& Z = v[2];
    //using Vector<T>::operator+;
    Vector_3d()
        : Vector<T>(3)
    {}

    Vector_3d(T x, T y, T z)
        : Vector<T>(3)//, X(x), Y(y), Z(z)
    {
        Vector<T>::setX(x);
        Vector<T>::setY(y);
        Vector<T>::setZ(z);
    }

    Vector_3d(T begin_x, T begin_y, T begin_z,
              T end_x, T end_y, T end_z)
        :  Vector<T>(3), begin(Point<T>(begin_x, begin_y, begin_z)),
                         end(Point<T>(end_x, end_y, end_z))
    {
        Vector<T>::setX(end.getX() - begin.getX());
        Vector<T>::setY(end.getY() - begin.getY());
        Vector<T>::setZ(end.getZ() - begin.getZ());
    }

    Vector_3d(const Vector_3d<T>& v)
        //: Vector<T>(v)

    {
        setX(v.getX); setY(v.getY); setZ(v.getZ);
        cout << "[Vector_3d] Constr. copy.\n";
    }

    Vector_3d<T> operator=(const Vector_3d<T>& v)
    {
        //Vector<T>::operator=(v);
        setX(v.getX); setY(v.getY); setZ(v.getZ);
        cout << "[Vector_3d] Op. =\n";
    }

    Vector_3d(Vector_3d<T>&& v) = delete;
    Vector_3d& operator=(Vector_3d<T>&& v) = delete;

    virtual ~Vector_3d() { cout << "[Vector_3d] Kill.\n"; }

    T getX() const { return Vector<T>::getX(); }
    T getY() const { return Vector<T>::getY(); }
    T getZ() const { return Vector<T>::getZ(); }

    void setX(const T new_x) { Vector<T>::setX(new_x); }
    void setY(const T new_y) { Vector<T>::setY(new_y); }
    void setZ(const T new_z) { Vector<T>::setZ(new_z); }

    void setPoints(Point<T>&& a, Point<T>&& b)
    {
        begin = move(a); end = move(b);
    }

    void showVec() { cout << *this << endl << "Begin: "
                          << begin << " .End: " << end << ".\n"; }

    auto absVec() { return Vector<T>::absVec(); }

};




/*

int main(int argc, char const *argv[])
{
    Vector<int>* v[5];
    Vector_3d<int> v1(1, 2, 3); Vector_3d<int> v2(0, 6, 7);
    Vector_3d<int> v3(0, 1, 5); Vector_3d<int> v4(10, 46, 2);
    v[0] = &v1; v[1] = &v2; v[2] = &v3; v[3] = &v4;
    for (int i = 0; i < 4; i++)
        cout << *v[i] << " ";
    *v[3] = crossProduct(*v[0], *v[1]);
    cout << *v[3] << endl;
    auto r = v1.absVec();
    cout << r << endl;
    // pa = make_pair<Point<int>, Point<int>>((1,2,3), (4,5,6));
    //cout << pa; // << " " << typeid(pa).name;
    Vector_3d<int> p(1, 2, 3, 4, 5, 7);
    cout << p;
    return 0;
}
*/
