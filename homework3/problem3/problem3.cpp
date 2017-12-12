/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework3, Problem3
 * Task:    (DES) Find sets test1(E_1, E*_1, C'_1) and test2(E_2, E*_2, C'_2) where
 *          E_1 = 000011,  E*_1 = 110111,  C'_1 = 0111
 *          E_2 = 000100,  E*_2 = 110000,  C'_2 = 1010
 *
 * Build: g++ -std=c++11 problem3.cpp -o problem3_exe
 * Run: ./problem3_exe
 *
 **********************************************************************************************************************/

#include <iostream>
#include <bitset>
#include <list>
#include <algorithm>

short sbox1[4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

short sbox2[4][16] = {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
};

class SBox
{
public:
    SBox(short m[4][16])
    {
        for(int i=0; i<4; ++i)
            for(int j=0; j<16; ++j)
                matrix[i][j] = m[i][j];
    }

    std::bitset<4> operator()(std::bitset<6> x)
    {
        short r = (x[5] << 1) | x[0];
        short c = (x[4] << 3) | (x[3] << 2) | (x[2] << 1) | x[1];

        return (std::bitset<4>)matrix[r][c];
    }

private:
    short matrix[4][16];
};

std::list<std::bitset<6>> IN(std::bitset<6> B, std::bitset<4> C, SBox S)
{
    std::list<std::bitset<6>> ret;

    for(int i=0; i<64; ++i) {
        std::bitset<6> b(i);
        if( ( S(b) ^ S(B ^ b) ) == C )
            ret.push_back(b);
    }

    return ret;
}

std::list<std::bitset<6>> test(std::bitset<6> E, std::bitset<6> e, std::bitset<4> C, SBox S)
{
    std::list<std::bitset<6>> ret;

    std::bitset<6> E1 = E ^ e;
    std::list<std::bitset<6>> in = IN(E1,C,S);

    for(auto it = in.begin(); it != in.end(); ++it) {
        std::bitset<6> b = (*it) ^ E;
        if(std::find(ret.begin(), ret.end(), b) == ret.end())
            ret.push_back((*it) ^ E);
    }

    return ret;
}

int main() {

    std::cout << std::endl;

    SBox S1(sbox1);
    SBox S2(sbox2);

    std::list<std::bitset<6>> test1 = test(0b000011, 0b110111, 0b0111, S1);
    std::list<std::bitset<6>> test2 = test(0b000100, 0b110000, 0b1010, S2);

    std::cout << "test1(000011, 110111, 0111) = {";
    auto it = test1.begin();
    std::cout << *it; ++it;
    while(it != test1.end()) { std::cout << ", " << (*it); ++it; }
    std::cout << "}" << std::endl << std::endl;

    std::cout << "test2(000100, 110000, 1010) = {";
    it = test2.begin();
    std::cout << *it; ++it;
    while(it != test2.end()) { std::cout << ", " << (*it); ++it; }
    std::cout << "}" << std::endl;

    std::cout << std::endl;
    return 0;
}