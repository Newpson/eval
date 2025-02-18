#pragma once

#include "evaluable.h"

struct Variable: public Evaluable
{
    double value;
    Variable(double value = 0.0);
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override;
};
