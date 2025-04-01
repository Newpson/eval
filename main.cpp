#include <iostream>
#include <memory>
#include <string>

#include "evaluator.h"
#include "variable.h"

int main()
{
    std::shared_ptr<Variable> x(new Variable());
    Evaluator::library_t library = {
        {"x", x},
    };
    library.insert(Evaluator::default_library.begin(), Evaluator::default_library.end());

    x->value = 3.1415;
    std::cout << Evaluator::eval("sin(x)", library) << std::endl;
    x->value = 4.14;
    std::cout << Evaluator::eval("sin(x)", library) << std::endl;

    return 0;
}
