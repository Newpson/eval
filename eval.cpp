#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <cctype>
#include <unordered_map>
#include <algorithm>

class Evaluator
{
public:
    class Evaluable
    {
    public:
        enum class Type
        {
            UNDEFINED,
            LITERAL,
            VARIABLE,
            PARENTHESIS_LEFT,
            PARENTHESIS_RIGHT,
            COMMA,
            OPERATOR,
            FUNCTION,
        };

        enum class Priority
        {
            MIN = 0,
            MAX = 10,
        };

        Evaluable(const Type type = Type::UNDEFINED, const Priority priority = Priority::MAX):
            type(type), priority(priority)
        {}

        virtual double eval() = 0;
        const Type type;
        const Priority priority;
    };
private:
    std::unordered_map<std::string, Evaluable> library;
};

class Sine: public Evaluator::Evaluable
{
public:
    Sine(): Evaluable(Type::FUNCTION, Priority::MAX)
    {}

    virtual double eval() override
    {
        return std::sin();
    }
};

static bool is_delimiter(const char c, const std::string &delimiters)
{
    for (const char d : delimiters)
        if (c == d)
            return true;
    return false;
}

std::vector<std::string_view> tokenize(const std::string &string, const std::string &delimiters)
{
    std::vector<std::string_view> tokens;
    std::string::const_iterator token_begin = string.begin();
    for (auto string_iter = string.begin(); string_iter != string.end(); ++string_iter) {
        if (is_delimiter(*string_iter, delimiters)) {
            std::string::const_iterator token_end = string_iter;
            if (token_end - token_begin > 0)
                tokens.push_back(std::string_view(token_begin.base(), token_end.base()));
            tokens.push_back(std::string_view(string_iter.base(), 1));
            token_begin = token_end + 1;
        }
    }
    return tokens;
}

int main()
{
    std::string equation("sin(x - sin(2 * pow(1 + 3 + 4.88 / 45 - 9, 0.33 - x)) + sin(1 + 3.1415 / x)");
    equation.erase(std::remove_if(equation.begin(), equation.end(), [](unsigned char x) { return std::isspace(x); }), equation.end());
    auto tokens = tokenize(equation, "+-*/(),");

    for (const std::string_view &token : tokens)
        std::cout << token;
    std::cout << std::endl;

    return 0;
}
