#include <iostream>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <fstream>
//#include "point.cpp"


namespace My_math
{
    namespace Vec
    {

template <typename T>
class Vector
{
private:
    size_t my_size;         // Размер вектора
    T* data;                // Указатель на соординаты вектора

protected:
    T setX(T n) { data[0] = n; return data[0]; }
    T setY(T n) { data[1] = n; return data[1]; }
    T setZ(T n) { data[2] = n; return data[2]; }

    T getX() const { return data[0]; }
    T getY() const { return data[1]; }
    T getZ() const { return data[2]; }

    auto absVec() const;

public:
    Vector();                                       // Конструктор по умолчанию
    explicit Vector(size_t new_size);               // Конструктор, задающий р-р
    explicit Vector(std::initializer_list<T> list); // Конструктор, задающий координаты

    Vector(Vector<T>&& v);                          // Конструктор перемещения
    Vector& operator=(Vector<T>&& v);               // Перемещающий оператор присваивания

    Vector(const Vector<T>& v);                     // Конструктор копирования
    Vector<T>& operator=(const Vector<T>& v);       // Копирующее присваивание

    virtual ~Vector()
    {
         delete[] data;
         std::cout << "[Vector] Kill.\n";
    }

    T& operator[](size_t i);                        // Операторы доступа
    const T& operator[](size_t i) const;

    size_t getSize() const { return my_size; }      // Вернуть размер вектора

                                                    // Оператор вывода
    template <typename Type>
    friend std::ostream& operator<<(std::ostream& stream, const Vector<Type>& v);

                                                    // Оператор ввода
    template <typename Type>
    friend std::istream& operator>>(std::istream& stream, Vector<Type>& v);

