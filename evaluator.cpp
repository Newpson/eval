#include <iostream>

#include <cctype>
#include <string>
#include <vector>
#include <charconv>

#include "evaluator.h"
#include "evaluable.h"
#include "evaluator-default_library.h"
#include "tokens.h"

#include <cassert>

bool Evaluator::iscallable(const Evaluable::Type type)
{
    return (type == Evaluable::Type::OPERATOR || type == Evaluable::Type::FUNCTION);
}

bool Evaluator::Comparator::operator()(const std::string &str, const std::string_view strview) const
{
    return str == strview;
}

bool Evaluator::Comparator::operator()(const std::string_view strview, const std::string &str) const
{
    return strview == str;
}

bool Evaluator::Comparator::operator()(const std::string &a, const std::string &b) const
{
    return a == b;
}

std::size_t Evaluator::Hasher::operator()(const std::string &str) const
{
    return std::hash<std::string>{}(str);
}

std::size_t Evaluator::Hasher::operator()(const std::string_view strview) const
{
    return std::hash<std::string_view>{}(strview);
}

double Evaluator::eval(const std::string &expression, const library_t &library)
{
    std::string packed(expression);
    std::erase_if(packed, [](unsigned char x) { return std::isspace(x); });

    // FIXME extreme bullshit (hardcoded delimiters)
    // [generate delimiters from OPERATOR | PARENTHESIS_* | COMMA]
    // [maybe combine OPERATOR and FUNCTION into single type]
    const auto tokens = tokenize(packed, "+-*/(),^");

    Evaluable::arg_stack_t args;
    Evaluable::eval_stack_t evals;

    for (const std::string_view &token: tokens)
    {
        if (std::isdigit(token[0])) {
            double value;
            std::from_chars(token.begin(), token.end(), value);
            // TODO check std::from_chars_result
            args.push(value);
        }
        else if (library.contains(token))
        {
            // TODO check if found (merge with whole `else if` branch)
            auto current = library.find(token)->second;
            switch (current->type)
            {
            case Evaluable::Type::VARIABLE:
                args.push(current->eval(args, evals));
                break;
            case Evaluable::Type::FUNCTION:
                [[ fallthrough ]];
            case Evaluable::Type::OPERATOR:
            {
                auto top = evals.empty() ? nullptr : evals.top();
                while (top != nullptr && iscallable(top->type) && top->priority >= current->priority)
                {
                    args.push(top->eval(args, evals));
                    evals.pop(); // pop just evaluated operator
                    top = evals.empty() ? nullptr : evals.top();
                }
                evals.push(current);
                break;
            }
            case Evaluable::Type::PARENTHESIS_LEFT:
                evals.push(current);
                [[ fallthrough ]];
            case Evaluable::Type::COMMA:
                break;
            case Evaluable::Type::PARENTHESIS_RIGHT:
                current->eval(args, evals);
                break;
            default:
                // FIXME extreme bullshit (cerr debugging)
                std::cerr << "Bullshit happens (can't evaluate)" << std::endl;
                return 0.0;
            }
        } else
        {
            // FIXME extreme bullshit (cerr debugging)
            std::cerr << "Bullshit happens (uknown token)" << std::endl;
            return 0.0;
        }
    }

    while (!evals.empty()) {
        args.push(evals.top()->eval(args, evals));
        evals.pop();
    }

    assert(args.size() != 0);
    return args.top();
}

const Evaluator::library_t Evaluator::default_library = {
    {"(", std::shared_ptr<Evaluable>(new parenthesis_left())},
    {")", std::shared_ptr<Evaluable>(new parenthesis_right())},
    {",", std::shared_ptr<Evaluable>(new comma())},
    {"+", std::shared_ptr<Evaluable>(new op_plus())},
    {"-", std::shared_ptr<Evaluable>(new op_minus())},
    {"*", std::shared_ptr<Evaluable>(new op_asterisk())},
    {"/", std::shared_ptr<Evaluable>(new op_slash())},
    {"^", std::shared_ptr<Evaluable>(new op_caret())},
};
