#pragma once

#include <cmath>
#include <stack>
#include <string>
#include <unordered_map>
#include "evaluable.h"

class Evaluator
{
public:
    Evaluator() = default;

    double eval(const std::string &expression);
    void add_evaluable(const std::string &name, const Evaluable *evaluable);
    void set_library(std::unordered_map<std::string, Evaluable *> &library);

private:
    std::unordered_map<const std::string, const Evaluable *> library;
    std::stack<double> arguments;
    std::stack<Evaluable> evaluables;
};
