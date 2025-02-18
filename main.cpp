#include <iostream>
#include <string>

#include <cmath>

#include "evaluator.h"

class func_sin: public Evaluable
{
public:
    func_sin(): Evaluable(Type::FUNCTION, PRIORITY_MAX - 1) {}
    virtual double eval(arg_stack_t &args, eval_stack_t &evals) const override
    {
        return std::sin(pull_arg(args));
    }
};

int main()
{

    std::string expression("1.0 - sin(2^(sin(4)))");
    Evaluator::library_t extension = {
        {"sin", std::shared_ptr<Evaluable>(new func_sin())}
    };
    // FIXME extreme bullshit (std::unordered map can't merge with const (WTF?) so we create a copy)
    // extension.merge(Evaluator::default_library);
    Evaluator::library_t library(Evaluator::default_library);

    library.merge(extension);
    double value = Evaluator::eval(expression, library);
    std::cout << value << std::endl;

    return 0;
}
