#include "turkish_crypto.h"
#include <iostream>
using namespace std;

int main() {

    unordered_map<char, char> umap;

    umap['a'] = 'H';
    umap['b'] = 'K';
    umap['c'] = 'S';
    umap['�'] = 'V';
    umap['d'] = '�';
    umap['e'] = 'R';
    umap['f'] = 'C';
    umap['g'] = 'A';
    umap['�'] = 'G';
    umap['h'] = 'F';
    umap['�'] = 'Y';
    umap['i'] = '�';
    umap['j'] = 'E';
    umap['k'] = 'T';
    umap['l'] = 'L';
    umap['m'] = 'N';
    umap['n'] = '�';
    umap['o'] = 'B';
    umap['�'] = '�';
    umap['p'] = 'J';
    umap['r'] = '�';
    umap['s'] = 'D';
    umap['�'] = 'U';
    umap['t'] = 'Z';
    umap['u'] = 'M';
    umap['�'] = 'I';
    umap['v'] = 'O';
    umap['y'] = 'P';
    umap['z'] = '�';

    setTurkish();

    string text = "ger�ekler her zaman ger�ektir!";

    string encrypted_text = substitution_cipher(text, umap);
    string decrypted_text = substitution_decipher(encrypted_text, umap);

    cout << encrypted_text << endl << decrypted_text << endl;

    int a = 120;
    int b = 36;
    int x = 0;
    int y = 0;

    extendedGCD(a, b, x, y);
    cout << "Extended GCD of (" << a << ", " << b << ") = " << "(" << x << ", " << y << ")\n" << endl;

    encrypted_text = affine_cipher(text, 5, 4);
    decrypted_text = affine_decipher(encrypted_text, 5, 4);
    cout << "Affine Cipher:" << encrypted_text << endl;
    cout << "Affine Decipher:" << decrypted_text << endl << endl;

    encrypted_text = vigenere_cipher(text, "halilo�lu", false);
    decrypted_text = vigenere_decipher(encrypted_text, "halilo�lu", false);
    cout << "Vigenere Cipher:" << encrypted_text << endl;
    cout << "Vigenere Decipher:" << decrypted_text << endl << endl;

    vector<vector<int>> matrix = {{7, 9}, {26, 20}};
    encrypted_text = hill_cipher(text, matrix);
    decrypted_text = hill_decipher(encrypted_text, matrix);
    cout << "Hill Cipher:" << encrypted_text << endl;
    cout << "Hill Decipher:" << decrypted_text << endl << endl;

    system("pause");

}
