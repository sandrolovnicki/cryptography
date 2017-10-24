/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework1, Problem3
 * Task:
 *
 * Build: g++ problem3.cpp -o problem3_exe
 * Run: ./problem3_exe
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

    void findmostFrequentCiphertextThreegrams()
    {
        for(int i=0; i<textLength-2; i++) {
            if(ciphertext[i] == ' ') continue;

            std::string bi = "";
            bi += ciphertext[i];
            if(ciphertext[i+1] == ' ') {
                bi += ciphertext[i+2];
                bi += ciphertext[i+3];
            }
            else {
                bi += ciphertext[i+1];
                if(ciphertext[i+2] == ' ')
                    bi += ciphertext[i+3];
                else
                    bi += ciphertext[i+2];
            }

            bool found = false;
            std::vector<std::pair<std::string, int> >::iterator it;
            for(it = mostFrequentCiphertextThreegrams.begin(); it != mostFrequentCiphertextThreegrams.end(); ++it)
                if(it->first == bi) {
                    it->second++;
                    found = true;
                    break;
                }
            if(!found) mostFrequentCiphertextThreegrams.push_back(std::make_pair(bi,1));
        }

        std::sort(mostFrequentCiphertextThreegrams.begin(), mostFrequentCiphertextThreegrams.end(), fun);
    }

    void findmostFrequentCiphertextQuadgrams()
    {
        for(int i=0; i<textLength-3; i++) {
            if(ciphertext[i] == ' ') continue;

            std::string bi = "";
            bi += ciphertext[i];
            if(ciphertext[i+1] == ' ') {
                bi += ciphertext[i+2];
                bi += ciphertext[i+3];
                bi += ciphertext[i+4];
            }
            else {
                bi += ciphertext[i+1];
                if(ciphertext[i+2] == ' ') {
                    bi += ciphertext[i+3];
                    bi += ciphertext[i+4];
                }
                else {
                    bi += ciphertext[i+2];
                    if(ciphertext[i+3] == ' ')
                        bi += ciphertext[i+4];
                    else
                        bi += ciphertext[i+3];
                }
            }

            bool found = false;
            std::vector<std::pair<std::string, int> >::iterator it;
            for(it = mostFrequentCiphertextQuadgrams.begin(); it != mostFrequentCiphertextQuadgrams.end(); ++it)
                if(it->first == bi) {
                    it->second++;
                    found = true;
                    break;
                }
            if(!found) mostFrequentCiphertextQuadgrams.push_back(std::make_pair(bi,1));
        }

        std::sort(mostFrequentCiphertextQuadgrams.begin(), mostFrequentCiphertextQuadgrams.end(), fun);
    }

    void printText(char type, std::string title)
    {
        std::cout << std::endl << "--- " << title << " ---" << std::endl;
        std::string text = (type == 'c' ? ciphertext : openText);
        for(int i=0; i<textLength; i++)
            std::cout << text[i];
        std::cout << std::endl;
    }

    void printAlphabet()
    {
        std::cout << std::endl;
        for(int i=0; i<26; i++)
            printf("%c ", 'A'+i);
        std::cout << std::endl;
        for(int i=0; i<26; i++) {
            int ind = findOInGuesses('A'+i);
            if(ind != -1)
                printf("%c ", userGuesses[ind].second);
            else
                printf("_ ");
        }
        std::cout << std::endl;
    }

    void printmostFrequentCiphertextLetters(int quantity)
    {
        std::cout << quantity << " most frequent letters:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextLetters[i].first << "(" << mostFrequentCiphertextLetters[i].second << "), ";
        std::cout << mostFrequentCiphertextLetters[quantity-1].first << "(" << mostFrequentCiphertextLetters[quantity-1].second << ")" << std::endl;
    }

    void printmostFrequentCiphertextBigrams(int quantity)
    {
        std::cout << quantity << " most frequent bigrams:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextBigrams[i].first << "(" << mostFrequentCiphertextBigrams[i].second << "), ";
        std::cout << mostFrequentCiphertextBigrams[quantity-1].first << "(" << mostFrequentCiphertextBigrams[quantity-1].second << ")" << std::endl;
    }

    void printmostFrequentCiphertextThreegrams(int quantity)
    {
        std::cout << quantity << " most frequent threegrams:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextThreegrams[i].first << "(" << mostFrequentCiphertextThreegrams[i].second << "), ";
        std::cout << mostFrequentCiphertextThreegrams[quantity-1].first << "(" << mostFrequentCiphertextThreegrams[quantity-1].second << ")" << std::endl;
    }

    void printmostFrequentCiphertextQuadgrams(int quantity)
    {
        std::cout << quantity << " most frequent threegrams:  ";
        for(int i=0; i<quantity-1; i++)
            std::cout << mostFrequentCiphertextQuadgrams[i].first << "(" << mostFrequentCiphertextQuadgrams[i].second << "), ";
        std::cout << mostFrequentCiphertextQuadgrams[quantity-1].first << "(" << mostFrequentCiphertextQuadgrams[quantity-1].second << ")" << std::endl;
    }

    void makeGuesses()
    {
        userGuesses.clear();
        char x,y,c;

        std::cout << std::endl << "type your guesses in the form open_text_letter->ciphertext_letter" << std::endl;
        std::cout << "example: P->S (meaning P gets encrypted into S)" << std::endl;
        std::cout << "type '-' if you are done with guessing" << std::endl << std::endl;

        int i=0;
        while(1) {
            i++;
            std::cout << "guess " << i << ": ";
            std::cin >> x;
            if(x == '-') break;
            std::cin >> c; std::cin >> c;
            std::cin >> y;
            userGuesses.push_back(std::make_pair(x,y));
        }
    }

    int findOInGuesses(char o)
    {
        for(int i=0; i<userGuesses.size(); i++)
            if(userGuesses[i].first == o)
                return i;
        return -1;
    }

    int findCInGuesses(char c)
    {
        for(int i=0; i<userGuesses.size(); i++)
            if(userGuesses[i].second == c)
                return i;
        return -1;
    }

    void substitute()
    {
        std::cout << std::endl;

        for (int i = 0; i < textLength; i++) {
            if (ciphertext[i] != ' ') {
                int index = findCInGuesses(ciphertext[i]);
                if(index != -1)
                    openText[i] = userGuesses[index].first;
                else
                    openText[i] = '_';
            } else
                openText[i] = ' ';
        }

        printText('o',"open text obtained with this substitution");
        printAlphabet();
        std::cout << std::endl;
    }

    void add()
    {
        std::cout << std::endl << "type your add in the form open_text_letter->ciphertext_letter" << std::endl;
        std::cout << "example: P->S (meaning P gets encrypted into S)" << std::endl;
        std::cout << "add: ";

        char open, cipher, c;
        std::cin >> open;
        std::cin >> c; std::cin >> c;
        std::cin >> cipher;

        for (int i = 0; i < textLength; i++)
            if(ciphertext[i] == cipher)
                openText[i] = open;
        userGuesses.push_back(std::make_pair(open,cipher));

        printText('o',"open text obtained with this change");
        printAlphabet();
        std::cout << std::endl;
    }

    void remove()
    {
        std::cout << std::endl << "type open text letter which you want to remove from guesses" << std::endl;
        std::cout << "remove: ";

        char open;
        std::cin >> open;

        for (int i = 0; i < textLength; i++)
            if(openText[i] == open)
                openText[i] = '_';

        std::vector<std::pair<char, char> >::iterator it;
        for(it = userGuesses.begin(); it != userGuesses.end(); it++)
            if(it->first == open)
                break;
        userGuesses.erase(it);

        printText('o',"open text obtained with this removal");
        printAlphabet();
        std::cout << std::endl;
    }

