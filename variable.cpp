#include "variable.h"

Variable::Variable(double value):
    value(value), Evaluable(Type::VARIABLE)
{}

double Variable::eval(arg_stack_t &args, eval_stack_t &evals) const
{
    return value;
}
