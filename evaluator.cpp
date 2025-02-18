#include <iostream>

#include <cctype>
#include <string>
#include <vector>

#include "evaluator.h"
#include "evaluable.h"
#include "evaluator-default_library.h"
#include "tokens.h"

double Evaluator::eval(const std::string &expression, const library_t &library)
{
    std::string packed(expression);
    std::erase_if(packed, [](unsigned char x) { return std::isspace(x); });
    packed.insert(packed.begin(), '(');
    packed += ')';

    // FIXME extreme bullshit (hardcoded delimiters)
    const auto tokens = tokenize(packed, "+-*/(),^");
    Evaluable::arg_stack_t args;
    Evaluable::eval_stack_t evals;

    for (const std::string_view &token: tokens)
    {
        // FIXME extreme bullshit (create string from string_view to match unordered_map.push call)
        std::string token_str(token);
        if (std::isdigit(token_str[0]))
        {
            args.push(std::stod(token_str));
        }
        else if (library.contains(token_str))
        {
            auto current = library.at(token_str);
            switch (current->type)
            {
            case Evaluable::Type::VARIABLE:
                args.push(current->eval(args, evals));
                break;
            case Evaluable::Type::FUNCTION:
                evals.push(current);
                break;
            case Evaluable::Type::OPERATOR:
            {
                auto top = evals.empty() ? nullptr : evals.top();
                if (top != nullptr && top->type == Evaluable::Type::OPERATOR && top->priority >= current->priority)
                {
                    args.push(top->eval(args, evals));
                    evals.pop(); // pop just evaluated operator
                }
                evals.push(current);
                break;
            }
            case Evaluable::Type::PARENTHESIS_LEFT:
            case Evaluable::Type::COMMA:
                evals.push(current);
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
