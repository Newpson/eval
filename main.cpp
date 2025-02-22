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
    Evaluator::library_t extension = {
        {"sin", std::shared_ptr<Evaluable>(new func_sin())},
        {"x", std::shared_ptr<Variable>(new Variable())},
    };
    // FIXME extreme bullshit (std::unordered map can't merge with const (WTF?) so we create a copy)
    // extension.merge(Evaluator::default_library);
    Evaluator::library_t library(Evaluator::default_library);
    library.merge(extension);

    std::string expression("2*2 - sin(2*2)^2 + 1");
    std::cout << "Value: " << Evaluator::eval(expression, library) << std::endl;
    return 0;
}
