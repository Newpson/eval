#include <iostream>
#include <string>

#include "evaluator.h"

int main()
{
    std::string expression("1.0 - sin(2^(sin(4)))");
    Evaluator evaluator;
    double value = evaluator.eval(expression);
    std::cout << value << std::endl;

    return 0;
}
