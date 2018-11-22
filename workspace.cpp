#include <iostream>
#include <memory>
#include <initializer_list>
#include <stack>
#include "my_math_lib.h"
#include "workexception.cpp"

using VecInt = My_math::Vec::Vector<int>;
using MatrInt = My_math::Matr::Matrix<int>;
using PolyInt = My_math::Poly::Polynomial<int>;
using std::cout;
using std::cin;

//void foo() { cout << "!!!!!!!!!!!!!\n"; }

template <typename T>
void menu(unsigned index)
{
    switch (index)
    {
        case 1:
            cout << "Work with vectors.\n"
                 << "'+' - addition\n'-' - subtraction\n"
                 << "'*' - constant multiplication\n"
                 << "'.' - scalar multiplication\n'x' - vector multiplication\n";
            break;
        case 2:
            cout << "Work with matrix.\n"
                 << "'+' - addition\n'-' - subtraction\n"
                 << "'*' - scalar multiplication\n"
                 << "'x' - matrix multiplication\n't' - transposition\n";
            break;
        case 3:
            cout << "Work with polynomial.\n"
                 << "'+' - addition\n'-' - subtraction\n"
                 << "'*' - scalar multiplication\n"
                 << "'x' - matrix multiplication\n't' - transposition\n";
            break;
    }
}

template <typename Stack_type>
void addVecInStack(std::stack<Stack_type>& stack)
{
    size_t s;
    cout << "Enter vector size:\n";
    cin >> s;
    stack.emplace(VecInt(s));
    //cout << "Enter vector coord:\n";
    cin >> stack.top();
}

template <typename Stack_type>
void addMatrInStack(std::stack<Stack_type>& stack)
{
    size_t i, j;
    cout << "Enter matrix size:\n";
    cin >> i >> j;
    stack.emplace(MatrInt(i, j));
    //cout << "Enter matrix coord:\n";
    //stack.top().setData();
    cin >> stack.top();
}

template <typename T>
void workWithVector()
{
    menu<T>(1);
    std::stack<My_math::Vec::Vector<T>> stack_vec;
    char choice = 'y';
    char op;
    size_t size;
    while (choice == 'y')
    {
        try
        {
        while(choice == 'y')
        {
            cout << "Add vector or operand? v / o\n";
            try
            {
                cin >> choice;
                if (choice != 'v' && choice != 'o')
                    throw WorkException("Error. Invalid character entered\n");
            }
            catch(WorkException& ex)
            {
                cout << ex.what();

                cin >> choice;
            }
                if (choice != 'v' && choice != 'o')
                    throw WorkException("Error. Invalid character again:(\n");

            if (choice == 'v')
            {
                addVecInStack(stack_vec);
            }
            else if (choice == 'o')
            {
                cout << "Enter operator:\n";
                try
                {
                    cin >> op;
                    if (choice != 'v' && choice != 'o')
                        throw WorkException("Error. Invalid character entered\n");
                }
                catch(WorkException& ex)
                {
                    cout << ex.what();
                }
            }
            cout << "Add again? y / n\n";
            try
            {
                cin >> choice;
                if (choice != 'y' && choice != 'n')
                    throw WorkException("Error. Invalid character entered\n");
            }
            catch(WorkException& ex)
            {
                cout << ex.what();
            }
        }
    }
    catch (WorkException& ex)
    {
        cout << "Global. " << ex.what();
    }
        switch (op)
        {
            case '+':
            {
                auto v1 = stack_vec.top(); stack_vec.pop();
                auto v2 = stack_vec.top(); stack_vec.pop();
                v1 = v1 + v2;
                cout << v1;
                break;
            }
            case '-':
            {
                auto v1 = stack_vec.top(); stack_vec.pop();
                auto v2 = stack_vec.top(); stack_vec.pop();
                v1 = v1 - v2;
                cout << v1;
                break;
            }
            case '*':
            {
                auto v = stack_vec.top();
                cout << "Enter scalar:\n";
                float scalar; cin >> scalar;
                v = scalar * v;
                cout << v;
                break;
            }
        }
        cout << "Do you continue? y / n\n";
        try
        {
            cin >> choice;
            if (choice != 'y' && choice != 'n')
                throw WorkException("Error. Invalid character entered\n");
        }
        catch(WorkException& ex)
        {
            cout << ex.what();
        }
    }


}

template <typename T>
void workWithMatrix()
{
    menu<T>(2);
    std::stack<My_math::Matr::Matrix<T>> stack_matr;
    char choice = 'y';
    char op;
    size_t size;
    while (choice == 'y')
    {
        while(choice == 'y')
        {
            cout << "Add matrix or operand? m / o\n";
            cin >> choice;
            if (choice == 'm')
            {
                addMatrInStack(stack_matr);
            }
            else if (choice == 'o')
            {
                cout << "Enter operator:\n";
                cin >> op;
            }
            cout << "Add again? y / n\n"; cin >> choice;
        }

        switch (op)
        {
            case '+':
            {
                auto M1 = stack_matr.top(); stack_matr.pop();
                auto M2 = stack_matr.top(); stack_matr.pop();
                M1 = M1 + M2;
                cout << M1;
                break;
            }
            case '-':
            {
                auto M1 = stack_matr.top(); stack_matr.pop();
                auto M2 = stack_matr.top(); stack_matr.pop();
                M1 = M1 - M2;
                cout << M1;
                break;
            }
            case '*':
            {
                auto M = stack_matr.top();
                cout << "Enter scalar:\n";
                float scalar; cin >> scalar;
                M = scalar * M;
                cout << M;
                break;
            }
            case 'x':
            {
                auto M1 = stack_matr.top(); stack_matr.pop();
                auto M2 = stack_matr.top(); stack_matr.pop();
                M1 = M1 * M2;
                cout << M1;
                break;
            }
            case 't':
            {
                cout << My_math::Matr::transposition<T>(stack_matr.top());
                break;
            }
        }
        cout << "Do you continue?\n"; cin >> choice;
    }
}
