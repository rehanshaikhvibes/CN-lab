#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long calculateX10(string equation) {
    // Step 1: Clean the input
    // Remove spaces
    equation.erase(remove(equation.begin(), equation.end(), ' '), equation.end());
    // Remove '^' just in case they typed "x^4"
    equation.erase(remove(equation.begin(), equation.end(), '^'), equation.end());
    // Convert any capital 'X' to lowercase 'x'
    transform(equation.begin(), equation.end(), equation.begin(), ::tolower);

    // Step 2: Split the equation by the '+' sign
    vector<string> terms;
    stringstream ss(equation);
    string term;
    
    while (getline(ss, term, '+')) {
        terms.push_back(term);
    }

    long long total = 0;

    // Step 3: Evaluate each term with x = 10
    for (const string& t : terms) {
        if (t == "1") {
            total += 1;
        } else if (t == "x") {
            total += 10;
        } else if (!t.empty() && t[0] == 'x') {
            // Extract the number after 'x' using substring
            int power = stoi(t.substr(1));
            
            // Calculate 10 to that power (cast to long long to handle big numbers)
            total += (long long)pow(10, power);
        }
    }

    return total;
}

int main() {
    string userInput;
    
    cout << "Enter your polynomial (e.g., x4 + x + 1): ";
    // Use getline to capture spaces in the user's input
    getline(cin, userInput);

    long long result = calculateX10(userInput);

    cout << "Result when x = 10: " << result << endl;

    return 0;
}