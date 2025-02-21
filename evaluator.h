#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "evaluable.h"

class Evaluator
{
public:
    using library_t = std::unordered_map<std::string, std::shared_ptr<Evaluable>>;
    static const library_t default_library;

    static double eval(const std::string &expression, const library_t &library = default_library);
protected:
    static bool iscallable(const Evaluable::Type type);
};
