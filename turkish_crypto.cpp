// turkish_crypto.cpp

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>
#include <clocale>
#include <stdexcept>
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

// Function definitions

void setTurkish() {
    setlocale(LC_ALL, "Turkish");
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

    for(int i=0; i<plain_text.size(); i++) {
        plain_text[i] = tolower(plain_text[i]);
    }

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

    // Lower all text
    for(int i=0; i<plain_text.size(); i++) {
        plain_text[i] = tolower(plain_text[i]);
    }

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

    for (char &c : encrypted_text) {
        c = tolower(c);
    }

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

    // Lower all text
    for(int i=0; i<plain_text.size(); i++) {
        plain_text[i] = tolower(plain_text[i]);
    }
    for(int i=0; i<key.size(); i++) {
        key[i] = tolower(key[i]);
    }

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

    // Convert all text to lowercase
    for(int i = 0; i < plain_text.size(); i++) {
        plain_text[i] = tolower(plain_text[i]);
    }

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
        int result = matrix[0][0] * block[0] % 29; // Just an example, adjust as per your matrix size
        cipher_text += int_to_char[result];
    }

    return cipher_text;
}

string hill_decipher(string& encrypted_text, vector<vector<int>> matrix) {

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

            cout << "[" << i << "]" << "[" << j << "]" << " : " << reverse_matrix[i][j] << "\n";

        }
        cout << " ";
    }

    cout << "Determinant: " << k << endl;
    cout << "Inverse Determinant: " << inverse_k << endl;



    return hill_cipher(encrypted_text, reverse_matrix);

}
