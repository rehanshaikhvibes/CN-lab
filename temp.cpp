#include <iostream>
#include <cmath> // Required library for pow()

int main() {
    double x = 2.5;
    
    // Calculates x to the power of 4
    double result = std::pow(x, 4); 
    
    std::cout << "Result: " << result << std::endl;
    return 0;
}
