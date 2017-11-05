/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework2, Problem2
 * Task:    Find the key K in Hill's cipher if m=2 and pair (open text, ciphertext) is known.
 *
 * Build: g++ problem2.cpp -o problem2_exe
 * Run: ./problem2_exe
 *
 ***********************************************************************************************************************
 * USAGE:
 *
 *
***********************************************************************************************************************/

#include <iostream>
#include <vector>


class Hill
{
public:
    Hill(std::string _openText, std::string _ciphertext)
    {
        openText = _openText;
        if(openText.length() % 2 == 1) openText += 'X';
        ciphertext = _ciphertext;
    }

    void getOpenText()
    {
        std::cout << "open text ? ";
        std::cin >> openText;
    }

    void getCiphertext()
    {
        std::cout << "ciphertext? ";
        std::cin >> ciphertext;
    }

    void printEquation(int _first2, int _second2)
    {
        std::cout << std::endl;
        first2 = _first2;
        second2 = _second2;

        std::cout << "matrix equation AK=b for " << first2 << ". and " << second2 << ". pair of letters:" << std::endl;
        std::cout << "|" << openText[first2+0]-'A' << ((openText[first2+0]-'A')<10?"  ":" ") << ((openText[first2+1]-'A')<10?" ":"") << openText[first2+1]-'A' << "| |k1 k2|  =  |" << ciphertext[first2+0]-'A' << ((ciphertext[first2+0]-'A')<10?"  ":" ") << ((ciphertext[first2+1]-'A')<10?" ":"") << ciphertext[first2+1]-'A' << "|" << std::endl;
        std::cout << "|" << openText[second2+0]-'A' << ((openText[second2+0]-'A')<10?"  ":" ") << ((openText[second2+1]-'A')<10?" ":"") << openText[second2+1]-'A' << "| |k3 k4|     |" << ciphertext[second2+0]-'A' << ((ciphertext[second2+0]-'A')<10?"  ":" ") << ((ciphertext[second2+1]-'A')<10?" ":"") << ciphertext[second2+1]-'A' << "|" << std::endl;
    }

    bool findDeterminants()
    {
        std::cout << std::endl;

        int det = ((openText[first2+0]-'A')*(openText[second2+1]-'A') - (openText[first2+1]-'A')*(openText[second2+0]-'A'))%26;
        std::cout << "detA      = " << det << std::endl;

        for(int i=0; i<26; i++)
            if((i*det)%26 == 1) {
                inverse_detA = i;
                std::cout << "(detA)^-1 = " << inverse_detA << std::endl;
                return true;
            }
        std::cout << "(detA)^-1 does not exist." << std::endl << "------------------------------------------" << std::endl;
        return false;
    }

    void findInverseA()
    {
        std::cout << std::endl;

        inverse_A[0][0] = (inverse_detA * (openText[second2+1]-'A')) % 26;
        inverse_A[0][1] = ((-inverse_detA+26) * (openText[first2+1]-'A')) % 26;
        inverse_A[1][0] = ((-inverse_detA+26) * (openText[second2+0]-'A')) % 26;
        inverse_A[1][1] = (inverse_detA * (openText[first2+0]-'A')) % 26;

        std::cout << "A^-1 = |" << inverse_A[0][0] << (inverse_A[0][0]<10?"  ":" ") << (inverse_A[0][1]<10?" ":"") << inverse_A[0][1] << "|" << std::endl;
        std::cout << "       |" << inverse_A[1][0] << (inverse_A[1][0]<10?"  ":" ") << (inverse_A[1][1]<10?" ":"") << inverse_A[1][1] << "|" << std::endl;
    }

    void findKey()
    {
        std::cout << std::endl;

        key[0][0] = ((inverse_A[0][0] * (ciphertext[first2+0]-'A')) + (inverse_A[0][1] * (ciphertext[second2+0]-'A'))) % 26;
        key[0][1] = ((inverse_A[0][0] * (ciphertext[first2+1]-'A')) + (inverse_A[0][1] * (ciphertext[second2+1]-'A'))) % 26;
        key[1][0] = ((inverse_A[1][0] * (ciphertext[first2+0]-'A')) + (inverse_A[1][1] * (ciphertext[second2+0]-'A'))) % 26;
        key[1][1] = ((inverse_A[1][0] * (ciphertext[first2+1]-'A')) + (inverse_A[1][1] * (ciphertext[second2+1]-'A'))) % 26;

        std::cout << "K = |" << key[0][0] << (key[0][0]<10?"  ":" ") << (key[0][1]<10?" ":"") << key[0][1] << "|" << std::endl;
        std::cout << "    |" << key[1][0] << (key[1][0]<10?"  ":" ") << (key[1][1]<10?" ":"") << key[1][1] << "|" << std::endl;
    }

    void printTest()
    {
        std::cout << std::endl;
        std::cout << "testing all pairs:" << std::endl;

        int ct0, ct1;

        for(int i=0; i<openText.length()-1; i+=2) {
            ct0 = ((openText[i] - 'A') * key[0][0] + (openText[i+1] - 'A') * key[1][0]) % 26;
            ct1 = ((openText[i] - 'A') * key[0][1] + (openText[i+1] - 'A') * key[1][1]) % 26;
            std::cout << "|" << openText[i] << " " << openText[i+1] << "| |" << key[0][0] << (key[0][0]<10?"  ":" ") << (key[0][1]<10?" ":"") << key[0][1] << "| = |"
                      << (char) (ct0 + 'A') << " " << (char) (ct1 + 'A') << "|" << std::endl;
            std::cout << "      |" << key[1][0] << (key[1][0]<10?"  ":" ") << (key[1][1]<10?" ":"") << key[1][1] << "|" << std::endl;
        }
    }

    int textLength()
    {
        return openText.length();
    }


private:
    std::string openText;
    std::string ciphertext;
    int first2;
    int second2;
    int key[2][2];
    int inverse_detA;
    int inverse_A[2][2];
};

int main()
{
    std::cout << std::endl;

    Hill h("", "");

    h.getOpenText();
    h.getCiphertext();

    char ok='n';
    for(int pair1=0; pair1<h.textLength()-1; pair1+=2) {
        for (int pair2 = 0; pair2<h.textLength()-1; pair2+=2) {
            if (((pair1 - pair2) < 0 ? (-pair1 + pair2) : (pair1 - pair2)) < 2) continue;
            h.printEquation(pair1, pair2);
            if (h.findDeterminants() == true) {
                h.findInverseA();
                h.findKey();
                h.printTest();
                std::cout << "is this OK? [y/n] ";
                std::cin >> ok;
                if(ok == 'y') break;
            }
        }
        if(ok == 'y') break;
    }

    std::cout << std::endl;
    return 0;
}
