#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <initializer_list>

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
    value_type& getCoeff(size_t index) { assert(index >= 0 && index <= rang);
                                        return coefficient[index]; }
    const value_type& getCoeff(size_t index) const
    { assert(index >= 0 && index <= rang);
                                        return coefficient[index]; }
    //auto evaluate(const float x);        // Вычислить

    template <class Type>
    friend Polynomial operator+(Polynomial<Type>& p, Polynomial<Type>& q);

    template <class Type>
    friend std::ostream& operator<<(std::ostream& stream, Polynomial<T>&& p);

    template <class Type>
    friend bool operator<(Polynomial<Type>& p, Polynomial<Type>& q);

private:
    unsigned rang;                    // Степень многочлена
    value_type *coefficient;     // Указатель на массив коэффициентов
    float x;
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
std::ostream& operator<<(std::ostream& stream, Polynomial<T>&& poly)
{
    for (size_t i = 0; i < poly.getRang() - 1; i++)
        stream << poly.getCoeff(i) << "*x^" << i << " + ";
    stream << poly.getCoeff(poly.getRang()-1) << "*x^" << poly.getRang() << std::endl;
    return stream;
}

/*
template <typename Poly_type, typename Value_type>
auto evaluate(Polynomial<Poly_type>&& poly, Value_type x)
{

}
/*
template <class Number>
float Polynomial<Number>::evaluate(float x)
{
    double t = 0.0;
    for (int i = n - 1; i >= 0; i--)
        t = t*x + a[i];
    return t;
}

template <class Number>
void Polynomial<Number>::setCoef()
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 10 + 1;
}

template <class Number>
void Polynomial<Number>::setRang(int N)
{
    this->n = N+1;
    delete[] this->a;
    this->a = new Number[N+1];
    for (int i = 0; i < this->n; i++)
    {
        a[i] = 0;
    }
}

template <class Number>
Polynomial<Number>::~Polynomial()
{
    delete[] a;
}

template <class Number>
Polynomial<Number> operator+(Polynomial<Number>& p, Polynomial<Number>& q)
{
    Polynomial<Number> temp(0, p.n > q.n ? p.n-1 : q.n-1);

    for (int i = 0; i < p.n; i++)
        temp.a[i] += p.a[i];

    for (int j = 0; j < q.n; j++)
        temp.a[j] += q.a[j];

    return temp;
}


template <class Number>
bool operator<(Polynomial<Number>& p, Polynomial<Number>& q)
{
    return p.evaluate(p.x) < q.evaluate(q.x) ? true : false;
}

template <class Number>
Polynomial<Number> Polynomial<Number>::operator=(const Polynomial<Number>& p)
{
    if (this != &p)
    {
        assert(this->n == p.n);
        this->n = p.n;

        for (int i = 0; i < p.n; i++)
            this->a[i] = p.a[i];
    }
    return *this;
}
/*
int main(int argc, char const *argv[]) {
    Polynomial<int> p(5, 3);
    Polynomial<int> q(2, 3);
    Polynomial<int> s(0, 5);

    //p.setCoef();
    //q.setCoef();

    cout << p << endl << q << endl << s << endl;
    cout << p.getRang() << endl << q.getRang() << endl << s.getRang() << endl;
    //p.setValue(3);
    //q.setValue(3);

    s = p;
    p = q;
    q = s;
     cout << p << endl << q << endl << s << endl;

    /*cout << p << endl;
    cout << q << endl;
    if (p < q)
        cout << p;
    else
        cout << q;

    return 0;
}*/
    }
}
