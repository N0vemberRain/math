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
    size_t my_size;
    T* data;

    //static unsigned int n;      // Текущее число векторов
    //static Vector* array[];     // Массив указателей на векторы

    //unsigned int n = 0;

protected:
    T setX(T n) { data[0] = n; return data[0]; }
    T setY(T n) { data[1] = n; return data[1]; }
    T setZ(T n) { data[2] = n; return data[2]; }

    T getX() const { return data[0]; }
    T getY() const { return data[1]; }
    T getZ() const { return data[2]; }

    auto absVec() const;

public:
    Vector() : my_size(0), data(nullptr) {}
    Vector(size_t new_size)
        : my_size(new_size), data(new T[my_size])
    {
        for (size_t i = 0; i < my_size; i++)
            *(data+i) = 0;
    }

    Vector(std::initializer_list<T> list)
        //: my_size(list.size()), coords(new T[my_size])
    {
        my_size = list.size();
        data = new T[my_size];
        size_t i = 0;
        for (const auto& it : list)
        {
            *(data + i) = it;
            i++;
        }
    }

    Vector(Vector<T>&& v)               // Конструктор перемещения
        : my_size(v.my_size), data(v.data)
    {
        v.data = nullptr;
        v.data = 0;

        std::cout << "[Vector] Move constr.\n";
    }

    Vector& operator=(Vector<T>&& v)    // Перемещающий оператор присваивания
    {
        assert(my_size == v.my_size);

        std::swap(data, v.data);
        std::cout << "[Vector] Move op. =\n";
        return *this;
    }
    /*
    Vector(const Vector<T>& v)
        : my_size(v.my_size), data(new T[my_size])
    {
        //for (size_t i = 0; i < my_size; i++)
        //    data[i] = v.data[i];

        std::copy(&v.data[0], &v.data[v.my_size], &data[0]);

        cout << "[Vector] Constr. Copy.\n";
    }

    Vector<T>& operator=(const Vector<T>& v)
    {
        if (this == &v)
            return *this;

        my_size = v.my_size;
        data = new T[my_size];

        //for (size_t i = 0; i < my_size; i++)
        //    data[i] = v.data[i];
        std::copy(&v.data[0], &v.data[v.my_size], &data[0]);
        cout << "[Vector] Op. =\n";

        return *this;
    }
*/
    virtual ~Vector()
    {
         delete[] data;
         std::cout << "[Vector] Kill.\n";
    }

    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    const T at(size_t i) const;

    size_t getSize() const { return my_size; }

    template <typename Type>
    friend std::ostream& operator<<(std::ostream& stream, const Vector<Type>& v);

    template <typename Type>
    friend std::istream& operator>>(std::istream& stream, Vector<Type>& v);

    template <typename Type>
    friend Vector<Type> operator+(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type>
    friend Vector<Type> operator-(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type, typename Num>
    friend Vector<Type> operator*(const Num n, const Vector<Type>& v);

    template <typename Type>
    friend auto dotProductAlg(const Vector<Type>& v, const Vector<Type>& u);

    template <typename Type>
    friend Vector<Type> crossProduct(const Vector<Type>& v, const Vector<Type>& u);

    void fileIn();
    void fileInPos(int position);
    void fileOut();
    void fileIn_text();
    void fileOut_text();
/*
    static void addVector();
    static void showAll();
    static void writeAll();
    static void readAll();

    void writeAll(ostream&);
    void readAll(istream&);
*/

    struct exceptOut {};
    struct exceptIn {};
    struct exceptData {};




};

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
const T Vector<T>::at(size_t i) const
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
    std::cout << "Enter coords: ";
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

    std::ifstream in_file;     // Создать поток ввода из файла.
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

    std::ofstream out_file;   // Создать поток вывода в файл.
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
    in_file.seekg(position_in_file); // Установить указатель чтения
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
    /*
    try
    {
        if (v.getSize() != u.getSize())
            throw exceptData<T>();
    }
    catch (Vector<T>::exceptData<T>())
    {
        cerr << "Error: size is different.\n";
    }
*/
    assert(v.getSize() == u.getSize());
    Vector<T> sum(v.getSize());
    for (size_t i = 0; i < sum.getSize(); i++)
    {
        sum[i] = v.at(i) + u.at(i);
    }
    return sum;
}

template <typename T>
Vector<T> operator-(const Vector<T>& v, const Vector<T>& u)
{
    /*
    try
    {
        if (v.getSize() != u.getSize())
            throw Vector<T>::exceptData<T>();
    }
    catch (Vector<T>::exceptData<T>())
    {
        cerr << "Error: size is different.\n";
    }
*/
    assert(v.getSize() == u.getSize());
    Vector<T> subt(v.getSize());
    for (size_t i = 0; i < subt.getSize(); i++)
        subt[i] = v[i] - u[i];
    return subt;
}

template <typename T, typename Num>
Vector<T> operator*(const Num n, const Vector<T>& v)
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

template <typename T>
auto simpleFoo(Vector<T> v)
{
    std::cout << v << "Simple Foo\n";
    return v;
}
/*
template <typename T>
auto createVector(Vector<T>&& v)
{
    return Vector<T>(std::move(v));
}

template <typename T>
auto createVector(const Vector<T> v)
{
    return
}
*/
}
}