private:
    std::string ciphertext;
    std::vector<std::pair<int, int> > keys;
    std::string openText;
    int textLength;
    std::vector<std::pair<char, int> > mostFrequentCiphertextLetters;
    std::vector<std::pair<std::string, int> > mostFrequentCiphertextBigrams;
    std::vector<std::pair<std::string, int> > mostFrequentCiphertextThreegrams;
    std::vector<std::pair<std::string, int> > mostFrequentCiphertextQuadgrams;
    std::vector<std::pair<char, char> > userGuesses;
};

int main()
{
    AffineDecrypter decrypter("problem3_ciphertext.txt");

    decrypter.findmostFrequentCiphertextLetters();
    decrypter.findmostFrequentCiphertextBigrams();
    decrypter.findmostFrequentCiphertextThreegrams();
    decrypter.findmostFrequentCiphertextQuadgrams();

    decrypter.printText('c', "ciphertext to decrypt");

    int l,b,t,q;
    std::cout << std::endl << "How many most frequent letters you want to see? "; std::cin >> l;
    decrypter.printmostFrequentCiphertextLetters(l);
    std::cout << std::endl << "How many most frequent bigrams you want to see? "; std::cin >> b;
    decrypter.printmostFrequentCiphertextBigrams(b);
    std::cout << std::endl << "How many most frequent threegrams you want to see? "; std::cin >> t;
    decrypter.printmostFrequentCiphertextThreegrams(t);
    std::cout << std::endl << "How many most frequent quadgrams you want to see? "; std::cin >> q;
    decrypter.printmostFrequentCiphertextQuadgrams(q);

    std::string response;
    while(true) {
        decrypter.makeGuesses();
        decrypter.substitute();

        while(true) {
            std::cout << std::endl << "What do you want to do? [add/remove/quit, default - guess again] ";
            std::cin >> response;

            if (response == "add") decrypter.add();
            else if (response == "remove") decrypter.remove();
            else break;
        }
        if(response == "quit") break;
    }

    std::cout << std::endl;

    return 0;
}
