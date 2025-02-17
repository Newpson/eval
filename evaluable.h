#include <stack>

class Evaluable
{
public:
    enum class Type
    {
        UNDEFINED,
        LITERAL,
        VARIABLE,
        PARENTHESIS_LEFT,
        PARENTHESIS_RIGHT,
        COMMA,
        OPERATOR,
        FUNCTION,
    };

    enum class Priority
    {
        MIN = 0,
        MAX = 10,
    };

    Evaluable(const Type type = Type::UNDEFINED, const Priority priority = Priority::MAX);

    virtual double eval(std::stack<double> &args) = 0;
    const Type type;
    const Priority priority;

    bool operator==(const Evaluable &evaluable);

protected:
    double pull(std::stack<double> &args);
};
