#include <cctype>
#include <cmath>
#include <stack>
#include <string>
#include <vector>

#include "evaluator.h"
#include "tokens.h"

double Evaluator::eval(const std::string &expression)
{
    std::string packed(expression);
    std::erase_if(packed, [](unsigned char x) { return std::isspace(x); });

    auto tokens = tokenize(packed, "+-*/(),");

    return -1.0;
}

void Evaluator::add_evaluable(
        const std::string &name,
        const Evaluable *evaluable)
{
    library.insert({name, evaluable});
}
