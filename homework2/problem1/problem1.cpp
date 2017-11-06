/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework2, Problem2
 * Task:    In problem1_ciphertext.txt is a ciphertext obtained with Vigenere's cipher from open text on Croatian language.
 *          Find length of the keyword, keyword itself and decrypt the text.
 *
 * Build: g++ problem1.cpp -o problem1_exe
 * Run: ./problem1_exe
 *
 ***********************************************************************************************************************
 * USAGE:
 *
 *
***********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>


class Vigenere
{
public:
    Vigenere(std::string ciphertext_file, std::string letters_p)
    {
        std::ifstream ctxt(ciphertext_file.c_str());
        if (ctxt.is_open()) {
            getline (ctxt,ciphertext0);
            ctxt.close();
        } else std::cout << "Unable to open ciphertext file";

        ciphertext = "";
        for(int i=0; i<ciphertext0.length(); i++) {
            if(ciphertext0[i] == ' ') continue;
            ciphertext += ciphertext0[i];
        }
        ciphertextLength = ciphertext.length();

        std::ifstream lp(letters_p.c_str());
        if(lp.is_open()) {
            for (int i = 0; i < 26; i++)
                lp >> frequencies[i].first;
            lp.close();
        } else std::cout << "Unable to open letters_p file";

        columns = 0;
        openText = "";
        resetFrequencies();
    }

    void resetFrequencies()
    {
        for(int i=0; i<26; i++)
            frequencies[i].second = 0;
    }

    void Kasiski()
    {
        std::cout << std::endl;

        std::string first="";
        std::string found="";
        std::cout << "Kasiski test:" << std::endl;
        for(int i=0; i<ciphertextLength-3; i++) {
            first += ciphertext[i];
            first += ciphertext[i+1];
            first += ciphertext[i+2];
            for(int j=i+2; j<ciphertextLength-3; j++) {
                found += ciphertext[j];
                found += ciphertext[j+1];
                found += ciphertext[j+2];
                if(first == found)
                    std::cout << first << "-" << i << " " << found << "-" << j << "  -> difference = " << j-i << std::endl;
                found = "";
            }
            first = "";
        }
	std::cout << std::endl;
    }

    void createMatrix(int m)
    {
        std::cout << std::endl;

        keyLength=m;
        columns = ciphertextLength/keyLength + 1;
        double ic;
        int col;
        resetFrequencies();

        matrix = (char**)std::malloc(keyLength*sizeof(char*));
        for(int i=0; i<keyLength; i++)
            matrix[i] = (char*)std::malloc((columns+1)*sizeof(char));

        for(int k=0; k<keyLength; k++) {
            resetFrequencies();
            ic = 0.0;
            col=0;
            for (int i=k; i<ciphertextLength; i+=keyLength) {
                frequencies[ciphertext[i] - 'A'].second++;
                matrix[k][col] = ciphertext[i];
                std::cout << matrix[k][col];
                col++;
            }
            for (int i = 0; i < 26; i++)
                ic += frequencies[i].second * (frequencies[i].second - 1);
            std::cout << "  I_c = " << ic / (columns * (columns - 1)) << std::endl;
        }
    }

    void calculateMhs()
    {
        std::cout << std::endl;

        double max;
        int j,g,h;
        double mg;
        key = "";

        for(j=0; j<keyLength; j++) {
            resetFrequencies();
            for(int i=0; i<columns; i++)
                frequencies[matrix[j][i]-'A'].second++;
            max = 0.0;
		std::cout << "for j=" << j << ", M_gs are:" << std::endl;
            for(g=0; g<26; g++) {
                mg = 0.0;
                for(int i=0; i<26; i++)
                    mg += frequencies[i].first * frequencies[(i-g+26)%26].second;
                mg /= columns;
		std::cout << std::fixed << std::setprecision(6) << mg << " ";
		if((g+1)%10==0) std::cout << std::endl;
                if(mg > max) {
                    max = mg;
                    h = g;
                }
            }
            key += 'A'+ (-h+26)%26;
            std::cout << std::endl << " => M_h=" << max << " and h=" << std::fixed << std::setprecision(6) << h << std::endl << std::endl;
        }
        std::cout << "key: " << key << std::endl;
    }

    void decrypt(std::string _key)
    {
        if(_key != "") key = _key;

        for(int i=0; i<ciphertextLength; i++) {
            openText += ((ciphertext[i]-'A'-key[i%keyLength]+'A'+26) % 26) + 'A';
        }
        std::cout << std::endl << "open text:" << std::endl <<  openText << std::endl;

        std::ofstream otxt("problem1_opentext.txt");
        otxt << openText;
        otxt.close();
    }

private:
    std::string openText;
    std::string ciphertext0;
    std::string ciphertext;
    std::pair<double, int> frequencies[26];
    int keyLength;
    std::string key;
    int ciphertextLength;
    int columns;
    char** matrix;
};

int main()
{
    Vigenere v("problem1_ciphertext.txt", "croatian_letters_p.txt");

    v.Kasiski();

    int k;
    char response='n';
    while(response != 'y') {
        while (response != 'y') {
            std::cout << "guess key length: ";
            std::cin >> k;
            v.createMatrix(k);
            std::cout << "Satisfied? [y/n] ";
            std::cin >> response;
        }
        v.calculateMhs();
        std::cout << "Satisfied? [y/n] ";
        std::cin >> response;
        if(response == 'n') {
            std::cout << "Modify key? [y/n] ";
            std::cin >> response;
            if(response == 'y') {
                std::cout << "Enter fully correct key: ";
                std::string key0;
                std::cin >> key0;
                v.decrypt(key0);
                std::cout << std::endl;
                return 0;
            }
        }
    }
    v.decrypt("");
    std::cout << std::endl;

    return 0;
}
