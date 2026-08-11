#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long calculateX10(string equation) {
    equation.erase(remove(equation.begin(), equation.end(), ' '), equation.end());
    equation.erase(remove(equation.begin(), equation.end(), '^'), equation.end());
    transform(equation.begin(), equation.end(), equation.begin(), ::tolower);

    vector<string> terms;
    stringstream ss(equation);
    string term;
    
    while (getline(ss, term, '+')) {
        terms.push_back(term);
    }
    long long total = 0;
    for (const string& t : terms) {
        if (t == "1") {
            total += 1;
        } else if (t == "x") {
            total += 10;
        } else if (!t.empty() && t[0] == 'x') {
            int power = stoi(t.substr(1));
            total += (long long)pow(10, power);
        }
    }

    return total;
}

// XOR division - like subtraction we do in normal division
string xor_func(string a, string b) {
    string result = "";
    // Skip the first bit as it's always 0 after XOR in this context
    for (size_t i = 1; i < b.length(); i++) {
        if (a[i] == b[i]) {
            result += "0";
        } else {
            result += "1";
        }
    }
    return result;
}

// Performs Modulo-2 division (XOR division).
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick); //grab 1st 4 bits
    
    // Here we use 0's because last no is still not processed
    string zeros(divisor.length(), '0');

    while (pick < dividend.length()) {
        if (tmp[0] == '1') {
            tmp = xor_func(divisor, tmp) + dividend[pick];
        } else {
            tmp = xor_func(zeros, tmp) + dividend[pick];
        }
        pick += 1;
    }

    // Final step
    if (tmp[0] == '1') {
        tmp = xor_func(divisor, tmp);
    } else {
        tmp = xor_func(zeros, tmp);
    }
    
    return tmp;
}

int main() {
    cout << "\n--- Cyclic Redundancy Check (CRC) ---\n";
    
    string data, poly;
    cout << "Enter data bits (e.g., 100100): ";
    cin >> data;
    
    // FIX: Updated the prompt to match what the logic actually expects
    cout << "Enter generator polynomial equation (e.g., x3+x+1): ";
    cin >> poly;
    
    // Converts "x3+x+1" to "1011"
    string poly_val = to_string(calculateX10(poly)); 

    // FIX: Use poly_val.length() instead of poly.length()
    string appended_zeros(poly_val.length() - 1, '0');
    string appended_data = data + appended_zeros;

    string remainder = mod2div(appended_data, poly_val);
    cout << "\nBinary Divisor is:       " << poly_val << "\n";
    cout << "Calculated CRC Checksum: " << remainder << "\n";

    string codeword = data + remainder;
    cout << "Transmitted codeword:    " << codeword << "\n";

    cout << "\n--- Receiver Side ---\n";
    string recv_codeword;
    
    cin.ignore();
    
    cout << "Enter received codeword (press Enter to use '" << codeword << "'): ";
    getline(cin, recv_codeword);
    
    if (recv_codeword.empty()) {
        recv_codeword = codeword;
    }

    // FIX: Passed poly_val (e.g., "1011") instead of poly (e.g., "x3+x+1")
    string recv_remainder = mod2div(recv_codeword, poly_val);
    
    // If the remainder contains any '1', an error occurred
    if (recv_remainder.find('1') != string::npos) {
        cout << "Error detected! Remainder: " << recv_remainder << "\n";
    } else {
        cout << "No error detected. Remainder: " << recv_remainder << "\n";
    }

    return 0;
}