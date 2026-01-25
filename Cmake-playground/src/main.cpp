#include <iostream>

int main() {
    double num1, num2;
    char op;

    std::cout << "Simple C++ Calculator" << std::endl;
    std::cout << "Enter an expression (e.g., 4 + 5): ";
    std::cin >> num1 >> op >> num2;

    switch(op) {
        case '+':
            std::cout << "Result: " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << "Result: " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << "Result: " << num1 * num2 << std::endl;
            break;
        case '/':
            if(num2 != 0)
                std::cout << "Result: " << num1 / num2 << std::endl;
            else
                std::cout << "Error: Division by zero!" << std::endl;
            break;
        default:
            std::cout << "Invalid operator!" << std::endl;
    }

    return 0;
}
