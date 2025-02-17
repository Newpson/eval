// #include "evaluator.h"
#include <iostream>

float a()
{
    return 1.0;
}

float b()
{
    return 2.0;
}

int main()
{
    std::string equation("sin(x - sin(2 * pow(1 + 3 + 4.88 / 45 - 9, 0.33 - x)) + sin(1 + 3.1415 / x)");

    // Evaluator evaluator;
    // double value = evaluator.eval(equation);

    // std::cout << value << std::endl;
    return 0;
}
