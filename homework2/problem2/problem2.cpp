/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework2, Problem2
 * Task:    Given a key word and open text, obtain the Playfair's ciphertext
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


class Playfair
{
public:
    Playfair(std::string _keyWord, std::string _openText)
    {
        for(int i=0; i<26; i++)
            alphabet.push_back('A'+i);
        keyWord = _keyWord;
        openText = _openText;
        ciphertext = "";
    }

    void getKeyWord()
    {
        std::cout << "key word ? ";
        std::cin >> keyWord;
    }
    void getOpenText()
    {
        std::cout << "open text? ";
        std::cin >> openText;
    }

    std::vector<char>::iterator findInAlphabet(char x)
    {
        for(it = alphabet.begin(); it != alphabet.end(); ++it) {
            if(*it == x)
                return it;
        }
        return it;
    }

    void constructMatrix()
    {
        int i=0, m_i=0;

        while(i<keyWord.length()) {
            if(keyWord[i] == 'W') keyWord[i]='V';
            it = findInAlphabet(keyWord[i]);
            if(it == alphabet.end()) {
                ;
            } else {
                playfairMatrix[m_i/5][m_i%5] = keyWord[i];
                alphabet.erase(it);
                ++m_i;
            }
            ++i;
        }
        for(it = alphabet.begin(); it != alphabet.end(); ++it) {
            if(*it == 'W') continue;
            playfairMatrix[m_i/5][m_i%5] = *it;
            ++m_i;
        }
    }

    void printMatrix()
    {
        std::cout << "playfair matrix (W<=>V):" << std::endl;
        for(int i=0; i<5; i++) {
            for (int j = 0; j < 5; j++)
                std::cout << playfairMatrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    std::pair<int, int> findInMatrix(char x)
    {
        if(x == 'W') x = 'V';
        for(int i=0; i<5; i++)
            for (int j = 0; j < 5; j++)
                if(playfairMatrix[i][j] == x)
                    return std::make_pair(i,j);
    }

    void encrypt()
    {
        if(openText.length()%2 == 1) openText += "X";

        std::pair<int,int> firstLetter;
        std::pair<int,int> secondLetter;

        for(int i=0; i<openText.length()-1; i+=2) {
            firstLetter = findInMatrix(openText[i]);
            secondLetter = findInMatrix(openText[i+1]);

            if(firstLetter.first == secondLetter.first) {
                // get right next in row
                if(firstLetter.second == 4) {
                    firstLetter.second = 0;
                } else {
                    firstLetter.second++;
                }
                ciphertext += playfairMatrix[firstLetter.first][firstLetter.second];

                if(secondLetter.second == 4) {
                    secondLetter.second = 0;
                } else {
                    secondLetter.second++;
                }
                ciphertext += playfairMatrix[secondLetter.first][secondLetter.second];
            }

            else if(firstLetter.second == secondLetter.second) {
                // get down next in column
                if(firstLetter.first == 4) {
                    firstLetter.first = 0;
                } else {
                    firstLetter.first++;
                }
                ciphertext += playfairMatrix[firstLetter.first][firstLetter.second];

                if(secondLetter.first == 4) {
                    secondLetter.first = 0;
                } else {
                    secondLetter.first++;
                }
                ciphertext += playfairMatrix[secondLetter.first][secondLetter.second];
            }

            else {
                ciphertext += playfairMatrix[firstLetter.first][secondLetter.second];
                ciphertext += playfairMatrix[secondLetter.first][firstLetter.second];
            }
        }
    }

    void printOpenText()
    {
        std::cout << "open text : " << openText << std::endl;
    }
    void printCiphertext()
    {
        std::cout << "ciphertext: " << ciphertext << std::endl;
    }

private:
    std::string keyWord;
    std::string openText;
    std::string ciphertext;
    std::vector<char> alphabet;
    std::vector<char>::iterator it;
    char playfairMatrix[5][5];
};

int main()
{
    Playfair t("", "");
    std::cout << std::endl;
    t.getKeyWord();
    t.getOpenText();
    t.constructMatrix();
    std::cout << std::endl;
    t.printMatrix();
    std::cout << std::endl;
    t.encrypt();
    t.printOpenText();
    t.printCiphertext();
    std::cout << std::endl;

    return 0;
}
