#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <vector>
#include <initializer_list>
#include <cmath>

namespace My_math
{
    namespace Poly
    {

template <typename T>
class Polynomial
{
public:
    using value_type = T;

    Polynomial();
    Polynomial(const unsigned N);
    Polynomial(std::initializer_list<value_type> list);
    Polynomial(Polynomial&& poly);
    Polynomial& operator=(Polynomial&& poly);
    ~Polynomial();

    Polynomial(const Polynomial& poly) = delete;
    Polynomial& operator=(const Polynomial& poly) = delete;

    void setValue(const float v) { this->x = v; }
    void setCoef();
    void setRang(const int N);
    int getRang() const { return this->rang; }
    value_type& getCoeff(const size_t index);
    const value_type& getCoeff(const size_t index) const;
    void randomPoly();

    template <class Type>
    friend Polynomial operator+(Polynomial<Type>&& p, const Polynomial<Type>& q);

    template <class Type>
    friend std::ostream& operator<<(std::ostream& stream, Polynomial<T>&& p);

    template <class Type>
    friend bool operator<(Polynomial<Type>& p, Polynomial<Type>& q);

private:
    unsigned rang;                    // Степень многочлена
    value_type *coefficient;     // Указатель на массив коэффициентов
};

template <typename T>
Polynomial<T>::Polynomial()
    : rang(1), coefficient(new T(0))
{}

template <typename T>
Polynomial<T>::Polynomial(const unsigned N)
    : rang(N), coefficient(new T[rang])
{
    for (size_t i = 0; i < rang; i++)
        coefficient[i] = 0;
}

template <typename T>
Polynomial<T>::Polynomial(std::initializer_list<T> list)
    : rang(list.size()), coefficient(new T[rang])
{
    size_t i = 0;
    for (const auto& it : list)
    {
        *(coefficient + i) = it;
        i++;
    }
}

template <typename T>
Polynomial<T>::Polynomial(Polynomial&& poly)
    : rang(std::move(poly.rang)), coefficient(std::move(poly.coefficient))
{
    std::cout << "[Polynomial] Move constr.\n";
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(Polynomial&& poly)
{
    assert(rang == poly.rang);
    std::swap(coefficient, poly.coefficient);
    std::cout << "[Polynomial] Move op. =\n";
    return *this;
}

template <typename T>
Polynomial<T>::~Polynomial() { delete[] coefficient; }

template <typename T>
T& Polynomial<T>::getCoeff(const size_t index)
{
    assert(index >= 0 && index <= rang);
    return coefficient[index];
}

template <typename T>
const T& Polynomial<T>::getCoeff(const size_t index) const
{
    assert(index >= 0 && index <= rang);
    return coefficient[index];
}
/*
template <class T>
void Polynomial<T>::randomPoly()
{
    std::vector<int> temp1[rang];
    std::vector<int> temp2[rang];
    for (auto& it : temp1)
    {
        *it = rand() % 10 + 1;
    }
    static_cast<float>(temp1);
    for (auto& it : temp2)
    {
        *it = rand() % 10 + 1;
    }
    static_cast<float>(temp2);
    for (auto& it : temp2)
    {
        *it = *it / 10;
    }
    for (size_t i = 0; i < rang; i++)
    {
        getCoeff(i) = temp1 + temp2;
    }
}
*/
template <typename T>
std::ostream& operator<<(std::ostream& stream, Polynomial<T>&& poly)
{
    for (size_t i = 0; i < poly.getRang() - 1; i++)
        stream << poly.getCoeff(i) << "*x^" << i << " + ";
    stream << poly.getCoeff(poly.getRang()-1) << "*x^" << poly.getRang() << std::endl;
    return stream;
}

template <typename Poly_type, typename Value_type>
auto evaluate(Polynomial<Poly_type>&& poly, Value_type x)
{
    auto res = 0.0;
    for (size_t i = 0; i < std::move(poly.getRang()); i++)
    {
        res += std::move(poly.getCoeff(i)) * pow(x, i);
    }
    return res;
}


/*
template <typename T>
void Polynomial<T>::setRang(const int N)
{
    this->rang = N;
    delete[] this->coefficient;
    this->coefficient = nullptr;
    this->coefficient = new Number[N];
    for (size_t i = 0; i < this->rang; i++)
    {
        coefficient[i] = 0;
    }
}
*/
template <typename Poly_type>
Polynomial<Poly_type> operator+(Polynomial<Poly_type>&& p, const Polynomial<Poly_type>& q)
{
    //Polynomial<Number> temp(0, p.n > q.n ? p.n-1 : q.n-1);
    assert(std::move(p.getRang()) == q.getRang());

    //Polynomial<Poly_type> sum(std::forward<Poly_type>(p.getRang()));

    for (size_t i = 0; i < p.getRang(); i++)
    {
        p.getCoeff(i) = p.getCoeff(i) + q.getCoeff(i);
    }/*
    for (size_t i = 0; i < sum.getRang(); i++)
        sum.getCoeff(i) = sum.getCoeff(i) + q.getCoeff(i);*/
    return std::move(p);
}

/*
template <class Number>
bool operator<(Polynomial<Number>& p, Polynomial<Number>& q)
{
    return p.evaluate(p.x) < q.evaluate(q.x) ? true : false;
}*/

    }
}
