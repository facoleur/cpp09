// main.cpp

#include "header.hpp"

bool isOperator(const char c, const std::string &operators) {
  return operators.find_first_of(c) != std::string::npos;
}

int pop(std::stack<int> &stack) {
  if (stack.empty())
    throw std::runtime_error("Error: stack can't be empty");

  int res = stack.top();
  stack.pop();

  return res;
}

int calculator(const std::string &input) {

  std::stack<int> stack;

  const std::string operators = "+-*/";

  for (size_t i = 0; i < input.length(); i++) {
    if (i < 2 && isOperator(input[i], operators)) {
      throw std::runtime_error("Error: unexpected operator " +
                               std::string(1, input[i]));
    }

    if (!isdigit(input[i]) && !isOperator(input[i], operators)) {
      throw std::runtime_error("Error: unexpected token " +
                               std::string(1, input[i]));
    }

    if (std::isdigit(input[i])) {
      stack.push(input[i] - '0');
    } else {
      char op = input[i];

      int b = pop(stack);
      int a = pop(stack);

      switch (op) {
      case '+':
        stack.push(a + b);
        break;

      case '-':
        stack.push(a - b);
        break;

      case '*':
        stack.push(a * b);
        break;

      case '/':
        if (b == 0)
          throw std::runtime_error("Error: divider can't be 0");
        stack.push(a / b);
        break;

      default:
        throw std::runtime_error("Error: unexpected token " +
                                 std::string(1, op));
        break;
      }
    }
  }

  if (stack.size() != 1) {
    std::cout << stack.size() << std::endl;
    throw std::runtime_error("Error: stack size should be 1");
  }

  return stack.top();
}

int main(int argc, char const *argv[]) {
  if (argc != 2)
    return 1;

  std::string input = std::string(argv[1]);
  input = removeAllWhitespace(input);

  try {
    int result = calculator(removeAllWhitespace(input));

    std::cout << result << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
