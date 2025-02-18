#include "evaluable.h"

Evaluable::Evaluable(const Type type, const int priority):
    type(type), priority(priority)
{}

double Evaluable::pull_arg(arg_stack_t &args) const
{
    double value = args.top();
    args.pop();
    return value;
}

double Evaluable::eval(arg_stack_t &args, eval_stack_t &evals) const
{
    return 0.0;
}
