#include <iostream>
#include <string>

using std::string;

class WorkException
{
private:
    string msg;
public:
    WorkException(string new_msg)
        : msg(new_msg)
    {}

    string getMsg() const { return msg; }

    virtual string what()
    {
        return msg;
    }
};

class StackException
    : public WorkException
{
public:
    StackException(string new_msg)
        : WorkException(new_msg)
    {}

    virtual string what()
    {
        return getMsg();
    }
};
