// turkish_crypto.cpp

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>
#include <clocale>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "turkish_crypto.h"

using namespace std;

    unordered_map<char, int> char_to_int = {
        {'a', 0}, {'b', 1}, {'c', 2}, {'ç', 3}, {'d', 4}, {'e', 5},
        {'f', 6}, {'g', 7}, {'ð', 8}, {'h', 9}, {'ý', 10}, {'i', 11},
        {'j', 12}, {'k', 13}, {'l', 14}, {'m', 15}, {'n', 16}, {'o', 17},
        {'ö', 18}, {'p', 19}, {'r', 20}, {'s', 21}, {'þ', 22}, {'t', 23},
        {'u', 24}, {'ü', 25}, {'v', 26}, {'y', 27}, {'z', 28}
    };

    unordered_map<int, char> int_to_char = {
        {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'ç'}, {4, 'd'}, {5, 'e'},
        {6, 'f'}, {7, 'g'}, {8, 'ð'}, {9, 'h'}, {10, 'ý'}, {11, 'i'},
        {12, 'j'}, {13, 'k'}, {14, 'l'}, {15, 'm'}, {16, 'n'}, {17, 'o'},
        {18, 'ö'}, {19, 'p'}, {20, 'r'}, {21, 's'}, {22, 'þ'}, {23, 't'},
        {24, 'u'}, {25, 'ü'}, {26, 'v'}, {27, 'y'}, {28, 'z'}
    };

    unordered_map<char, char> to_lower_map = {
        {'A', 'a'}, {'B', 'b'}, {'C', 'c'}, {'Ç', 'ç'}, {'D', 'd'}, {'E', 'e'},
        {'F', 'f'}, {'G', 'g'}, {'Ð', 'ð'}, {'H', 'h'}, {'I', 'ý'}, {'Ý', 'i'},
        {'J', 'j'}, {'K', 'k'}, {'L', 'l'}, {'M', 'm'}, {'N', 'n'}, {'O', 'o'},
        {'Ö', 'ö'}, {'P', 'p'}, {'R', 'r'}, {'S', 's'}, {'Þ', 'þ'}, {'T', 't'},
        {'U', 'u'}, {'Ü', 'ü'}, {'V', 'v'}, {'Y', 'y'}, {'Z', 'z'}
    };

    unordered_map<char, char> to_upper_map = {
    {'a', 'A'}, {'b', 'B'}, {'c', 'C'}, {'ç', 'Ç'}, {'d', 'D'}, {'e', 'E'},
    {'f', 'F'}, {'g', 'G'}, {'ð', 'Ð'}, {'h', 'H'}, {'ý', 'I'}, {'i', 'Ý'},
    {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {'m', 'M'}, {'n', 'N'}, {'o', 'O'},
    {'ö', 'Ö'}, {'p', 'P'}, {'r', 'R'}, {'s', 'S'}, {'þ', 'Þ'}, {'t', 'T'},
    {'u', 'U'}, {'ü', 'Ü'}, {'v', 'V'}, {'y', 'Y'}, {'z', 'Z'}
    };

// Function definitions

void setTurkish() {
    setlocale(LC_ALL, "Turkish");
}

string to_lower(string text) {
    string result = "";

    for(int i = 0; i < text.size(); i++) {
        char current_char = text[i];
        // If the character is in the map, convert it to lowercase
        if (to_lower_map.find(current_char) != to_lower_map.end()) {
            result += to_lower_map[current_char];
        } else {
            // If the character is not in the map, keep it unchanged
            result += current_char;
        }
    }

    return result;
}

string to_upper(string text) {
    string result = "";

    for(int i = 0; i < text.size(); i++) {
        char current_char = text[i];
        // If the character is in the map, convert it to uppercase
        if (to_upper_map.find(current_char) != to_upper_map.end()) {
            result += to_upper_map[current_char];
        } else {
            // If the character is not in the map, keep it unchanged
            result += current_char;
        }
    }

    return result;
}

pair<int, int> primeFactorization(int n) {
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            int q = n / p;
            return {p, q};
        }
    }
    return {-1, -1}; // error, n should be a product of two primes
}

int euler_totient(int n) {
    int result = n; // Start with n

    // Check for each number i from 2 to sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        // If i is a factor of n
        if (n % i == 0) {
            // If i is a prime factor, divide n by i as long as it's divisible
            while (n % i == 0) {
                n /= i;
            }
            // Subtract the multiples of the prime factor i
            result -= result / i;
        }
    }

    // If n is still greater than 1, then it must be a prime number
    if (n > 1) {
        result -= result / n;
    }

    return result;
}

