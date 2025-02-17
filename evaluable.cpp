#include "evaluable.h"

Evaluable::Evaluable(
    const Type type, const Priority priority):
    type(type), priority(priority)
{}

double Evaluable::pull(std::stack<double> &args)
{
    double value = args.top();
    args.pop();
    return value;
}

bool Evaluable::operator==(const Evaluable &evaluable)
{
    return this == &evaluable;
}
