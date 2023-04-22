#include <exceptions>

using namespace std;

class VariableNotExist : public exception
{
public:
    VariableNotExist(const char *msg) : exception(), msg_(msg){};
    const char *what() const throw()
    {
        return msg_;
    }

private:
    const char *msg_;
};

class StrategyNotExist : public exception
{
public:
    StrategyNotExist(const char *msg) : exception(), msg_(msg){};
    const char *what() const throw()
    {
        return msg_;
    }

private:
    const char *msg_;
};