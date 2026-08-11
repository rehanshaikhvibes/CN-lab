#include <iostream>
#include <string>
using namespace std;

string pol2binary(){
    
}

//XOR division - like subtraction we do in normal division
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
    
    //Yaha we used 0's bcoz last no is stillnot processed
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
    cout << "Enter data bits: ";
    cin >> data;
    cout << "Enter generator polynomial (e.g., 1101 for CRC-3): ";
    cin >> poly;

    string appended_zeros(poly.length() - 1, '0');
    string appended_data = data + appended_zeros;

    string remainder = mod2div(appended_data, poly);
    cout << "\nCalculated CRC Checksum: " << remainder << "\n";

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

    string recv_remainder = mod2div(recv_codeword, poly);
    
    // If the remainder contains any '1', an error occurred
    if (recv_remainder.find('1') != string::npos) {
        cout << "Error detected!" << recv_remainder << "\n";
    } else {
        cout << "No error detected.\n";
    }

    return 0;
}