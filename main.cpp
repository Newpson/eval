#include <iostream>
#include <string>
#include <memory>

#include <cmath>
#include "evaluable.h"
#include "variable.h"
#include "evaluator.h"

class func_sin: public Evaluable
{
public:
    func_sin(): Evaluable(Type::FUNCTION, PRIORITY_MAX-1) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        return std::sin(pull_arg(args));
    }
};

int main()
{
    std::shared_ptr<Variable> x(new Variable());
    Evaluator::library_t library = {
        {"sin", std::shared_ptr<Evaluable>(new func_sin())},
        {"x", x},
    };
    library.insert(Evaluator::default_library.begin(), Evaluator::default_library.end());

    x->value = 3.1415;
    std::cout << Evaluator::eval("sin(x)", library) << std::endl;
    x->value = 4.14;
    std::cout << Evaluator::eval("sin(x)", library) << std::endl;

    return 0;
}
