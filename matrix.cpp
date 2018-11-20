#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <typeinfo>
#include <vector>

namespace My_math
{
    namespace Matr
    {

template<typename T>
class Matrix
{
public:

    using value_type = T;

    Matrix();                                    // Конструктор по умолчанию
    Matrix(size_t row, size_t column);           // Конструктор, задающий р-р
    Matrix(const Matrix<T>& ob);                 // Конструктор копирования
    Matrix<T>& operator=(const Matrix<T>& m);    // Копирующее присваивание
    ~Matrix();

    int getRow() const { return row; }           // Вернуть кол-во строк
    int getColumn() const { return column; }     // Вернуть кол-во столбцов

    template <typename Type>                     // Оператор вывода
    friend std::ostream& operator<<(std::ostream& stream, const Matrix<Type>& m);

    const T getData(size_t, size_t) const;       // Вернуть данные в поз. i, j
    T& setData(const size_t, const size_t);      // Установить данные в поз. i, j
    void setElements();
    Matrix<T> transposition(const Matrix<T>& m); // Транспонирование матрицы

private:
    size_t row;                                  // Кол-во строк
    size_t column;                               // Кол-во столбцов
    value_type **data;                           // Указатель на данные матрицы
};

template <typename T>
Matrix<T>::Matrix()
    : row(2), column(2)
{
    data = new value_type*[row];
    for (size_t i = 0; i < row; i++)
        data[i] = new T[column];
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            data[i][j] = 0;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(size_t row, size_t column)
    : row(row), column(column)
{
    data = new value_type*[row];
    for (size_t i = 0; i < row; i++)
        data[i] = new T[column];
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            data[i][j] = 0;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
    : row(m.row), column(m.column)
{
    assert(row == m.row && column == m.column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
    std::cout << "[Matrix] Copy constr.\n";
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    assert(row == m.row && column == m.column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
    std::cout << "[Matrix] Copy op. =\n";
    return *this;
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < row; i++)
        delete[] data[i];

    delete[] data;
    std::cout << "[Matrix] Kill.\n";
}

template <typename T>
const T Matrix<T>::getData(size_t index_row, size_t index_column) const
{
    assert(index_row >= 0 && index_row <= this->row);
    assert(index_column >= 0 && index_column <= this->column);

    return this->data[index_row][index_column];
}

template <typename T>
T& Matrix<T>::setData(const size_t index_row, const size_t index_column)
{
    assert(index_row >= 0 && index_row <= this->row);
    assert(index_column >= 0 && index_column <= this->column);

    return this->data[index_row][index_column];
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>& m)
{
    stream << std::endl;
    for (size_t i = 0; i < m.row; i++)
    {
        stream << "|";
        for (size_t j = 0; j < m.column; j++)
        {
            stream << " " << m.getData(i, j) << " ";
        }
        stream << "|" << std::endl;
    }
    stream << std::endl;
    return stream;
}

template <typename T>
void Matrix<T>::setElements()
{
    for (size_t i = 0; i < this->row; i++)
    {
        for (size_t j = 0; j < this->column; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

template <typename T>
Matrix<T> transposition(const Matrix<T>& m)
{
    Matrix<T> Tm(m.getColumn(), m.getRow());
    for (size_t i = 0; i < Tm.getRow(); i++)
    {
        for (size_t j = 0; j < Tm.getColumn(); j++)
        {
            Tm.setData(i, j) = m.getData(j, i);
        }
    }
    return Tm;
}

template <typename T>
auto operator+(const Matrix<T>& M, const Matrix<T>& N)
{
    assert(M.getRow() == N.getRow() && M.getColumn() == N.getColumn());
    Matrix<T> sum(M.getRow(), M.getColumn());
    for (size_t i = 0; i < sum.getRow(); i++)
    {
        for (size_t j = 0; j < sum.getColumn(); j++)
        {
            sum.setData(i, j) = M.getData(i, j) + N.getData(i, j);
        }
    }
    return sum;
}

template <typename T>
auto operator-(const Matrix<T>& M, const Matrix<T>& N)
{
    assert(M.getRow() == N.getRow() && M.getColumn() == N.getColumn());
    Matrix<T> subt(M.getRow(), M.getColumn());
    for (size_t i = 0; i < subt.getRow(); i++)
    {
        for (size_t j = 0; j < subt.getColumn(); j++)
        {
            subt.setData(i, j) = M.getData(i, j) - N.getData(i, j);
        }
    }
    return subt;
}

template <typename Scalar, typename Value_type>
auto operator*(const Scalar n, const Matrix<Value_type>& m)
{
    Matrix<Value_type> mult(m.getRow(), m.getColumn());
    for (size_t i = 0; i < mult.getRow(); i++)
    {
        for (size_t j = 0; j < mult.getColumn(); j++)
        {
            mult.setData(i, j) = n * m.getData(i,j);
        }
    }
    return mult;
}

template <typename Scalar, typename Value_type>
auto operator*(const Matrix<Value_type>& m, const Scalar n)
{
    Matrix<Value_type> mult(m.getRow(), m.getColumn());
    for (size_t i = 0; i < mult.getRow(); i++)
    {
        for (size_t j = 0; j < mult.getColumn(); j++)
        {
            mult.setData(i, j) = m.getData(i, j) * n;
        }
    }
    return mult;
}

template <typename Value_type>
auto operator*(const Matrix<Value_type>& m, const Matrix<Value_type>& n)
{
    assert(m.getRow() == n.getRow() && m.getColumn() == n.getColumn());
    assert(m.getRow() == m.getColumn() && n.getRow() == n.getColumn());

    Matrix<Value_type> mult(m.getRow(), m.getColumn());
    size_t t = 0;
    for (size_t i = 0; i < mult.getRow(); i++)
    {
        for (size_t j = 0; j < mult.getColumn(); j++)
        {
            while (t < m.getRow())
            {
                mult.setData(i,j) = mult.getData(i,j) + (m.getData(i, t) * n.getData(t,j));
                t++;
            }
            t = 0;
        }
    }
    return mult;
}

    }
}
