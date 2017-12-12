/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework3, Problem1
 * Task:    In ciphertext.txt is a ciphertext obtained with column transposition cipher from open text on Croatian language.
 *          Decrypt the text if number of columns is greater than 4 and less than 16.
 *
 * Build: g++ problem1.cpp -o problem1_exe
 * Run: ./problem1_exe
 *
 **********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <list>

class ColumnTransposition
{
public:
    ColumnTransposition(std::string file)
    {
        std::ifstream btxt("frequent_bigrams.txt");
        std::string bg;
        if(btxt.is_open()) {
            while(btxt >> bg) frequent_bigrams.insert(bg);
            btxt.close();
        }
        else std::cout << "Unable to open frequent bigrams file";

        std::ifstream ctxt(file.c_str());
        ciphertext = "";
        char c;
        if(ctxt.is_open()) {
            while(ctxt >> c) ciphertext += c;
            ctxt.close();
        } else std::cout << "Unable to open ciphertext file";

        std::cout << std::endl << ciphertext << std::endl << "length: " << ciphertext.length() <<  std::endl;
    }

    void showFactorization()
    {
        bool isFirst = true;
        std::cout << ciphertext.length() << " = ";
        int ltmp = ciphertext.length();
        int hl = ltmp/2;

        for(int i=2; i<=hl; ++i)
            while(ltmp%i == 0) {
                if(isFirst) { std::cout << i; isFirst = false; }
                else std::cout << "*" << i;
                ltmp /= i;
            }

        std::cout << std::endl;
    }

    bool isVowel(char c)
    {
        switch(c) {
            case 'A': return true;
            case 'E': return true;
            case 'I': return true;
            case 'O': return true;
            case 'U': return true;
            default: return false;
        }
    }

    void drawMatrix()
    {
        std::cout << std::endl;

        matrix = (char**)malloc(rows*sizeof(char*));
        for(int i=0; i<rows; ++i) matrix[i] = (char*)malloc(columns*sizeof(char));
        int consCount;

        for(int i=0; i<rows; ++i)
            for(int j=0; j<columns; ++j) {
                if(j*rows+i >= ciphertext.length())
                    matrix[i][j] = 'X';
                else
                    matrix[i][j] = ciphertext[j*rows + i];
            }

        for(int i=0; i<rows; ++i) {
            consCount = 0;
            for(int j=0; j<columns; ++j) {
                std::cout << matrix[i][j] << " ";
                if(isVowel(matrix[i][j]))
                    consCount++;
            }
            std::cout << " " << consCount << ":" << columns-consCount << std::endl;
        }

        std::cout << std::endl;
    }

    void drawBigramOccurrenceTable()
    {
        int count;
        std::string bigram;

        std::cout << std::endl << "bigram occurrences table:" << std::endl;
        for(int i=-2; i<columns; ++i) {
            for (int j=-1; j<columns; ++j) {
                if(i == -2 && j == -1) { std::cout << "   |"; continue; }
                if(i == -1 && j == -1) { std::cout << "---|"; continue; }
                if(j == -1) { std::cout << " " << i+1 << (i+1 < 10 ? " |" : "|"); continue; }
                if(i == -2) { std::cout << " " << j+1 << (j+1 < 10 ? " " : ""); continue; }
                if(i == -1) { std::cout << "---"; continue; }
                if (i == j) { std::cout << "   "; continue; }
                else {
                    count=0;
                    for(int r=0; r<rows; ++r) {
                        bigram = "";
                        bigram += matrix[r][i];
                        bigram += matrix[r][j];
                        if(frequent_bigrams.find(bigram) != frequent_bigrams.end())
                            count++;
                    }
                    std::cout << " " << count << (count < 10 ? " " : "");
                }
            }
            std::cout << std::endl;
        }
    std::cout << std::endl;
    }

    void decrypt()
    {
        int kNum;
        std::list<int> key;
        std::cout << "type key (permutation of {1,...," << columns << "}): ";
        for(int k=0; k<columns; ++k) {
            std::cin >> kNum;
            key.push_back(kNum-1);
        }

        std::cout << "SOLUTION: " << std::endl;

        for(int i=0; i<rows; ++i)
            for(std::list<int>::iterator it=key.begin(); it != key.end(); ++it)
                std::cout << matrix[i][*it];

        std::cout << std::endl << std::endl;
    }

    int rows;
    int columns;

private:
    std::set<std::string> frequent_bigrams;
    std::string ciphertext;
    std::string open_text;
    char** matrix;
};

int main() {

    ColumnTransposition CT("ciphertext.txt");

    CT.showFactorization();

    char matrixSatisfied='n';
    while (matrixSatisfied != 'y') {
        std::cout << "type matrix dimensions (row column): ";
        std::cin >> CT.rows >> CT.columns;
        CT.drawMatrix();
        std::cout << "satisfied with matrix? [y/n] ";
        std::cin >> matrixSatisfied;
    }

    CT.drawBigramOccurrenceTable();

    CT.decrypt();

    return 0;
}
