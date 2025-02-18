#pragma once

#include <stack>
#include <memory>

class Evaluable
{
public:
    using arg_stack_t = std::stack<double>;
    using eval_stack_t = std::stack<std::shared_ptr<Evaluable>>;

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

    Evaluable(const Type type = Type::UNDEFINED, const int priority = PRIORITY_MAX);

    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const;
    const Type type;
    const int priority;

    static constexpr int PRIORITY_MIN = 0;
    static constexpr int PRIORITY_MAX = 10;

protected:
    double pull_arg(arg_stack_t &args) const;
};
