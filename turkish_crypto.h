// turkish_crypto.h

#ifndef TURKISH_CRYPTO_H
#define TURKISH_CRYPTO_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>
#include <clocale>
#include <stdexcept>
using namespace std;

extern unordered_map<char, int> char_to_int;
extern unordered_map<int, char> int_to_char;

void setTurkish();

int determinant2x2(vector<vector<int>>& matrix);

int modPow(int base, int exp, int mod);

int gcd(int a, int b);

int extendedGCD(int a, int b, int &x, int &y);

int modInverse(int b, int phi_n);

string substitution_cipher(string& plain_text, unordered_map<char, char>& umap, bool space_enabled=false);

string substitution_decipher(string& encrypted_text, unordered_map<char, char>& umap, bool space_enabled=false);

string affine_cipher(string& plain_text, int a, int b, bool space_enabled=false);

string affine_decipher(string& encrypted_text, int a, int b, bool space_enabled=false);

string vigenere_cipher(string& plain_text, string key, bool space_enabled=false);

string vigenere_decipher(string& encrypted_text, string key, bool space_enabled=false);

string hill_cipher(string& plain_text, vector<vector<int>>& matrix);

string hill_decipher(string& encrypted_text, vector<vector<int>> matrix);

#endif // TURKISH_CRYPTO_H