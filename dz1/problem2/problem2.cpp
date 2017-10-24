/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework1, Problem2
 * Task:
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
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


bool operator<(const std::pair<char,int>& lhs, const std::pair<char,int>& rhs)
{
    return lhs.second > rhs.second;
}

bool fun(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs)
{
    return lhs.second > rhs.second;
}


class AffineDecrypter
{
public:
    AffineDecrypter(std::string file)
    {
        std::ifstream myFile(file.c_str());
        if (myFile.is_open()) {
            getline (myFile,ciphertext);
            myFile.close();
        } else std::cout << "Unable to open file";

        textLength = ciphertext.length();

        for(int i=0; i<26; i++)
            mostFrequentCiphertextLetters.push_back(std::make_pair('A'+i,0));

        openText = ciphertext;
    }

    void findmostFrequentCiphertextLetters()
    {
        for(int i=0; i<textLength; ++i)
            mostFrequentCiphertextLetters[ciphertext[i]-'A'].second++;

        std::sort(mostFrequentCiphertextLetters.begin(), mostFrequentCiphertextLetters.end(), operator<);
    }
    void findmostFrequentCiphertextBigrams()
    {
        for(int i=0; i<textLength-1; i++) {
            if(ciphertext[i] == ' ') continue;

            std::string bi = "";
            bi += ciphertext[i];
            if(ciphertext[i+1] == ' ') bi += ciphertext[i+2];
            else bi += ciphertext[i+1];

            bool found = false;
            std::vector<std::pair<std::string, int> >::iterator it;
            for(it = mostFrequentCiphertextBigrams.begin(); it != mostFrequentCiphertextBigrams.end(); ++it)
                if(it->first == bi) {
                    it->second++;
                    found = true;
                    break;
                }
            if(!found) mostFrequentCiphertextBigrams.push_back(std::make_pair(bi,1));
        }

        std::sort(mostFrequentCiphertextBigrams.begin(), mostFrequentCiphertextBigrams.end(), fun);
    }

    void printText(char type, std::string title)
    {
        std::cout << std::endl << "--- " << title << " ---" << std::endl;
        std::string text = (type == 'c' ? ciphertext : openText);
        for(int i=0; i<textLength; i++)
            std::cout << text[i];
        std::cout << std::endl;
    }

    void printmostFrequentCiphertextLetters(int quantity)
    {
        std::cout << quantity << " most frequent letters:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextLetters[i].first << "(" << mostFrequentCiphertextLetters[i].second << "), ";
        std::cout << mostFrequentCiphertextLetters[4].first << "(" << mostFrequentCiphertextLetters[quantity-1].second << ")" << std::endl;
    }

    void printmostFrequentCiphertextBigrams(int quantity)
    {
        std::cout << quantity << " most frequent bigrams:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextBigrams[i].first << "(" << mostFrequentCiphertextBigrams[i].second << "), ";
        std::cout << mostFrequentCiphertextBigrams[4].first << "(" << mostFrequentCiphertextBigrams[quantity-1].second << ")" << std::endl;
    }

    void make2Guesses()
    {
        userGuesses.clear();
        char x,y,c;

        std::cout << std::endl << "type your 2 guesses in the form open_text_letter->ciphertext_letter" << std::endl;
        std::cout << "example: P->S (meaning P gets encrypted into S)" << std::endl;

        for(int i=0; i<2; i++) {
            std::cout << "guess " << i+1 << ": ";
            std::cin >> x;
            std::cin >> c; std::cin >> c;
            std::cin >> y;
            userGuesses.push_back(std::make_pair(x,y));
        }
    }

    void solveCongruences()
    {
        keys.clear();
        int x1 = userGuesses[0].first - 'A';
        int y1 = userGuesses[0].second - 'A';
        int x2 = userGuesses[1].first - 'A';
        int y2 = userGuesses[1].second - 'A';

        std::cout << std::endl;
        std::cout << "BASED ON YOUR 2 CHOICES, THESE ARE CONGRUENCES FOR COMPUTING A KEY (a,b)" << std::endl << std::endl;
        std::cout << "a*" << x1 << " + b = " << y1 << " (mod 26)  &&  ";
        std::cout << "a*" << x2 << " + b = " << y2 << " (mod 26)" << std::endl;

        std::cout << std::endl << "solutions:";
        for(int a=0; a<26; a++) {
            for (int b = 0; b < 26; b++) {
                if ((((a * x1) + b) % 26 == y1) && (((a * x2) + b) % 26 == y2)) {
                    keys.push_back(std::make_pair(a,b));
                    std::cout << std::endl << "KEY" << keys.size()-1 << " = (" << keys[keys.size()-1].first << "," << keys[keys.size()-1].second << ")";
                    std::cout << "    check: " << a << "*" << x1 << " + " << b << " = " << (a * x1 + b) % 26 << " (mod 26)  &&  ";
                    std::cout << a << "*" << x2 << " + " << b << " = " << (a * x2 + b) % 26 << " (mod 26)";
                }
            }
        }
        if(keys.size() == 0)
            std::cout << std::endl << "no solutions";
    }

    void decrypt()
    {
        int y;
        int a_1;
        std::cout << std::endl;

        for(int k=0; k<keys.size(); k++) {
            a_1 = -1;
            for (int i = 0; i < 26; i++) {
                if ((i * keys[k].first) % 26 == 1) {
                    a_1 = i;
                    std::cout << std::endl << "KEY" << k << " -> a^-1 = " << a_1;
                }
            }
            if (a_1 == -1) {
                std::cout << std::endl << "KEY" << k << " -> a has no inverse";
                continue;
            }

            for (int i = 0; i < textLength; i++) {
                if (ciphertext[i] != ' ') {
                    y = ciphertext[i] - 'A';
                    openText[i] = (char) (((a_1 * (y - keys[k].second + 26)) % 26) + 'A');
                } else
                    openText[i] = ' ';
            }

            printText('o',"open text obtained with this key");
            std::cout << std::endl;
        }
    }

private:
    std::string ciphertext;
    std::vector<std::pair<int, int> > keys;
    std::string openText;
    int textLength;
    std::vector<std::pair<char, int> > mostFrequentCiphertextLetters;
    std::vector<std::pair<std::string, int> > mostFrequentCiphertextBigrams;
    std::vector<std::pair<char, char> > userGuesses;
};

int main()
{
    AffineDecrypter decrypter("problem2_ciphertext.txt");

    decrypter.findmostFrequentCiphertextLetters();
    decrypter.findmostFrequentCiphertextBigrams();

    decrypter.printText('c', "ciphertext to decrypt");

    int l,b;
    std::cout << std::endl << "How many most frequent letters you want to see? "; std::cin >> l;
    decrypter.printmostFrequentCiphertextLetters(l);
    std::cout << std::endl << "How many most frequent bigrams you want to see? "; std::cin >> b;
    decrypter.printmostFrequentCiphertextBigrams(b);

    char response;
    while(true) {
        decrypter.make2Guesses();
        decrypter.solveCongruences();
        decrypter.decrypt();

        std::cout << std::endl << "Does this look OK to you? [y/n] "; std::cin >> response;
        if(response == 'y') break;
    }

    std::cout << std::endl;

    return 0;
}