                                                    // Операции с векторами
    template <typename Type>
    friend Vector<Type> operator+(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type>
    friend Vector<Type> operator-(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type, typename Scalar>       // Умножение вектора на число
    friend Vector<Type> operator*(const Scalar n, const Vector<Type>& v);

    template <typename Type>                        // Скалярное произведение векторов
    friend auto dotProductAlg(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type>                        // Векторное произведение векторов
    friend Vector<Type> crossProduct(const Vector<Type>& v, const Vector<Type>& u);

    void fileIn();                         // Чтение из бинарного файла
    void fileInPos(int position);          // Чтение из бинарного файла с указанием позиции
    void fileOut();                        // Запись в бинарный файл
    void fileIn_text();                    // Чтение из текстового файла
    void fileOut_text();                   // Запись в текстовый файл
/*
    static void addVector();
    static void showAll();
    static void writeAll();
    static void readAll();

    void writeAll(ostream&);
    void readAll(istream&);
*/

    struct exceptOut {};                   // Исключения записи
    struct exceptIn {};                    // Исключения чтения
    //struct exceptData {};
};

template <typename T>
Vector<T>::Vector() : my_size(0), data(nullptr) {}

template <typename T>
Vector<T>::Vector(const size_t new_size)
    : my_size(new_size), data(new T[my_size])
{
    for (size_t i = 0; i < my_size; i++)
        *(data+i) = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
    : my_size(list.size()), data(new T[my_size])
{
    size_t i = 0;
    for (const auto& it : list)
    {
        *(data + i) = it;
        i++;
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v)
    : my_size(v.my_size), data(v.data)
{
    v.data = nullptr;
    v.data = 0;

    std::cout << "[Vector] Move constr.\n";
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v)
{
    assert(my_size == v.my_size);
    std::swap(data, v.data);
    std::cout << "[Vector] Move op. =\n";
    return *this;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v)
    : my_size(v.my_size), data(new T[my_size])
{
    std::copy(&v.data[0], &v.data[v.my_size], &data[0]);
    std::cout << "[Vector] Constr. Copy.\n";
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    if (this == &v)
        return *this;

    my_size = v.my_size;
    data = new T[my_size];

    std::copy(&v.data[0], &v.data[v.my_size], &data[0]);
    std::cout << "[Vector] Op. =\n";

    return *this;
}

/*
template <typename T>
int Vector<T>::n;

template <typename T>
Vector<T>* Vector<T>::array[5];

template <typename T>
void Vector<T>::addVector()
{
    size_t rang;
    cout << "Enter a rang of new vector: ";
    Vector<T> temp(rang);
    cin >> temp;
    array[n++] = temp;
}
*/
template <typename T>
const T& Vector<T>::operator[](size_t i) const
{
    assert(i >= 0 && i < this->my_size);
    return this->data[i];
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{
    assert(i >= 0 && i < this->my_size);
    return this->data[i];
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& v)
{
    stream <<"( ";
    for (size_t i = 0; i < v.my_size; i++)
        stream << v.data[i] << " ";
    stream <<") ";

    return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, Vector<T>& v)
{
    std::cout << "Enter coords: \n";
    for (size_t i = 0; i < v.getSize(); i++)
        stream >> v.data[i];

    return stream;
}

template <typename T>
void Vector<T>::fileIn()
{
    try
    {
    T arr[this->my_size];

    std::ifstream in_file;                        // Создать поток ввода из файла.
    in_file.open("Vector.DAT", std::ios::binary); // Открыть поток
    if (!in_file)
    {
        throw exceptIn();
        //return;
    }
    //in_file.seekg(num * sizeof(Vector<T>)); // Сдвиг файлового
                                                    // указателя.
    in_file.read(reinterpret_cast<char*>(arr), this->my_size * sizeof(T));
    in_file.close();

    for (size_t i = 0; i < this->my_size; i++)
    {
        this->data[i] = arr[i];
    }
    }
    catch(exceptIn& ex)
    {
        std::cout << "Input error.\n";
    }
}

template <typename T>
void Vector<T>::fileOut()
{
    try
    {
    T arr[this->my_size];
    for (size_t i = 0; i < this->my_size; i++)
    {
        arr[i] = this->data[i];
    }

    std::ofstream out_file;                     // Создать поток вывода в файл.
                                                // Открыть потко вывода в файл.
    out_file.open("Vector.DAT", std::ios::app | std::ios::binary);
    if (!out_file)
    {
        throw exceptOut();
        //cout << "Errer. Open file.\n";
        //return;
    }
                                                // Запись в файл.
    out_file.write(reinterpret_cast<char*>(arr), this->my_size * sizeof(T));
    out_file.close();
    }
    catch(exceptOut& ex)
    {
        std::cout << "Output error.\n";
    }
}

template <typename T>
void Vector<T>::fileInPos(int position)
{
    T arr[this->my_size];

    std::ifstream in_file("Vector.DAT", std::ios::binary);
    if (!in_file)
    {
        throw exceptIn();
    }

    in_file.seekg(0, std::ios::end);
                                            // Вернуть указатель чтения на конечную позицию
    int endposition = in_file.tellg();
                                            // Найти кол-во векторов в файле
    int n = endposition / sizeof(T);
    std::cout << "In file " << n << " vectors.\n";
                                            // Вычислить позицию для чтения
    int position_in_file = (position-1) * this->my_size * sizeof(T);
    in_file.seekg(position_in_file);        // Установить указатель чтения
    in_file.read(reinterpret_cast<char*>(arr), this->my_size * sizeof(T));
    in_file.close();

    for (size_t i = 0; i < this->my_size; i++)
    {
        this->data[i] = arr[i];
    }
}

template <typename T>
void Vector<T>::fileOut_text()
{
    std::ofstream out_st;
    out_st.open("Vector.txt");
    for (size_t i = 0; i < this->my_size; i++)
        out_st << this->data[i] << " ";
    //out_st << *this;
    out_st.close();
}

template <typename T>
void Vector<T>::fileIn_text()
{
    std::ifstream in_st;
    in_st.open("Vector.txt");
    in_st >> *this;
    in_st.close();
}

template <typename T>
Vector<T> operator+(const Vector<T>& v, const Vector<T>& u)
{
    assert(v.getSize() == u.getSize());
    Vector<T> sum(v.getSize());
    for (size_t i = 0; i < sum.getSize(); i++)
    {
        sum[i] = v[i] + u[i];
    }
    return sum;
}

template <typename T>
Vector<T> operator-(const Vector<T>& v, const Vector<T>& u)
{
    assert(v.getSize() == u.getSize());
    Vector<T> subt(v.getSize());
    for (size_t i = 0; i < subt.getSize(); i++)
        subt[i] = v[i] - u[i];
    return subt;
}

template <typename T, typename Scalar>
Vector<T> operator*(const Scalar n, const Vector<T>& v)
{
    Vector<T> res(v.getSize());
    for (size_t i = 0; i < res.getSize(); i++)
        res[i] = n * v[i];
    return res;
}

template <typename T>
auto dotProductAlg(const Vector<T>& v, const Vector<T>& u)
{
    assert(v.getSize() == u.getSize());
    std::vector<T> res;
    T sum;
    res.resize(v.getSize());
    for (auto& it : res)
        it = v[it] * u[it];
    for (auto& it : res)
        sum = sum + it;
    return sum;
}

template <typename T>
Vector<T> crossProduct(const Vector<T>& v, const Vector<T>& u)
{
    assert(v.getSize() == 3 || u.getSize() == 3);

    return Vector<T>({v[1] * u[2] - v[2] * u[1],
                      v[2] * u[0] - v[0] * u[2],
                      v[0] * u[1] - v[1] * u[0]});
}

template <typename T>
auto Vector<T>::absVec() const
{
     return sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2));
}

    }
}
/*
using Vi = My_math::Vec::Vector<int>;
using Vf = My_math::Vec::Vector<float>;
int main()
{
    Vi v(5); Vf u{1.1, 2.2, 3.5};
    std::cout << v << u;
    return 0;
}*/
