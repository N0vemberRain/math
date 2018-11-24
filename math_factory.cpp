#include <iostream>
#include <memory>
#include <initializer_list>
#include "my_math_lib.h"

void createVec(int n) { My_math::Vec::Vector<int> v(n); std::cout << v; }
void createMatr(int row, int column) { My_math::Matr::Matrix<int> m(row, column); std::cout << m; }
void createPoly(int n) { My_math::Poly::Polynomial<int> p(n); std::cout << p; }

struct Math_factory
{
    virtual void operator()(const int n, int first ...) = 0;
    virtual ~Math_factory() {}
};

struct Vec_factory
    : Math_factory
{
    virtual void operator() (const int n, int first, ...) override { createVec(first); }
    virtual ~Vec_factory() {}
};

struct Matr_factory
    : Math_factory
{
    virtual void operator() (const int n, int first, ...) override
    {
         int* arg = &first; createMatr(*arg, *(arg+1));
    }
    virtual ~Matr_factory() {}
};

struct Poly_factory
    : Math_factory
{
    virtual void operator() (const int n, int first, ...) override
    {
        createPoly(first);
    }
    virtual ~Poly_factory() {}
};

int main(int argc, char const *argv[]) {

    std::unique_ptr<Math_factory> p_math;
    int c;
    //while(c == )
    //{
        std::cin >> c;
        int n = 3;
        switch (c) {
            case 1: p_math = std::unique_ptr<Vec_factory>(new Vec_factory);
                std::cout << "Init vector\n";
                break;
            case 2: p_math = std::unique_ptr<Matr_factory>(new Matr_factory);
                std::cout << "Init matrix\n";
                break;
            case 3: p_math = std::unique_ptr<Poly_factory>(new Poly_factory);
                std::cout << "Init polinomial\n";
                break;
        }

        (*p_math)(1, 4);
    //}

    return 0;
}
