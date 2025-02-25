#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "evaluable.h"

class Evaluator
{
public:
    struct Comparator
    {
        using is_transparent = void;
        bool operator()(const std::string &a, const std::string &b) const;
        bool operator()(const std::string &str, const std::string_view strview) const;
        bool operator()(const std::string_view strview, const std::string &str) const;
    };

    struct Hasher
    {
        using is_transparent = void;
        std::size_t operator()(const std::string &str) const;
        std::size_t operator()(const std::string_view strview) const;
    };

    using library_t = std::unordered_map<
        std::string, std::shared_ptr<Evaluable>,
        Hasher, Comparator>;
    static const library_t default_library;

    static double eval(const std::string &expression, const library_t &library = default_library);
protected:
    static bool iscallable(const Evaluable::Type type);
};
