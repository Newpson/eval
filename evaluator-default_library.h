#pragma once

#include <cmath>

#include "evaluable.h"

/* priority (descending):
   ( ) ,
   func
   ^
   * /
   + -
*/

class parenthesis_left: public Evaluable
{
public:
    parenthesis_left(): Evaluable(Type::PARENTHESIS_LEFT) {}
};

class parenthesis_right: public Evaluable
{
public:
    parenthesis_right(): Evaluable(Type::PARENTHESIS_RIGHT) {}

    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        while (!evals.empty() && evals.top()->type != Type::PARENTHESIS_LEFT) {
            args.push(evals.top()->eval(args, evals));
            evals.pop();
        }
        if (!evals.empty())
            evals.pop(); // pop "("
        return 0.0;
    }
};

class comma: public Evaluable
{
public:
    comma(): Evaluable(Type::COMMA) {}
};

class op_plus: public Evaluable
{
public:
    op_plus(): Evaluable(Type::OPERATOR, PRIORITY_MAX - 4) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        return pull_arg(args) + pull_arg(args);
    }
};

class op_minus: public Evaluable
{
public:
    op_minus(): Evaluable(Type::OPERATOR, PRIORITY_MAX - 4) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        double right = pull_arg(args);
        double left = pull_arg(args);
        return left - right;
    }
};

class op_asterisk: public Evaluable
{
public:
    op_asterisk(): Evaluable(Type::OPERATOR, PRIORITY_MAX - 3) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        return pull_arg(args) * pull_arg(args);
    }
};

class op_slash: public Evaluable
{
public:
    op_slash(): Evaluable(Type::OPERATOR, PRIORITY_MAX - 3) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        double right = pull_arg(args);
        double left = pull_arg(args);
        return left / right;
    }
};

class op_caret: public Evaluable
{
public:
    op_caret(): Evaluable(Type::OPERATOR, PRIORITY_MAX - 2) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        double exponent = pull_arg(args);
        double base = pull_arg(args);
        return std::pow(base, exponent);
    }
};
