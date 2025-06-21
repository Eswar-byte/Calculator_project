#include <bits/stdc++.h>
using namespace std;

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }
double power(double a, double b) { return pow(a, b); }
double squareRoot(double a) { return sqrt(a); }

double getValidatedDouble(string prompt) {
    double num;
    while (true) {
        cout << prompt;
        cin >> num;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        } else {
            return num;
        }
    }
}

int main() {
    char opt;
    bool running = true;
    vector<string> history;

    cout << "==== Advanced C++ Calculator ====\n";
    cout << "Operators: +  -  *  /  ^  r (sqrt)  h (history)  x (exit)\n";

    while (running) {
        cout << "\nEnter an operator: ";
        cin >> opt;

        if (opt == 'x' || opt == 'X') {
            cout << "Exiting calculator. Goodbye!\n";
            break;
        }

        if (opt == 'h' || opt == 'H') {
            cout << "\nCalculation History:\n";
            if (history.empty()) {
                cout << "No calculations performed yet.\n";
            } else {
                for (string entry : history)
                    cout << entry << endl;
            }
            continue;
        }

        double n1 = 0, n2 = 0, result = 0;
        string record;

        if (opt == 'r') {
            n1 = getValidatedDouble("Enter number to find square root: ");
            if (n1 < 0) {
                cout << "Error: Square root of negative number is not real.\n";
                continue;
            }
            result = squareRoot(n1);
            record = "√" + to_string(n1) + " = " + to_string(result);
        } else if (opt == '+' || opt == '-' || opt == '*' || opt == '/' || opt == '^') {
            n1 = getValidatedDouble("Enter first number: ");
            n2 = getValidatedDouble("Enter second number: ");

            switch (opt) {
                case '+':
                    result = add(n1, n2);
                    record = to_string(n1) + " + " + to_string(n2) + " = " + to_string(result);
                    break;
                case '-':
                    result = subtract(n1, n2);
                    record = to_string(n1) + " - " + to_string(n2) + " = " + to_string(result);
                    break;
                case '*':
                    result = multiply(n1, n2);
                    record = to_string(n1) + " * " + to_string(n2) + " = " + to_string(result);
                    break;
                case '/':
                    while (n2 == 0.0) {
                        cout << "Division by zero is not allowed.\n";
                        n2 = getValidatedDouble("Please enter a non-zero divisor: ");
                    }
                    result = divide(n1, n2);
                    record = to_string(n1) + " / " + to_string(n2) + " = " + to_string(result);
                    break;
                case '^':
                    result = power(n1, n2);
                    record = to_string(n1) + " ^ " + to_string(n2) + " = " + to_string(result);
                    break;
            }
        } else {
            cout << "Invalid operator. Try again.\n";
            continue;
        }

        cout << "Result: " << result << endl;
        history.push_back(record);
    }

    return 0;
}
