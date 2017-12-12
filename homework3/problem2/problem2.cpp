/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework3, Problem2
 * Task:    In ciphertexts.txt are 2 ciphertext obtained with same key from open texts on Croatian language.
 *          Decrypt the texts if encryption is of form yi = xi + ki (mod 26) and open texts both start with one
 *          of four letters: S, P, N, D.
 *
 * Build: g++ -std=c++11 problem2.cpp -o problem2_exe
 * Run: ./problem2_exe
 *
 **********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <list>
#include <string>

class Kerckhoffs
{
public:
    Kerckhoffs(std::string file)
    {
        std::ifstream ctxt(file.c_str());
        if(ctxt.is_open()) {
            getline(ctxt, ciphertext1);
            getline(ctxt, ciphertext2);
            ctxt.close();
        } else std::cout << "Unable to open ciphertext file";

        open_text1 = "";
        open_text2 = "";
        position = 0;

        std::cout << std::endl << ciphertext1 << std::endl << ciphertext2 <<  std::endl;
    }

    void guessNextLetter()
    {
        char l;

        std::cout << std::endl <<  "guess " << (position+1) << ". letter in first open text: ";
        std::cin >> l;

        open_text1 += l;
        open_text2 += ((ciphertext2[position]-'A') - (ciphertext1[position]-'A') + (l-'A') + 26)%26 + 'A';

        std::cout << "open text 1: " << open_text1 << std::endl << "open text 2: " << open_text2 << std::endl;

        position++;
    }

    void rewind()
    {
        open_text1.pop_back();
        open_text2.pop_back();

        std::cout << "open text 1: " << open_text1 << std::endl << "open text 2: " << open_text2 << std::endl;

        position--;
    }


private:
    std::string ciphertext1;
    std::string open_text1;
    std::string ciphertext2;
    std::string open_text2;
    std::string key;
    int position;
};

int main() {

    Kerckhoffs K("ciphertexts.txt");

    char satisfied='n', rewind='n';
    while (satisfied != 'y') {
        K.guessNextLetter();
        std::cout << "rewind? [y/n] ";
        std::cin >> rewind;
        if(rewind == 'y')
            K.rewind();
        std::cout << "done? [y/n] ";
        std::cin >> satisfied;
    }


    return 0;
}