int determinant2x2(vector<vector<int>>& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

vector<vector<int>> inverse2x2(vector<vector<int>>& matrix) {
    vector<vector<int>> inverse(2, vector<int>(2, 0.0));

    // Calculate the inverse using the formula for 2x2 matrices
    inverse[0][0] = matrix[1][1];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];
    inverse[1][1] = matrix[0][0];

    return inverse;
}

int modPow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extendedGCD(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modInverse(int b, int phi_n) {
    int x, y;
    int g = extendedGCD(b, phi_n, x, y);
    if (g != 1) {
        throw invalid_argument("Inverse doesn't exist");
    }
    return (x % phi_n + phi_n) % phi_n;
}

string substitution_cipher(string& plain_text, unordered_map<char, char>& umap, bool space_enabled) {

    string cipher_text = "";

    plain_text = to_lower(plain_text);

    for(auto character : plain_text) {

        if(character == ' ' && space_enabled)
        cipher_text += ' ';
        else if(umap.find(character) != umap.end())
        cipher_text += umap[character];
    }

    return cipher_text;

}

string substitution_decipher(string& encrypted_text, unordered_map<char, char>& umap, bool space_enabled) {

    static unordered_map<char, char> decrypt_map;

    for (auto& pair : umap) {
        decrypt_map[pair.second] = pair.first;
    }

    for(int i=0; i<encrypted_text.size(); i++) {
        encrypted_text[i] = toupper(encrypted_text[i]);
    }

    string plain_text = "";

    for(auto character : encrypted_text) {

        if(character == ' ' && space_enabled)
        plain_text += ' ';
        else if(decrypt_map.find(character) != decrypt_map.end())
        plain_text += decrypt_map[character];
    }

    return plain_text;

}

string affine_cipher(string& plain_text, int a, int b, bool space_enabled) {

    string cipher_text = "";

    plain_text = to_lower(plain_text);

    // Iterate over each character in the plaintext
    for (char c : plain_text) {

        if(c == ' ' && space_enabled) {
            cipher_text += ' ';
            continue;
        }

        if(char_to_int.find(c) != char_to_int.end()) {
            // Apply the affine transformation formula (a * x + b) % 29
            int num = (a * char_to_int[c] + b) % 29;
            //cout << "(" << a << "*" << char_to_int[c] << "+" << b << ")%29 = " << num << "\n";
            // Append the corresponding character to the cipher text
            cipher_text += int_to_char[num];
            //cout << c << "-" << char_to_int[c] << " -> " << int_to_char[num] << "-" << num << "\n";
        }

    }

    return cipher_text;
}

string affine_decipher(string& encrypted_text, int a, int b, bool space_enabled) {

    string plain_text = "";

    encrypted_text = to_lower(encrypted_text);

    int a_inv = modInverse(a, 29);

    for (char c : encrypted_text) {
        if (space_enabled && c == ' ') {
            plain_text += ' ';
        } else {
            int c_val = char_to_int[c];
            int p_val = (a_inv * (c_val - b + 29)) % 29;
            plain_text += int_to_char[p_val];
        }
    }

    return plain_text;
}

string vigenere_cipher(string& plain_text, string key, bool space_enabled) {

    plain_text = to_lower(plain_text);
    key = to_lower(key);

    string cipher_text = "";
    int count = 0;

    for(int i=0; i<plain_text.size(); i++) {

        if(char_to_int.find(plain_text[i]) != char_to_int.end() ) {
            char char_a = plain_text[i];
            char char_key = key[(count%key.size())];

            int num = char_to_int[char_a] - char_to_int[char_key];

            while(num < 0) num += 29;

            //cout << char_a << " - " << char_key << " = " << int_to_char[num] << endl;

            cipher_text += int_to_char[num];

            count++;

        }else if(plain_text[i] == ' ' && space_enabled) {
            cipher_text += ' ';
        }

    }

    return cipher_text;

}

string vigenere_decipher(string& encrypted_text, string key, bool space_enabled) {

    encrypted_text = to_lower(encrypted_text);
    key = to_lower(key);

    string plain_text = "";
    int count = 0;

    for(int i=0; i<encrypted_text.size(); i++) {

       if(char_to_int.find(encrypted_text[i]) != char_to_int.end() ) {
            char char_a = encrypted_text[i];
            char char_key = key[(count%key.size())];

            int num = char_to_int[char_a] + char_to_int[char_key];

            while(num >= 29) num -= 29;

            //cout << char_a << " - " << char_key << " = " << int_to_char[num] << endl;

            plain_text += int_to_char[num];
            count++;

        }else if(encrypted_text[i] == ' ' && space_enabled) {
            plain_text += ' ';
        }

    }

    return plain_text;

}

string hill_cipher(string& plain_text, vector<vector<int>>& matrix) {

    plain_text = to_lower(plain_text);

    string cipher_text = "";
    vector<int> block;

    // Encrypt the plain text in blocks of size 2 (assuming 2x2 matrix)
    for (int i = 0; i < plain_text.size(); ++i) {
        if (char_to_int.find(plain_text[i]) != char_to_int.end()) {
            block.push_back(char_to_int[plain_text[i]]);
        }

        // Check if we have a complete block of 2 characters
        if (block.size() == 2) {
            // Perform matrix multiplication to encrypt the block
            int result1 = (matrix[0][0] * block[0] + matrix[0][1] * block[1]) % 29;
            int result2 = (matrix[1][0] * block[0] + matrix[1][1] * block[1]) % 29;

            // Convert results back to characters
            cipher_text += int_to_char[result1];
            cipher_text += int_to_char[result2];

            // Clear block for the next pair
            block.clear();
        }
    }


    // If there's a leftover character (not paired), handle it as needed
    if (!block.empty()) {

        int result1 = (matrix[0][0] * block[0] + matrix[0][1] * 0) % 29;
        int result2 = (matrix[1][0] * block[0] + matrix[1][1] * 0) % 29;

        // Convert results back to characters
        cipher_text += int_to_char[result1];
        cipher_text += int_to_char[result2];

        //cout << "Result1: " << int_to_char[result1] << endl;
        //cout << "Result2: " << int_to_char[result2] << endl;
    }

    return cipher_text;
}

string hill_decipher(string& encrypted_text, vector<vector<int>> matrix) {

    encrypted_text = to_lower(encrypted_text);

    int k = determinant2x2(matrix);
    k = (k % 29);
    if(k<0) k = k+29;

    int inverse_k;
    int temp;

    extendedGCD(k, 29, inverse_k, temp);

    vector<vector<int>> reverse_matrix = inverse2x2(matrix);

    for(int i=0; i<reverse_matrix.size(); i++) {
        for(int j=0; j<reverse_matrix[i].size(); j++) {

            reverse_matrix[i][j] = ( (inverse_k) * reverse_matrix[i][j] ) % 29;
            if(reverse_matrix[i][j] < 0) reverse_matrix[i][j] += 29;

            //cout << "[" << i << "]" << "[" << j << "]" << " : " << reverse_matrix[i][j] << "\n";

        }
        //cout << " ";
    }

    cout << "Determinant: " << k << endl;
    cout << "Inverse Determinant: " << inverse_k << endl;



    return hill_cipher(encrypted_text, reverse_matrix);

}

//digraph
string rsa_cipher(string& plain_text, int n, int b) {

    // Convert all text to lowercase
    plain_text = to_lower(plain_text);

    string cipher_text = "";
    vector<int> block;
    int result;

    for (int i = 0; i < plain_text.size(); ++i) {

        if (char_to_int.find(plain_text[i]) != char_to_int.end()) {
            block.push_back(char_to_int[plain_text[i]]);
        }

        // Check if we have a complete block of 2 characters
        if (block.size() == 2) {

            int num = block[0] * 29 + block[1]; // Combine two characters into one number
            result = modPow(num, b, n); // Encrypt the number using RSA

            //cout << num << " num= " << block[0] << " * 29 + " << block[1] << endl;
            //cout << num << "^" << b << " (mod" << n << ")= " << result << endl;


            cipher_text += int_to_char[(result / 29) / 29];
            cipher_text += int_to_char[(result / 29) % 29];
            cipher_text += int_to_char[result % 29];

            //cout << "x: " << result/(29*29) << "\ty:" << (result/29) % 29 << "\tz: " << result%29 << endl;
            //cout << "x: " << int_to_char[result/(29*29)] << "\ty:" << int_to_char[(result/29) % 29] << "\tz: " << int_to_char[result%29] << endl;

            // Clear block for the next pair
            block.clear();
        }
    }

    // If there's a leftover character (not paired), handle it as needed
    if (!block.empty()) {
        int num = block[0] * 29; // Handle single character case
        result = modPow(num, b, n);

        //cout << num << " ";

        // Convert the encrypted number back to characters
        cipher_text += int_to_char[(result / 29) / 29];
        cipher_text += int_to_char[(result / 29) % 29];
        cipher_text += int_to_char[result % 29];

        cout << result/29 << "\t" << result%29 << endl;
    }

    return cipher_text;
}

string rsa_decipher(string& encrypted_text, int n, int b) {

    encrypted_text = to_lower(encrypted_text);

    // Calculate the Euler's Totient function
    int phi = euler_totient(n);

    cout << "Phi: " << phi << endl;

    // Find the modular inverse of b modulo phi
    int a, temp;
    extendedGCD(b, phi, a, temp);
    // Ensure a is positive
    a = (a % phi + phi) % phi;

    cout << "a: " << a << endl;

    // Convert all text to lowercase (if needed)
    encrypted_text = to_lower(encrypted_text);

    string plain_text = "";
    vector<int> block;
    int result;

    for (int i = 0; i < encrypted_text.size(); ++i) {
        if (char_to_int.find(encrypted_text[i]) != char_to_int.end()) {
            block.push_back(char_to_int[encrypted_text[i]]);
        }

        // Check if we have a complete block of 3 characters
        if (block.size() == 3) {
            // Combine three characters into one number
            int num = block[0] * 29 * 29 + block[1] * 29 + block[2];

            //cout << "num= " << block[0] << "*29*29 + " << block[1] << "*29 + " << block[2] << endl;

            // Decrypt the number using the modular inverse
            result = modPow(num, a, n);

            //cout << num << "^" << b << " (mod" << n << ")= " << result << endl;

            // Convert the decrypted number back to two characters
            plain_text += int_to_char[result / 29];
            plain_text += int_to_char[result % 29];

            //cout << int_to_char[block[0]] << int_to_char[block[1]] << int_to_char[block[2]] << endl;

            // Clear block for the next set of characters
            block.clear();
        }
    }

    // Handle any leftover characters
    if (!block.empty()) {
        int num = block[0] * 29 * 29; // Handle single character case
        if (block.size() > 1) {
            num += block[1] * 29;
        }
        result = modPow(num, a, n);

        cout << num << " ";

        // Convert the decrypted number back to characters
        plain_text += int_to_char[result / 29];
        plain_text += int_to_char[result % 29];
    }

    return plain_text;
}

vector<vector<int>> elgamal_cipher(string& plain_text, int p, int alpha, int a) {
    int beta = modPow(alpha, a, p);
    cout << "Beta: " << beta << endl;

    plain_text = to_lower(plain_text);

    vector<vector<int>> encrypted_int;
    vector<int> block;
    int y1;
    int y2;

    // Seed the random number generator for each iteration
    srand(time(nullptr));
    // Generate a random k (1 <= k <= p-2)
    int k = rand() % (p - 2) + 1;

    cout << "K random number: " << k << endl;

    for (int i = 0; i < plain_text.size(); ++i) {

        if (char_to_int.find(plain_text[i]) != char_to_int.end()) {
            block.push_back(char_to_int[plain_text[i]]);
        }

        // Check if we have a complete block of 3 characters
        if (block.size() == 3) {


            // Combine three characters into one number
            int num = block[0] * 29 * 29 + block[1] * 29 + block[2];

            // Encrypt the number using ElGamal
            y1 = modPow(alpha, k, p);
            y2 = num * modPow(beta, k, p) % p;

            // Store y1 and y2 in encrypted_int
            encrypted_int.push_back({y1, y2});

            cout << "y1: " << y1 << " y2: " << y2 << endl;

            // Clear block for the next set of characters
            block.clear();
        }
    }

    // Handle any leftover characters
    if (!block.empty()) {
        int num = block[0] * 29 * 29; // Handle single character case
        if (block.size() > 1) {
            num += block[1] * 29;
        }

        // Generate a random k (1 <= k <= p-2) for the leftover characters
        int k = rand() % (p - 2) + 1;

        y1 = modPow(alpha, k, p);
        y2 = num * modPow(beta, k, p) % p;

        // Store y1 and y2 in encrypted_int
        encrypted_int.push_back({y1, y2});

        cout << "y1: " << y1 << " y2: " << y2 << endl;
    }

    return encrypted_int;
}

string elgamal_decipher(int y1, int y2, int p, int alpha, int a) {

    string plaintext;

    int inverse_y1;
    int temp;

    //cout << "y1^(-1): " << inverse_y1 << endl;

    int x = modPow(y1, a, p);
    //cout << "x= " << y2 << " x (" << y1 << "^" << a << ")^-1" << " mod(" << p << ") )" << endl;

    extendedGCD(x, p, x, temp);
    if(x<0) x+=p;

    x = (y2 * x) % p;

    //cout << "y1: " << y1 << " y2: " << y2 << endl;
    //cout << "x: " << "( " << y2 << " * " << x << " ) % " << p << endl;

    int c3 = x % 29;
    x /= 29;
    int c2 = x % 29;
    int c1 = x / 29;

    if (c3 < 0) c3 += 29;
    if (c2 < 0) c2 += 29;
    if (c1 < 0) c1 += 29;

    //cout << c3 << "* 29^2 + " << c2 << "* 29^1 + " << c1 << endl;

    plaintext += int_to_char[c1];
    plaintext += int_to_char[c2];
    plaintext += int_to_char[c3];

    return plaintext;
}
